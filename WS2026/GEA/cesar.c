#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* ASCII: A-Z -> 65-90 */
#define ALPH 26
#define ASCIIA 65
#define ASCIIZ 90
#define SIZEIN 1024
#define HUNDRED 100
#define MODULO(a,b) ((a % b + b) % b)
#define DOT '.'
#define POUND '#'

/* print character distribution and return char with highest occurrence */
int printCharDist(int*, bool);

/* print character histogram */
void printCharHist(int*, int);

int main(void) {
  char langMaxOcc; 
  char s[SIZEIN];
  int charDist[ALPH] = {0};
  int charCnt = 0;

  /* gather input */
  printf("Choose language: 1 - German, 2 - English\n");
  switch (fgetc(stdin)) {
    case 2: langMaxOcc = 'E';
      break;
    case 1:
    default:
      langMaxOcc = 'E';
      break;
  }
  getc(stdin);
  printf("Input cipher text:\n");
  fgets(s, SIZEIN, stdin);
  
  /* count character occurrences */
  for (int i=0; i<SIZEIN; i++) {
    if (s[i] == '\0') {
      break;
    }
    if (s[i] >= ASCIIA && s[i] <= ASCIIZ) {
      charDist[s[i]-ASCIIA]++;
      charCnt++;
    }
  }
  
  /* print distribution */
  char max = printCharDist(charDist, true);
  printCharHist(charDist, charCnt);
  printf("\nMost frequent character: \'%c\'\n", max);
  
  /* shift whole input by |max - 'E'|%26 */
  int shift = (max - langMaxOcc) % ALPH;

  for (int i=0; i<SIZEIN; i++) {
    if (s[i] == '\0') {
      break;
    }
    if (s[i] >= ASCIIA && s[i] <= ASCIIZ) {
      s[i] = MODULO(((s[i]-ASCIIA)-shift),ALPH)+ASCIIA;
      //printf("shifted s[i]: %d, %c\n", s[i], s[i]);
    }
  }

  printf("\nSolution: %s\n", s);
return 0;
}

int printCharDist(int *charDist, bool silent) {
  char maxChar = -1;
  int maxOcc = -1;
  for (int i=0; i<ALPH; i++) {
    if (!silent) {
      printf("Letter \'%c\' - #: %d\n", i+ASCIIA, charDist[i]);
    }
    if (charDist[i] > maxOcc) {
      maxOcc = charDist[i];
      maxChar = i+ASCIIA;
    }
  }
  return maxChar;
}

void printCharHist(int *charDist, int charCnt) {
  for (int i=0; i<ALPH; i++) {
    char bar[33];
    
    int perc = charDist[i] > 0 ? round(((double)charDist[i]/charCnt)*HUNDRED) : 0;
    memset(bar, POUND, perc);
    memset(bar+perc, DOT, (33-perc));
    printf("%c |%s|\n", i+ASCIIA, bar);
  }
}
