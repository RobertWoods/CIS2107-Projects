#include "strlib.h"
#include <stdio.h>
#include <stdlib.h>
#define IN_WORD 1
#define OUT_WORD 0

char *ellipsize(char *s, int nw){
  int size=0;
  int words =0;
  int state = (isspace(*s));
  while(*s!='\0'){
    s++;
    size++;
  }
  s-=size;
  char *ellipse = (char*) malloc(size+5);
  if(ellipse==NULL)
    return NULL;

  char * result;
  result = ellipse;
  printf("Number of words: %d\n",words);

  while(*s!='\0' && (words < nw || state==IN_WORD)){
    *result = *s;
    result++;
    if(isspace(*s) && state==IN_WORD)
      state = OUT_WORD;
    else if(!(isspace(*s)) && state == OUT_WORD){
      state = IN_WORD;
      words++;
    }
    s++;
  }  
  *result = '.';
  result++;
  *result = '.';
  result++;
  *result = '.';
  result++;
  *result = '\0';
  return ellipse;
}
