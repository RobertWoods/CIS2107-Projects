#include <ctype.h>
#include "strlib.h"
int begins_with_ignore_case(char *s, char *pre){
  while(*pre!='\0'){
    if(tolower(*s)!=tolower(*pre))
      return 0;
    s++;
    pre++;
  }
  return 1;

		   
}
