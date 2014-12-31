//rename this to not_contains or something
//it also needs to work with the original function
//currently it doesn't stop when it's supposed to because
//there's no null character at the end of the string we're using
//it for
#include "strlib.h"
int is_unique(char *s, char c){
  while(*s!='\0'){
    if(*s==c)
      return 0;
    s++;
  }
  return 1;
}
