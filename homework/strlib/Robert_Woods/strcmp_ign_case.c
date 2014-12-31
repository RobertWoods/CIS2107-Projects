#include <ctype.h>
#include "strlib.h"
int strcmp_ign_case(char *s1, char *s2){
  while(*s1!='\0'){
    if(tolower(*s1)<tolower(*s2))
      return -1;
    else if(tolower(*s1)>tolower(*s2))
      return 1;
    else if(tolower(*s2)=='\0')
      return 1;
    else{
      s1++;
      s2++;
    }
  }
  if(tolower(*s2)!='\0')
    return -1;
  return 0;
}
