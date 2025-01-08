/* ucaesar.h */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>


#define ALPHABET_EN "abcdefghijklmnopqrstuvwxyz";

void printerr(char *message);
void printPrompt(char *prompt);
int getStringInput(char **input, char* prompt);
int getIntInput(int *input, char *prompt);


void printerr(char *message) {
	if (message == NULL) message = "Generic error within a funct()";
	printf("- %s: [%s]\n", message, strerror(errno));
	return;
}


void printPrompt(char *prompt) {
	if (prompt == NULL) prompt = ">";
	printf("%s ", prompt); 
	fflush(stdout);
	return;
}


int getStringInput(char **input, char* prompt) {		
	if (prompt == NULL) printPrompt("String:");
	else printPrompt(prompt);

	int char_count = 0;
	size_t input_size = 0;
	char_count = getline(input, &input_size, stdin);
	if (char_count == -1) {
		printerr("Error with getline()");
		return -1;
	}
	(*input)[strcspn(*input, "\n")] = '\0';
	return strlen(*input);
}


int getIntInput(int *input, char *prompt) {
	if (prompt == NULL) printPrompt("Integer:");
	else printPrompt(prompt);

	fflush(stdout);
	if (scanf("%d", input) != 1) {
		printerr("Error with scanf()");
		return -1;
	} 
	return 0;
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

