/**
  * @file lexicon.h
  * @author Don Gates (dpgates)
  macro constants for use by lexicon.c and wordle.c, and definitions for functions that handle working
  with word list files and picking a target word.
  */

#include <stdbool.h>

/** Maximum lengh of a word on the word list. */
#define WORD_LEN 5

/** Maximum number of words on the word list. */
#define WORD_LIMIT 100000

/** Minimum number of words on the word list. */
#define WORD_MIN 1

/**
  * reads the word list from the given file and checks it for any errors.  Prints an error message
  * if errors are detected.  Possible errors include: world list with no words, with too many words, with
  * any duplicate words, with any words of more or less than 5 letters, and with words that contain non-
  * lowercase letter characters
  * @param filename[] name of file being error-checked and having aa list extracted
  */
void extern readWords(char const filename[]);

/**
  * chooses a word from a list pseudo-randomly and copies it into the word[] array
  * @param seed a number used to assist in the random selection of a word from the list
  * @param word[] array that will hold the word selected
  */
void extern chooseWord(long seed, char word[]);

/**
  * checks word list to see if given word is in it
  * @param word[] the word to check against the list
  * @return true if list contains word, otherwise false
  */
bool extern inList(char const word[]);
