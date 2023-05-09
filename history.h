/**
  * @file history.h
  * @author Don Gates (dpgates)
  contains definitions and macros used by history.c and wordle.c
*/

/** range of guess counts tracked by program */
#define GUESS_RANGE 10

/**
  * reads a scores file, creates array from the file to manipulate its data, then overwrites the scores
  * file with updated data properly formatted.  Prints to the terminal the latest user statistics
  * @param guessCount the number of guesses user needed to guess the target word
  */
void extern updateScore(int guessCount);