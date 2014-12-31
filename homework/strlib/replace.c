#include <stdlib.h>
#include "strlib.h"

char *replace(char *s, char *pat, char *rep){


  int size = 0;
  int repsize = 0;
  int patsize = 0;
  int numpat = 0;
  while(*s!='\0'){
    if(begins_with_ignore_case(s,pat))
      numpat++;
    size++;
    s++;
  }
  s-=size;
  while(*rep != '\0'){
    repsize++;
    rep++;
  }
  rep-=repsize;

  while(*pat !='\0'){
    patsize++;
    pat++;
  }
  pat-=patsize;

  char *replaced = (char*) malloc(size-(numpat*patsize)+(numpat*repsize)+1);
  int replacedsize = 0;

  while(*s!='\0'){
    if(begins_with_ignore_case(s,pat)){
	while(*rep!='\0'){
	  *replaced = *rep;
	  replaced++;
	  rep++;
	}
	s+=(patsize-1);
	rep-=repsize;
    } else {
      *replaced = *s;
      replaced++;
    }
    s++;
  }
  *replaced = '\0';
  replaced -= (size-(numpat*patsize)+(numpat*repsize));//maybe +1 prob not though
  return replaced;
  
}
