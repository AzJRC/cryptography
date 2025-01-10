/* input.h */
#ifndef INPUT_H
#define INPUT_H

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

void printPrompt(char const *prompt);
int getStringInput(char **input, char* prompt);
int getIntInput(int *input, char *prompt);
int openFile(char *path, FILE **fptr);
int getLineFromFile(FILE *fptr, char **line);

#endif // INPUT_H
