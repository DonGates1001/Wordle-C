/**
  * @file lexicon.c
  * @author Don Gates (dpgates)
  stores list of words read from a file and provides functions for working with the list. Allows for 
  acceptance of valid lists and rejection of invalid lists.  Picks a target word and provides useful functions
  for wordle.c to manage gameplay
  */

#include "lexicon.h"
#include "io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** Large prime multiplier used to choose a word pseudo-randomly. */
#define MULTIPLIER 4611686018453

//array containing the list of words read from a file
static char list[WORD_LIMIT][WORD_LEN + 1];
//the current number of words in the list array
static int wordCount = 0;

void readWords(char const filename[]) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Can't open word list: %s\n", filename);
    exit(1);
  }
  
  char word[WORD_LEN + 1];
  
  while (fscanf(fp, "%s", word) == 1) {
    //verify word is correct size
    if (strlen(word) != WORD_LEN) {
      fprintf(stderr, "Invalid word file\n");
      fclose(fp);
      exit(1);
    }
    //verify word only contains valid characters a-z
    for (int i = 0; word[i]; i++) {
      if (word[i] < 'a' || word[i] > 'z') {
        fprintf(stderr, "Invalid word file\n");
        fclose(fp);
        exit(1);
      }
    }
    //copy word into word list if it's within bounds
    if (wordCount < WORD_LIMIT) {
      strcpy(list[wordCount], word);
    }
    wordCount++;
    
    //prints error message if list is too large
    if (wordCount > WORD_LIMIT) {
      fprintf(stderr, "Invalid word file\n");
      fclose(fp);
      exit(1);
    }
  }
  
  //prints error message if list is too small
  if (wordCount < WORD_MIN) {
    fprintf(stderr, "Invalid word file\n");
    fclose(fp);
    exit(1);
  }
  
  //prints error message if word list contains duplicate words
  if (wordCount > WORD_MIN) {
    for (int i = 0; i < wordCount - 1; i++) {
      for (int j = i + 1; j < wordCount; j++) {
        if (strcmp(list[i], list[j]) == 0) {
          fprintf(stderr, "Invalid word file\n");
          fclose(fp);
          exit(1);
        }
      }
    }
  }
  
  fclose(fp);
}

void chooseWord(long seed, char word[]) {
  //get an index to select from global array
  long idx = (seed % wordCount) * MULTIPLIER % wordCount;
  strcpy(word, list[idx]);
}

bool inList(char const word[]) {
  for (int i = 0; i < wordCount; i++) {
    if (strcmp(word, list[i]) == 0) {
      return true;
    }
  }
  return false;
}