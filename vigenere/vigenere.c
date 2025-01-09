#include "dep/caesar.h"


void runVigenereCipher(char *line, char *key, char *alphabet, int alphabet_length) {

	int key_length = strlen(key);
	int line_length = strlen(line);
	for (int i = 0; i < line_length; i++) {
		// skip non-alphabetic characters
		if (!isalpha(line[i])) {
			continue;
		}

		// verify corresponding letter in key
		int curr_charkey = key[i % key_length];

		// get shift value of key_c by substracting the
		// length beginning position pointer of alphabet
		// from the curr_charrkey found in alphabet.
		int curr_shift = (int)(strchr(alphabet, curr_charkey) - alphabet); 
		
		// get shifted character
		char new_char = shiftCharacter(line[i], curr_shift, alphabet, alphabet_length);
		line[i] = new_char;

		printf("Char %c -> [ Shift %d ] -> Char %c.\n", curr_charkey, curr_shift, new_char);
	}

	return;
}


int main() {
	char *alphabet = ALPHABET_EN;		
	int alphabet_length = strlen(alphabet);

	char *plaintext_input = NULL;
	getStringInput(&plaintext_input, "Plaintext:");

	char *key_input = NULL;
	getStringInput(&key_input, "Key:");

	runVigenereCipher(plaintext_input, key_input, alphabet, alphabet_length);

	printf("Cipher: %s.\n", plaintext_input);
	free(plaintext_input);
	free(key_input);
	
	return 0;
}
