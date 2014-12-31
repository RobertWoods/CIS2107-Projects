#include <stdio.h>
#include "strlib.h"
#include <stdlib.h>
char *center(char *s, int width){

  int size = 0;
  while(*s!='\0'){
    s++;
    size++;
  }
  int i;
  s-=size;
  char *result = (char*) malloc(size+1);
  char *c;
  c=result;
  if(width < size){
    for(i=0;i<size;i++){
      *c=*s;
      c++;
      s++;
    }
    return c;
  }

  for(i=0;i<((width-size)/2);i++){
    *c = ' ';
    c++;
  }
  for(i=0;i<size;i++){
    *c = *s;
    c++;
    s++;
  }
  for(i=((width-size)/2);i<(width-size);i++){
    *c= ' ';
    c++;
  }
  *c='\0';
  return result;
  
  
  
}
