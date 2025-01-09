/* caesar.c */
#include "caesar.h"


int main() {	
	// define alphabet
	char *alphabet = ALPHABET_EN;
	int alphabet_length = strlen(alphabet);

	// get plaintext input from user input	
	char *text_line = NULL;
	int text_length = getStringInput(&text_line, NULL);
	if (text_length < 0) return -1;
	
	// get shift from user input
	int shift = 0;
	int success = getIntInput(&shift, NULL);	
	if (success < 0) return -1;

	// verify shift is between the range
	if (shift < -alphabet_length || shift > alphabet_length) {
		printf("- Shift must be between %d and %d.\n", -alphabet_length, alphabet_length);
		return -1;	
	}

	printf("Using alphabet: %s [%d] to cipher %s.\n", alphabet, alphabet_length, text_line);
	
	runCaesarCipher(text_line, shift, alphabet, alphabet_length);

	printf("Shifted line: %s.\n", text_line);
	
	free(text_line);  //getline() requires us to free the allocated memory.
	return 0;
}
