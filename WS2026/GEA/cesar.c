#include <stdio.h>

/* ASCII: A-Z -> 65-90 */
#define ALPH 26
#define ASCIIA 65
#define ASCIIZ 90
#define SIZEIN 1024
#define MODULO(a,b) ((a % b + b) % b)

/* print character distribution and return char with highest occurrence */
int printCharDist(int*);

int main(void) {
  char langMaxOcc; 
  char s[SIZEIN];
  int charDist[ALPH] = {0};
 
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
  printf("Input cipher text:\n");
  fgets(s, SIZEIN, stdin);
  printf("input: %s\n", s);
  
  /* count character occurrences */
  for (int i=0; i<SIZEIN; i++) {
    if (s[i] == '\0') {
      break;
    }
    if (s[i] >= ASCIIA && s[i] <= ASCIIZ) {
      charDist[s[i]-ASCIIA]++; 
    }
  }
  
  /* print distribution */
  char max = printCharDist(charDist);
  printf("max occ. char: \'%c\'\n", max);
  
  /* shift whole input by |max - 'E'|%26 */
  int shift = (max - langMaxOcc) % ALPH;
  printf("shift: %d\n", shift);

  for (int i=0; i<SIZEIN; i++) {
    if (s[i] == '\0') {
      break;
    }
    if (s[i] >= ASCIIA && s[i] <= ASCIIZ) {
      s[i] = MODULO(((s[i]-ASCIIA)-shift),ALPH)+ASCIIA;
      printf("shifted s[i]: %d, %c\n", s[i], s[i]);
    }
  }

  printf("%s\n", s);
return 0;
}

int printCharDist(int *charDist) {
  char maxChar = -1;
  int maxOcc = -1;
  for (int i=0; i<ALPH; i++) {
    printf("Letter \'%c\' - #: %d\n", i+ASCIIA, charDist[i]);
    if (charDist[i] > maxOcc) {
      maxOcc = charDist[i];
      maxChar = i+ASCIIA;
    }
  }
  return maxChar;
}
