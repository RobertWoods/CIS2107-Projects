#include "strlib.h"
#include <stdio.h>
#include <stdlib.h>
char **chop(char *s, char c){

  char **result = malloc(500);
  int size=0;
  char *x;
  x=s;
  char **sa;
  sa = result;
  char *chars;
  chars = *result;
  int i =0;
  
  sa[i] = chars;
  i++;

  
  while(*s!='\0'){
    if(*s==c){
      *chars = '\0';
      sa[i] = (chars+1);
      i++;
    }
    else {
      chars = s;
    }
    chars++;
    s++;
  }
  sa[i] = NULL;
  sa[0] = x;
  
  return result;
}
