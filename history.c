/**
  * @file history.c
  * @author Don Gates (dpgates)
  Handles the printing of user statistics and saving those statistics to file
  for continuous tracking
  */

#include "history.h"
#include <stdio.h>

void updateScore(int guessCount) {
  FILE *scores = fopen("scores.txt", "r");
  
  //create scores.txt file if it doesn't exist
  if (!scores) {
    scores = fopen("scores.txt", "w");
    fprintf(scores, "0 0 0 0 0 0 0 0 0 0\n");
    fclose(scores);
    scores = fopen("scores.txt", "r");
  }
  
  //create array to hold contents of scores.txt
  int numGuesses[GUESS_RANGE];
  //read scores.txt contents
  for (int i = 0; i < GUESS_RANGE; i++) {
    fscanf(scores, "%d", &numGuesses[i]);
  }
  fclose(scores);
  
  //increment index matching guessCount
  guessCount < GUESS_RANGE ? numGuesses[guessCount - 1]++ : numGuesses[GUESS_RANGE - 1]++;
  
  //update scores.txt
  FILE *scoresUpdate = fopen("scores.txt", "w");
  for (int i = 0; i < GUESS_RANGE - 1; i++) {
    fprintf(scoresUpdate, "%d ", numGuesses[i]);
  }
  fprintf(scoresUpdate, "%d\n", numGuesses[GUESS_RANGE - 1]);
  fclose(scoresUpdate);
  
  //print updated scores
  guessCount == 1 ? printf("Solved in 1 guess\n") : printf("Solved in %d guesses\n", guessCount);
  for (int i = 1; i < GUESS_RANGE; i++) {
    printf(" %d  : %4d\n", i, numGuesses[i - 1]);
  }
  printf("10+ : %4d\n", numGuesses[GUESS_RANGE - 1]);
  
}