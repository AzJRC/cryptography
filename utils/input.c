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


int getFileInput(char *path, FILE *fptr, char *prompt) {
	if (prompt == NULL) printPrompt("File:");
	else printPrompt(prompt);

	fptr = fopen(path, "r");
	if (fptr == NULL) return -1;

	return 0;
}

