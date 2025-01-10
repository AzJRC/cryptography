/* caesar.c */
#include "caesar.h"
#include <argp.h>


// argparser logic
static char doc[] =
	"Application that encrypts plaintext using the Caesar cipher.";

static struct argp_option options[] = {
	{"verbose", 'v', 0, 0, "Produce verbose output"},
	{"input", 'i', "STREAM", OPTION_ARG_OPTIONAL, "Select input stream. Either STDIN or FILE."},
	{ 0 }
};

struct arguments {
	char *args[2];
	int verbose;
	char *input;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
	struct arguments *arguments = state->input;
	switch(key) {
		case 'v':
			arguments->verbose = true;
			break;
		case 'i':
			arguments->input = arg;
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = { options, parse_opt, 0, doc};


int main(int argc, char *argv[]) {		
	
	// define default argument values
	struct arguments arguments;
	arguments.verbose = false;
	arguments.input = "STDIN";
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	// define alphabet
	char *alphabet = ALPHABET_EN;
	int alphabet_length = strlen(alphabet);
	if (arguments.verbose) printf("* alphabet [%s:%d] loaded.", alphabet, alphabet_length); 

	// get plaintext or filepath from user input	
	char *input = NULL;
	char *input_prompt = NULL;
	if (strcmp(arguments.input, ARGINPUT_STDIN) == 0)
		input_prompt = "Plaintext:";
	else if (strcmp(arguments.input, ARGINPUT_FILE) == 0) 
		input_prompt = "Filepath:";

	int file_length = getStringInput(&input, input_prompt);
	if (file_length < 0) return -1;

	FILE *fptr = NULL;
	if (strcmp(arguments.input, ARGINPUT_FILE) == 0) {
		int file_length = openFile(input, &fptr);
		if (file_length < 0) return -1;
	}
	
	// get shift from user input
	int shift = 0;
	int success = getIntInput(&shift, NULL);	
	if (success < 0) return -1;
	if (shift < -alphabet_length || shift > alphabet_length) {
		// verify shift is between the range
		printf("- Shift must be between %d and %d.\n", -alphabet_length, alphabet_length);
		return -1;	
	}

	// run the caesar cipher depending on the input type
	if (strcmp(arguments.input, ARGINPUT_STDIN) == 0) {
		runCaesarCipher(input, shift, alphabet, alphabet_length, arguments.verbose);
		printf("Ciphertext: %s.\n", input);
	} else if (strcmp(arguments.input, ARGINPUT_FILE) == 0) {
		while (true) {
			int result = getLineFromFile(fptr, &input);
			if (result < 0) return -1;
			if (result == 0) break;
			
			input[result - 1] = '\0';
			runCaesarCipher(input, shift, alphabet, alphabet_length, arguments.verbose);
			printf("Ciphertext: %s.\n", input);
		}
	}
	
	free(input);  //getline() requires us to free the allocated memory.
	return 0;
}
