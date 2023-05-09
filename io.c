/**
  * @file io.c
  * @author Don Gates (dpgates)
  functions for assisting wordle.c in handling user input and program output to the terminal.  Also 
  assists program in file handling
  */

#include "io.h"
#include <stdio.h>
#include <stdbool.h>

/** escape sequence for printing green to terminal */
#define COLOR_GREEN "\x1b\x5b\x33\x32\x6d"
/** escape sequence for printing green to terminal */
#define COLOR_YELLOW "\x1b\x5b\x33\x33\x6d"
/** escape sequence for printing green to terminal */
#define COLOR_DEFAULT "\x1b\x5b\x30\x6d"

bool readLine(FILE *fp, char str[], int n) {
  int ch = fgetc(fp);
  int idx = 0;
  while (ch != '\n' && ch != EOF) {
    if (idx < n) {
      str[idx++] = ch;
    }
    ch = fgetc(fp);
  }
  if (idx == 0) {
    return false;
  }
  str[idx] = '\0';
  return true;
}

void colorGreen() {
  printf(COLOR_GREEN);
}

void colorYellow() {
  printf(COLOR_YELLOW);
}

void colorDefault() {
  printf(COLOR_DEFAULT);
}