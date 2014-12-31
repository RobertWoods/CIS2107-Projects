#include "strlib.h"
#include <ctype.h>
int ends_with_ignore_case(char *s, char *suff){
  int suffix_size;
  int size;
  while(*suff!='\0'){
    suffix_size++;
    suff++;
  }
  suff-=suffix_size;
  while(*s!='\0'){
    size++;
    s++;
  }
  s-=suffix_size;
  while(*s!='\0'){
    if(tolower(*s)!=tolower(*suff))
      return 0;
    s++;
    suff++;
  }
  return 1;
}
