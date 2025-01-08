/* caesar.c */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


char englishAlph[] = "abcdefghijklmnopqrstuvwxyz";

char *getStringError() {
	return strerror(errno);
}


void runCaesarCipher(char *line, int shift, char *alphabet, int alphabet_length) {	
	int was_upper = false;
	char *ptr = line;
	while (*ptr != '\0') {
		if (!isalpha(*ptr)) {
			ptr++; 
			continue;
		}

		char curr_char = tolower(*ptr);
		if (curr_char != *ptr) was_upper = true;

		char *char_alphab_ptr = NULL;
		int char_alphab_idx = 0;

		char_alphab_ptr = strchr(alphabet, curr_char);
		char_alphab_idx = (int)(char_alphab_ptr - alphabet);
		
		int char_shift_idx = char_alphab_idx + shift;
		char_shift_idx = (char_shift_idx + alphabet_length) % alphabet_length;

		char new_char = '\0';
		new_char = alphabet[char_shift_idx];
		printf("curr_char: %c, alpha_index: %d, shift_index: %d, new_char: %c\n", curr_char, char_alphab_idx, char_shift_idx, new_char);
		
		if (was_upper) {
			*ptr = toupper(new_char);
		} else {
			*ptr = new_char;
		}

		ptr++;
	}

	return;
}

int main() {	
	// define alphabet
	char *alphabet = englishAlph;
	int alphabet_length = strlen(alphabet);

	// get line from user input
	char *text_line = NULL;
	size_t text_line_size = 0;
	int char_count = 0;
	printf("Line: "); 
	fflush(stdout);
	char_count = getline(&text_line, &text_line_size, stdin);
	if (char_count == -1) {
		printf("- Error with getline: [%s]\n", getStringError());
		return -1;
	}

	text_line[strcspn(text_line, "\n")] = '\0';

	// get shift from user input
	int shift = 0; 
	while (true) {
		printf("Shift: ");
		fflush(stdout);
		if (scanf("%d", &shift) != 1) {
			printf("- Error with scanf(): %s.\n", strerror(errno));
			free(text_line);
			return -1;
		} 
		if (shift < -alphabet_length || shift > alphabet_length) {
			printf("- Shift must be between %d and %d.\n", -alphabet_length, alphabet_length);
			continue;	
		}
		break;
	}
		
	printf("Using alphabet: %s [%d]\n", alphabet, alphabet_length);
	
	runCaesarCipher(text_line, shift, alphabet, alphabet_length);

	printf("Shifted line: %s.\n", text_line);
	
	free(text_line);  //getline() requires us to free the allocated memory.
	return 0;
}
