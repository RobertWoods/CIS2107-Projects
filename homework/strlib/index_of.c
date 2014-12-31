#include "strlib.h"
int index_of(char *h, char *n){
  int index =0;
  while(*h!='\0'){
    if(*h==*n){
      if(isstring(h,n))
	return index;
    }
    index++;
    h++;
  }
  
}

int isstring(char *h, char *n){
  while(*h==*n &&*h!='\0'){
    h++;
    n++;
  }
  if(*n=='\0')
    return 1;
  return 0;
}
