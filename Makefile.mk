CC = gcc
CFLAGS = -Wall -g -std=c99

wordle: wordle.o lexicon.o history.o io.o
lexicon.o: lexicon.c lexicon.h io.h
history.o: history.c history.h
io.o: io.c io.h

clean:
	rm -f wordle.o lexicon.o history.o io.o
	rm -f wordle
	rm -f output.txt scores.txt