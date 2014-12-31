#include "strlib.h"
#include <stdio.h>
#include <stdlib.h>
char *make_space(int width){

  char *c;
  if ((c=(char*)calloc((width+20),sizeof(char)))==NULL){
    fprintf(stderr, "malloc error\n");
    return 0;
  }
  int i;
  for(i=0;i<width;i++){
    *c=' ';
    c++;
  }
  c++;
  *c='\0';
  c-=(width+1);
  return (char*)c;
  
}
