#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"

int main(void){

  //is_blank
  char string[] = "This is a string";
  printf("string = %s\n", string);
  printf("Is string blank: %d\n", is_blank(string));
  char string2[] = "";
  printf("Is string2 blank: %d\n", is_blank(string2));

  //drop_left
  drop_left(string,2);
  printf("After drop_left(string,2): %s\n",string);
  //drop_right
  drop_right(string,2);
  printf("After drop_right(string,2): %s\n",string);

  //index_of
  printf("The first location of \"is\": %d\n",index_of(string,"is"));
  printf("The first location of \"a\": %d\n",index_of(string,"a"));
  //address_of
  printf("The string starting from \"a\": %s\n",address_of(string, "a"));

  //make_space
  char *cp;
  cp=make_space(7);
  if(cp==NULL)
    printf("Why isnt this working...\n");
  printf("The following is 7 spaces wide : '%s'\n",cp);

  //distinct
  char d1[] = "This is a string";
  char *c = distinct(d1);
  printf("d1 with no duplicates is : %s\n",c);

  //center
  char centered[10] = "( )";
  char *cent;
  cent = center(centered,8);
  printf("center centered : '%s'\n",cent);

  //begins_with_ignore_case
  char ignore_case[] = "This ignored";
  char ignore[] = "this";
  char not_ignore[] = "That";
  printf("Is ignore a prefix of ignore_case : %d\n",begins_with_ignore_case(ignore_case,ignore));
  printf("Is not_ignore a prefix of ignore_case : %d\n",begins_with_ignore_case(ignore_case,not_ignore));
  //ends_with_ignore_case
  char this[] = "igNoRed";
  char not_this[] = "this";
  printf("Is this a sufix of ignore_case : %d\n",ends_with_ignore_case(ignore_case,this));
  printf("Is not_this a suffix of ignore_case : %d\n",ends_with_ignore_case(ignore_case,not_this));

  //remove_chars
  char *buggy = "buggy";
  char *by;
  by = remove_chars(buggy, "aguert");
  printf("buggy = %s\n",buggy);
  printf("remove(buggy,aguert) = %s\n",by);
  
  //repeat
  char *allright = "all right ";
  char *copy;
  copy = repeat(allright,3);
  printf("'%s' copied 3 times is : '%s'\n",allright,copy);

  
  //intersect
  char p1[50] = "This is a string";
  char p2[50] = "Your destiny, this is";
  char *p3 = intersect(p1,p2);
  printf("intersection of 'This is a string' and 'Your destiny, this is' : '%s'\n", p3);

  //strcmp_ign_case
  char z[] = "zzZZzzZZ";
  char a[] = "aaAAaaAA";
  char m[] = "mmMMmmMM";
  char ashort[] = "aaAA";
  char ab[] = "aaAAaaAB";
  printf("Is z > a : %d\n",strcmp_ign_case(z,a));
  printf("Is a > m : %d\n",strcmp_ign_case(a,m));
  printf("Is m > m : %d\n",strcmp_ign_case(m,m));
  printf("Is ashort > a : %d\n",strcmp_ign_case(ashort,a));
  printf("is ab > a : %d\n",strcmp_ign_case(ab,a));

  //ellipsize
  char story[] = "They lived pretty good after that";
  char *tale;
  tale = ellipsize(story, 3);
  printf("Ellipsed: %s\n",tale);

  
  //replace
  char base[] = "We're all pretty happy right now. Yes, happy, happy, happy!";
  char pat[] = "happy";
  char rep[] = "excited";
  char *excitedbase;
  excitedbase = replace(base,pat,rep);
  printf("%s\n",base);
  printf("Lets turn happy to excited : '%s'\n",excitedbase);

  //chop
  char sentence[] = "This is a sentence. It's delimited by space characters";
  char **chopped;
  printf("%s\n",sentence);
  chopped = chop(sentence,' ');
  int i=0;
  while(chopped[i]!=NULL){
    printf("chopped[%d] = '%s'\n",i,chopped[i]);
    i++;
  }
  printf("chopped[%d] = '%s'\n",i,chopped[i]);
  return 1;

}
