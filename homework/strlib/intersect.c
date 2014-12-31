#include "strlib.h"
#include <stdlib.h>

char *intersect(char *s1, char *s2){
  int size1=0;
  int size2=0;
  int size;
  while(*s1!='\0'){
    s1++;
    size1++;
  }
  s1-=size1;
  while(*s2!='\0'){
    s2++;
    size2++;
  }
  s2-=size2;
  if(size1>size2)
    size=size1;
  else
    size=size2;

  char *intersect = (char*) malloc(size+1);
  if(intersect==NULL)
    return NULL;

  char *c;
  c=intersect;
  while(*s1!='\0'){
    if(!(is_unique(s2,*s1))){
	*c=*s1;
	c++;
      }
      s1++;
  }
    *c = '\0';
    return intersect;
}
