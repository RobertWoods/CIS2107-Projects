#include "strlib.h"
#include <stdlib.h>
char *distinct(char *s){
  int size=0;
  char *chars;
  
  while(*s!='\0'){
    size++;
    s++;
  }
  s-=size;
  char *new = (char*) malloc(size+1);
  char *t;
  t = new;
  int i;
  for(i=0;i<size;i++){
    if(is_unique(new, *s)){
	*t = *s;
	t++;
    }
      s++;
  }
  return new;
}

