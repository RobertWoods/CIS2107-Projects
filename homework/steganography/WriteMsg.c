#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_LEN 50

int main(int argc, char **argv){

  FILE *fp;
  FILE *original;
  int c;
  int state = 0;

  /*Initializing command line arguments */
  int vflag=0;
  char *ivalue=NULL;
  char *ovalue=NULL;
  char *mvalue=NULL;
  int hflag=0;
  int flag;

  while((flag = getopt(argc,argv,"vi:o:m:h"))!=-1){
	switch (flag){
	case 'v':
	  vflag=1;
	  break;
	case 'i':
	  ivalue=optarg;
	  break;
	case 'o':
	  ovalue=optarg;
	  break;
	case 'm':
	  mvalue=optarg;
	  break;
	case 'h':
	  hflag=1;
	  break;
	case '?':
	  if(optopt=='i'||optopt=='o'||optopt=='m')
	    fprintf(stderr, "Option -%c requires an argument.\n",optopt);
	  else if(isprint (optopt))
	    fprintf(stderr, "Unkown option '-%c'.\n",optopt);
	  else
	    fprintf(stderr, "Unkown option character '\\x%x'.\n", optopt);
	  return 1;
	default:
	  break;
	  }
      }

  if(hflag)
    printf("This function hides a secret message inside of a .ppm.\n-v for verbose debugging out\n-i to specify input file to copy with message. This takes a required input.\n-o to specify a file name for the output file. This takes a required input. If this is not called, the file will be called testfile.ppm\n-m to specify the message to be hidden. This takes a required input.\n-h to print this help message.\n\n");

  if(vflag)
    printf("verbose = %d, input file = %s, output file = %s, secret message = %s, help = %d\n\n",vflag,ivalue,ovalue,mvalue,hflag);
  
  if(ivalue==NULL){
    printf("Please specify input image");
    return 1;
  }
  if(mvalue==NULL){
    printf("Please specify message");
    return 1;
  }
  original = fopen(ivalue,"r"); //open picture for reading
  char s[BUFF_LEN];
  int i;
  int j;
  int signal = 1;  
  /* Prints header P6 */
  fgets(s,BUFF_LEN,original);
  if(ovalue!=NULL)
    fp = fopen(ovalue,"w+");
  else
    fp = fopen("testfile.ppm", "w+");
  if(vflag)
    printf("Header file begins----------------------\n");
  fprintf(fp, s);
  if(vflag)
    printf("%s",s);
  /* Handles header comments */
  fgets(s,BUFF_LEN,original);
  while(s[0]=='#'||isspace(s[0])){
    fprintf(fp, "# This comment doesn't do anything\n");
    if(vflag)
      printf("%s",s);
    fgets(s,BUFF_LEN,original);
  }
  /*Gets and sets dimensions of picture
    Already set because of the while loop above */
  fprintf(fp,s);
  char subs1[10];
  char subs2[10];
  int t =0;
  while(s[t]!=' '){
    subs1[t]=s[t];
    t++;
  }
  t++;
  int k=0;
  while(s[t]!='\0'){
    subs2[k]=s[t];
    t++;
    k++;
  }
  if(vflag){
    printf("%s",s);
  }
  int height = atoi(subs1);
  int width = atoi(subs2);
  unsigned int pixels = (height*width);
  unsigned int currentpixels=0;
  /*Gets and sets color (should be 255) */
  fgets(s,BUFF_LEN,original);
  fprintf(fp,s);
  if(vflag){
    printf("%s",s);
    printf("End of header file-----------------------------\n\n");
    printf("Length of RGB header line = %d\n",strlen(s));
    printf("height = %d, width = %d, pixels = %d\n",height,width,pixels);
  }
  

  
  /*Reads and then writes length of hidden message*/
  unsigned int size = strlen(mvalue);
  unsigned int tempsize = reverse(size+1); //+1 for null character
  tempsize = tempsize>>((sizeof(unsigned int)-1)*8);
  if(vflag)
    printf("Size of message reversed = %d\n",tempsize);
  for(i=0;i<8;i++){ //arbitrary limit of hidden message as 255 characters
    char currentchar;
    currentchar=fgetc(original);
    currentchar=((currentchar&254)^(tempsize&1));
    tempsize=tempsize>>1;
    fputc(currentchar,fp);
  }
  currentpixels++;
  
  if(vflag)
    printf("Hidden message length: %d\n",size+1);
  /*Hides hidden message */
  for(i=0;i<size+1;i++){
    char currentchar;
    char message = mvalue[i];
    for(j=0;j<8;j++){
      currentchar=fgetc(original);
      unsigned int tempchar = (unsigned int) message;
      tempchar = reverse(tempchar);
      tempchar = tempchar>>((sizeof(unsigned int)-1)*8);;
      char temp = (char) tempchar;
      currentchar=(((temp>>j)&1)^((currentchar&254)));
      fputc(currentchar,fp);
    }
    currentpixels++;
  }
  
  /*Finishes off the file */
  char currentchar;
  currentchar=fgetc(original);
  while(currentpixels<(pixels*3)){
    fputc(currentchar,fp);
    currentchar=fgetc(original);
    currentpixels++;
   }
  fclose(fp);
  fclose(original);
  return 0;
}


