#include <ctype.h>
#include <stdio.h>
#include "strlib.h"

int is_blank(char *s){
  while(*s!='\0'){
    if(!isspace(*s))
       return 0;
    s++;
  }
  printf("Function complete\n");
  return 1;
}
