#include <stdio.h>

int main(int argc, char **argv){

  int c;
  int spaces;

  while((c = getchar())!=EOF){
    putchar(c);
    if(c=='\n'){
      putchar('\\');
      putchar('n');
    } else if(c=='\t') {
      putchar('\\');
      putchar('t');
    } else if(c==' '){
      spaces++;
    }
    else if(c!=' '){
      spaces=0;
    }
    if(spaces==3){
      putchar('\\');
      putchar('t');
      spaces=0;
    }
  }
  return 0;
}
