/* ucaesar.h */
#ifndef CAESAR_H
#define CAESAR_H

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utils/input.h"


#define ALPHABET_EN "abcdefghijklmnopqrstuvwxyz";


char shiftCharacter(char c, int shift, char *alphabet, int alphabet_length);
void runCaesarCipher(char *line, int shift, char *alphabet, int alphabet_length);


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

#endif // CAESAR_H
