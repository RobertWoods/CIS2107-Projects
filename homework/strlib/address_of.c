#include "strlib.h"
char *address_of(char *h, char *n){

  int index = index_of(h,n);
  return (h+index);
  
}
