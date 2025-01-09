
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = caesar


all:
	$(CC) $(OBJ).c ../utils/input.c -o bin/$(OBJ).o

debug:
	$(CC) $(CFLAGS) $(OBJ).c ../utils/input.c -o bin/$(OBJ).o

clean:
	rm bin/$(OBJ).o
