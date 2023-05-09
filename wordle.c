/**
  * @file wordle.c
  * @author Don Gates (dpgates)
  program for running a version of the game wordle through the command line
  */
  
#include "io.h"
#include "history.h"
#include "lexicon.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/** max number of cl args */
#define MAX_ARGS 3
/** min number of cl args */
#define MIN_ARGS 2
/** index of cl arg declaring file name */
#define FILE_ARG 1
/** index of cl arg declaring seed long */
#define SEED_ARG 2
/** value for printing green character */
#define GREEN_COLOR 2
/** value for printing yellow character */
#define YELLOW_COLOR 1
/** value for printing default color character */
#define DEFAULT_COLOR 0

/**
  * Function determines what indexes of the user's guess get printed out in which colors
  * @param printColor[] an array that holds a value representing the color the character at that index
  * should be when the user's guess is printed to output
  * @param guess[] is the user's guess
  * @param wordle[] is the target word
  */
static void outputColors(int printColor[], char guess[], char wordle[]) {
  //holds values to determine if target character at index has been matched with a guess character.
  //If it has, integer at that index gets flipped to 0
  int arrayWordle[] = {1, 1, 1, 1, 1};
  //holds values to determine if guess character at index has been matched with a target character
  //If it has, integer at that index gets flipped to 0
  int arrayGuess[] = {1, 1, 1, 1, 1};
  
  //determine the greens
  for (int i = 0; i < WORD_LEN; i++) {
    if (guess[i] == wordle[i]) {
      printColor[i] = GREEN_COLOR;
      arrayWordle[i] = 0;
      arrayGuess[i] = 0;
    }
  }
  //determine the yellows
  for (int i = 0; i < WORD_LEN; i++) {
    for (int j = 0; j < WORD_LEN; j++) {
      if ((guess[i] == wordle[j]) && (arrayGuess[i] != 0) && (arrayWordle[j] != 0)) {
        printColor[i] = YELLOW_COLOR;
        arrayGuess[i] = 0;
        arrayWordle[j] = 0;
      }
    }
  }
}

/**
  * Prints a character to output in the correct color
  * @param printColor[] array containing values that indicate color to print characters at each index
  * @param guess[] array containing characters to be printed
  * @param idx is the index of the character whose print color is to be determined
  */
static void outputPrint(int printColor[], char guess[], int idx) {
  if (printColor[idx] == GREEN_COLOR) {
    colorGreen();
    printf("%c", guess[idx]);
  } else if (printColor[idx] == YELLOW_COLOR) {
    colorYellow();
    printf("%c", guess[idx]);
  } else {
    colorDefault();
    printf("%c", guess[idx]);
  }
}

/**
  * Runs the wordle game.  Accepts commandline arguments and user interacts with game 
  * through terminal input.  Terminates either when user guesses target word or when user
  * types "quit."  Tracks user statistics and saves them to history file.
  * @param argc number of commandline arguments
  * @param argv 1 or 2 command line arguments: a file containing a 5-letter word list and an 
  * optional seed number to generate a word chosen from the provided list
  */
int main(int argc, char *argv[])
{
  //check for 1 or 2 cl args
  if (argc > MAX_ARGS || argc < MIN_ARGS) {
    fprintf(stderr, "usage: wordle <word-list-file> [seed-number]");
    exit(1);
  }
  
  //check if there is 2nd cl arg and whether it is positive long int
  if (argv[SEED_ARG] && atol(argv[SEED_ARG]) <= 0) {
    fprintf(stderr, "usage: wordle <word-list-file> [seed-number]");
    exit(1);
  }
  
  //create seed variable if there is a 2nd cl arg
  long seed;
  if (argv[SEED_ARG]) {
    seed = atol(argv[SEED_ARG]);
  }
  
  //read in the word list
  readWords(argv[FILE_ARG]);
  
  //determine the word for game play from the word list
  char wordle[WORD_LEN + 1];
  if (argv[SEED_ARG]) {
    chooseWord(seed, wordle);
  } else {
    chooseWord(time(NULL), wordle);
  }
  
  //track number of guesses
  int guessCount = 1;
  //will store user guess. 2 is added to word length to prevent user from winning with 6 letter word
  //whose first 5 letters match target wordle word
  char guess[WORD_LEN + 2] = "";
  //read in user input
  bool readSuccess = readLine(stdin, guess, WORD_LEN + 2);
  
  while (strcmp(wordle, guess) != 0) {
    //for quitters
    if ((strcmp(guess, "quit") == 0) || !readSuccess) {
      printf("The word was \"%s\"\n", wordle);
      return(EXIT_SUCCESS);
    }
    //for playaz
    if (!inList(guess)) {
      printf("Invalid guess\n");
      //guess = strcpy(guess, "");
    } else {
      //array to track print colors at character positions
      int printColor[WORD_LEN] = {DEFAULT_COLOR};
      outputColors(printColor, guess, wordle);
      for (int i = 0; i < WORD_LEN; i++) {
        if (i == 0) {
          if (printColor[i] == GREEN_COLOR) {
            colorGreen();
            printf("%c", guess[i]);
          } else if (printColor[i] == YELLOW_COLOR) {
            colorYellow();
            printf("%c", guess[i]);
          } else {
            printf("%c", guess[i]);
          }
        } else {
          //check if color to print has changed
          if (printColor[i] == printColor[i - 1]) {
            printf("%c", guess[i]);
          } else {
            outputPrint(printColor, guess, i);
          }
        }
      }
      //switch back to default color
      if (printColor[WORD_LEN - 1] != DEFAULT_COLOR) {
        colorDefault();
      }
      printf("\n");
      guessCount++;
    }
    readSuccess = readLine(stdin, guess, WORD_LEN + 2);
  }
  
  updateScore(guessCount);
  
  return(EXIT_SUCCESS);
}