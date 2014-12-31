#include "strlib.h"
#include <stdlib.h>
void drop_left(char *s, int n){

  if(s==NULL)
    return;
  char *b = s;
  int i;
  for(i=0;i<n;i++)
    b++;
  while(*b!='\0'){
    *s = *b;
    s++;
    b++;
  }
  *s='\0';
}
