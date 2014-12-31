#include <stdlib.h>
#include "strlib.h"

char *repeat(char *s, int x){
  int size = 0;
  while(*s!='\0'){
    size++;
    s++;
  }
  s-=size;
  char *repeated = (char*) malloc(size*x+1);
  if(repeated==NULL)
    return NULL;
  char *b = repeated;
  int i;
  for(i=0;i<x;i++){
    while(*s!='\0'){
      *b = *s;
      s++;
      b++;
    }
    s-=size;
  }
  *b='\0';
  return repeated;
}
