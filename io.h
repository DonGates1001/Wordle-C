/**
  * @file io.h
  * @author Don Gates (dpgates)
  definitions of functions for assisting wordle.c in handling user input and program output to the terminal.  
  Also assists program in file handling
  */

#include <stdbool.h>
#include <stdio.h>

/**
  * Reads a line from file, returning true if a line was read, otherwise false.  It stores a
  * successfully read line in the str array, which has a length in characters determined by the
  * n parameter  
  * @param fp a file from which to read a line
  * @param str[] character string in which the line's characters will be stored
  * @param length of str[] parameter
  * @return bool true if a line was read, otherwise false
  */
bool extern readLine(FILE *fp, char str[], int n);

/**
  * changes color of output text to green
  */
void extern colorGreen();

/**
  * changes color of output text to yellow
  */
void extern colorYellow();

/**
  * changes color of output text to default black
  */
void extern colorDefault();