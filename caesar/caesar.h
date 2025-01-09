/* ucaesar.h */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>


#define ALPHABET_EN "abcdefghijklmnopqrstuvwxyz";

void printerr(char const *message);
void printPrompt(char const *prompt);
int getStringInput(char **input, char* prompt);
int getIntInput(int *input, char *prompt);
char shiftCharacter(char c, int shift, char *alphabet, int alphabet_length);
void runCaesarCipher(char *line, int shift, char *alphabet, int alphabet_length);


void printerr(char const *message) {
	if (message == NULL) message = "Generic error within a funct()";
	printf("- %s: [%s]\n", message, strerror(errno));
	return;
}


void printPrompt(char const *prompt) {
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


char shiftCharacter(char c, int shift, char *alphabet, int alphabet_length) {
	char shifted_char = '\0';	// shifted char default to NULL character
	
	// get index of the character c in the alphabet by
	// substracting the beginning pointer location of the
	// alphabet to the pointer poiting to the location of
	// the character c in alphabet.
	int char_index = (int)(strchr(alphabet, c) - alphabet);

	// shift the character +shift letters from the original
	// position. Ensure the location is between boundaries.
	int char_shift = (char_index + shift + alphabet_length) % alphabet_length;

	shifted_char = alphabet[char_shift];  // update shifted char.
	return shifted_char;
}


void runCaesarCipher(char *line, int shift, char *alphabet, int alphabet_length) {	
	
	int was_upper = false;
	char *ptr = line;

	while (*ptr != '\0') {
		// skip non-alphabetic characters
		if (!isalpha(*ptr)) {
			ptr++; 
			continue;
		}

		// map character to its lowercase version
		char curr_char = tolower(*ptr);
		if (curr_char != *ptr) was_upper = true;

		// shift character given shift and alphabet
		char new_char = shiftCharacter(curr_char, shift, alphabet, alphabet_length);

		// get back original case
		if (was_upper) {
			*ptr = toupper(new_char);
		} else {
			*ptr = new_char;
		}

		printf("curr_char: %c -> new_char: %c\n", curr_char, new_char);
		ptr++;
	}

	return;
}

