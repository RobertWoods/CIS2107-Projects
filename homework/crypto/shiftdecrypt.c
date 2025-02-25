#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_LEN 20
#define DICT_SIZE 479625

char shift_char(unsigned char c,int n);
char *shift_string(char *s, int n);
int in_dict(char *s, char **dict);

int main(int argv, char **argc){
  //initialization
  FILE *dict_file;
  FILE *ciph_file;
  char *dict_name;
  if(argv>1)
	dict_name = argc[2];
  else
	dict_name = "/usr/share/dict/words";
  char *ciph_name = argc[1];
  dict_file = fopen(dict_name, "r");
  if(dict_file==NULL){
	printf("Error: Dictionary not found\n");
	return 0;
	}
  char **dict_array =(char**) malloc((DICT_SIZE)*(BUFF_LEN+1));
  char *ciph_array[100];
  int len = 0;
  
  //getting dictionary in array
  while(len < DICT_SIZE){
	char *word;
	word = malloc(BUFF_LEN);
	char c;
	int wordlen = 0;
	while((c = fgetc(dict_file))!='\n'&&c!=EOF){
		*word = c;
		word++;
		wordlen++;
	}
	*word = '\0';
	word-=wordlen;
	*(dict_array+len) = word;
	len++;
  }
  
  //initializing cipher file
  ciph_file = fopen(ciph_name, "r");
  if(ciph_file==NULL){
	printf("Error: File to decrypt not found\n");
	return 1;
  }
  int ciph_len = 0;
  int ciph_val = 1;
  int ciph_ans = -1;

  char words[BUFF_LEN];
  fgets(words,BUFF_LEN,ciph_file);

  if(words==NULL){
    printf("Error\n");
    ciph_val = 57;
  }
  
  //determining cipher value
  while(ciph_val < 26 && ciph_ans ==-1){
    if(cipher_match(ciph_file, dict_array, ciph_val)){
      ciph_ans = ciph_val;
	  }
    ciph_val++;
    fclose(ciph_file);
    ciph_file = fopen(ciph_name, "r");
  }
  printf("Cipher value = %d\n",ciph_ans);  
  if(ciph_ans==-1)
	return 0;
	
  //write decrypted file
  fclose(dict_file);
  fclose(ciph_file);
  ciph_file = fopen(ciph_name,"r");
  FILE *write_file;
  write_file = fopen("decrypted","w+");
  char ch;
  while((ch=fgetc(ciph_file))!=EOF){
	fputc(shift_char(ch,ciph_ans),write_file);
	//printf("%c",shift_char(ch,ciph_ans)); outputs file to stdout instead
  }
  
  return 1;
}

int cipher_match(FILE *file, char **dict, int ciph_val){
  int num_matching = 0;
  int ciph_len = 0;
  char words[BUFF_LEN];
  fgets(words, BUFF_LEN, file);

  while(words!=NULL && ciph_len<1000){
    char *temp_line;
    temp_line = strtok(words, "\n");
    while(temp_line!=NULL){
      char *temp_word;
      temp_word = strtok(temp_line, " .-'!?,+=@#$%^&*()_");
      while(temp_word!=NULL &&(strlen(temp_word)>1||(temp_word=="A"||temp_word=="I"))){
			num_matching += in_dict(shift_string(temp_word, ciph_val), dict);
			if(in_dict(shift_string(temp_word, ciph_val), dict)){
			}
			ciph_len++;
			temp_word = strtok(NULL, " .-'!?,+=@#$%^&*()_");
			
			}
		temp_line = strtok(NULL, "\n");
		}
		fgets(words, BUFF_LEN,file);
	}
  if(num_matching >= (ciph_len/1.5))
    return 1;
  return 0;
}

int in_dict(char *s, char **dict){
  int low = 0;
  int high = DICT_SIZE-1;
  int i = (low+high)/2;
  while(high!=low&&high!=i&&low!=i){
    if(strcasecmp(s,dict[i])==0){
		return 1;
    } else if(strcasecmp(s,dict[i])>0){
		low = i;
		i=((low+high)/2+1);
	} else if(strcasecmp(s,dict[i])<0){
		high = i;
		i=((low+high)/2);
		}
  }
  return 0;
}

char *shift_string(char *s, int n){
  if(n>26){
    fprintf(stderr,"Error : shift greater than 26\n");
    return s;
  }
  int len = strlen(s);
  char *str = (char*) malloc(len+1);
  while(*s!='\0'){
    *str = shift_char((unsigned char) *s, n);
    str++;
    s++;
  }
  *str = '\0';
  str-=len;
  return str;
}

char shift_char(unsigned char c, int n){
  if(n>26){
    fprintf(stderr, "Error: shift is greater than 26\n");
    return c;
  }
  if(c<='z'&&c>='a'){
    c+=n;
    if(c>'z')
      c-=('z'-'a'+1);
  } else if(c<='Z'&&c>='A'){
    c+=n;
    if(c>'Z')
      c-=('Z'-'A'+1);
  }
  return c;
}

