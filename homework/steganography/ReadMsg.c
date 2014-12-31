#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_LEN 50

int main(int argc, char **argv){
  int i;
  int j;
  FILE *file;
  char s[BUFF_LEN];

  /* handling getopt library commands */
  int vflag=0;
  char *ivalue=NULL;
  int hflag=0;
  int flag;
  int state = 0;
  
  while((flag=getopt(argc,argv,"vi:hf"))!=-1){   //no output file on Read
    switch(flag)
      {
      case 'v':
	vflag = 1;
	break;
      case 'i':
	ivalue = optarg;
	break;
      case 'h':
	hflag=1;
	break;
      case '?':
	if(optopt == 'i')
	  fprintf(stderr, "Option -%c requires an argument.\n",optopt);
	else if(isprint(optopt))
	  fprintf(stderr, "Unknown option '-%c'.\n",optopt);
	else
	  fprintf(stderr, "Unknown option character '\\x%x'.\n",optopt);
	return 1;
      default:
	break;
      }
  }

  if(hflag)
    printf("This function returns a secret message hidden in a file, if there is one. Otherwise, it returns nonsense.\n-v for verbose debugging output\n-i to specify input file. This command takes a required argument.\n-h prints this message to the screen.\n\n");

  if(ivalue==NULL)
    return;
  
  if(vflag){
    printf("verbose = %d, input image = %s, help = %d\n\n",vflag,ivalue,hflag);
    printf("Header begins-------------\n");
  }
  file=fopen(ivalue,"r");
  fgets(s,BUFF_LEN,file);
  if(vflag)
    printf("%s",s);
  fgets(s,BUFF_LEN,file);
  if(vflag)
    printf("%s",s);
  while(isspace(s[1])||s[1]=='#'){
    fgets(s,BUFF_LEN,file);
    if(vflag)
      printf("%s",s);
  }
  fgets(s,BUFF_LEN,file);
  if(vflag){
    printf("%s",s);
    printf("Header ends---------------\n\n");
  }
  int size = 0;
  for(i=0;i<8;i++){
    size<<=1;
    char tchar = fgetc(file);
    int bit = (tchar&1);
    size=(size^bit);
  }
  if(vflag)
    printf("Size of message = %d\n\n",size);
  char message[size];
  for(i=0;i<size;i++){
    char mchar=0;
    for(j=0;j<8;j++){
      mchar<<=1;
      char c = fgetc(file);
      c = c&1;
      mchar = (c^mchar);
    }
    message[i]=mchar;
  }
  fclose(file);
  printf("%s\n",message);
}
