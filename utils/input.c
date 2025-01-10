/* input.c */
#include "input.h"


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
	if (char_count == -1) return -1;

	(*input)[strcspn(*input, "\n")] = '\0';
	return strlen(*input);
}


int getIntInput(int *input, char *prompt) {
	if (prompt == NULL) printPrompt("Integer:");
	else printPrompt(prompt);
	if (scanf("%d", input) != 1) return -1;
	return 0;
}


int openFile(char *path, FILE **fptr) {
	*fptr = fopen(path, "r");
	if (fptr == NULL) return -1;
	return 0;
}


int getLineFromFile(FILE *fptr, char **line) {
    static long offset = 0;      // Tracks position in the current file
    static FILE *curr_file = NULL;

    // Handle switching to a new file
    if (curr_file != fptr) {
        curr_file = fptr;
        offset = 0;             // Reset offset for the new file
        rewind(fptr);           // Ensure the file starts at the beginning
    }

    // Move to the last known position
    if (fseek(curr_file, offset, SEEK_SET) == -1) {
        return -1; // Error seeking in the file
    }

    // Read the next line
    size_t len = 0;
    ssize_t char_count = getline(line, &len, curr_file);
    if (char_count == -1) {
        return 0; 
    }

    // Update offset
    offset = ftell(curr_file);

    return char_count; // Successfully read a line return count of characters read.
}
