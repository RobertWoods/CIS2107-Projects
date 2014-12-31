#include "strlib.h"
void drop_right(char *s, int n){
  char *b = s;
  int i;
  while(*b!='\0')
    b++;
  for(i=0;i<n;i++){
    if(b==s){
      *s='\0';
      return;
    }
    b--;
  }
  *b='\0';
}
