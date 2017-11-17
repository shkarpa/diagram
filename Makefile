CFLAGS=-std=c11 -Wall
all:
	cc diagram.h main.c -o main $(CFLAGS)
