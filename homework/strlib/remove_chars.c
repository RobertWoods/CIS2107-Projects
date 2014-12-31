#include "strlib.h"
#include <stdlib.h>

char *remove_chars(char *s1, char *s2){
  int size = 0;
  while(*s1!='\0'){
    size++;
    s1++;
  }
  s1-=size;
  
  char *newchar = (char*) malloc(size+1);
  if(newchar==NULL)
    return NULL;
  
  char *b = newchar;
  while(*s1!='\0'){
    if(is_unique(s2,*s1)){
      *b = *s1;
      b++;
    }
    s1++;
  }
  return newchar;
}
