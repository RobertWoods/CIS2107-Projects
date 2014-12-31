#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOT_HALTED 	0
#define HALTED     	1
#define HALTEDB		2
#define BUFF_LEN  	10

#define HALT 		'0'
#define LD 			'1'
#define ST			'2'
#define ADD			'3'
#define SUB 		'4'
#define LDA			'5'
#define JMP			'6'
#define SKIP		'7'
#define ACC			'8'
#define TWR			'9'

#define SKP			'0'
#define SKEQ		'1'
#define SKNE		'2'
#define	SKGT		'3'
#define SKGE		'4'
#define SKLT		'5'
#define SKLE		'6'

#define IN			'0'
#define	OUT			'1'
#define CLR			'2'
#define INC 		'3'
#define DEC			'4'
#define NEG			'5'
#define	SHL			'6'
#define SHR			'7'

#define MVRR		'0'
#define MVMR		'1'
#define MVRM		'2'
#define EXCH		'3'
#define ADDR		'4'
#define SUBR		'5'

struct instruction {
  char *instr;
  char *ip;
  int flag;
};

struct instruction get_instruction(char *s);
int has_int(int i, int* array);
char *get_str_from_instr(struct instruction inst);
char *process_instr(char *instr);

int main(int argv, char **argc){
  int state = NOT_HALTED;
  struct instruction *instr_array;
  
  if(argv!=2){
    fprintf(stderr, "Invalid input\n");
    return -1;
  }

  FILE *assembly_file;
  assembly_file = fopen(argc[1],"r");
  
  if(assembly_file==NULL){
    fprintf(stderr, "File not found");
    return -1;
  }
	
  FILE *diss_file;
  diss_file = fopen("file_dissassembled", "w+");
  if(diss_file==NULL){
    fprintf(stderr, "Error opening file for write");
    return -1;
  }
  
  int len = 0;
  char *line = (char *) calloc(1,BUFF_LEN+1);
  int intarray[100];
  int intindex = 0;
  
  while((fgets(line,BUFF_LEN,assembly_file))!=NULL){
	if(strlen(line)>2){
		*instr_array = get_instruction(line);
		if(instr_array->instr[0]==JMP){
			int a = (int)instr_array->instr[1]-'0';
			int b = (int)instr_array->instr[2]-'0';
			int c = (int)instr_array->instr[3]-'0';
			intarray[intindex]=(a*100+b*10+c*1);
			intindex++;
		}
	}
	free(line);
	line = (char*) calloc(1,BUFF_LEN+1);
  }
  intarray[intindex] = -1; //prevent oob
  rewind(assembly_file);
  intindex = 0;
  int intiter = 0;
  while((fgets(line,BUFF_LEN,assembly_file))!=NULL){
	if(strlen(line)>2){
		*instr_array = get_instruction(line);
		char *str;
		str = get_str_from_instr((*instr_array));
		fputs(instr_array->ip,diss_file);
		fputs(" ",diss_file);
		fputs(instr_array->instr,diss_file);
		fputs(" ",diss_file);
		if(has_int(intindex,intarray)||state==HALTEDB){
			fputs("L",diss_file);
			char* temp;
			if(intindex<10){
				char sig = '0'+intindex;
				*temp = sig;
				fputs(temp,diss_file);
				fputs(":",diss_file);
				fputs("  ",diss_file);
			} else if(intindex<100){
				char sig1 = '0'+intindex/10;
				char sig2 = '0'+intindex%10;
				*temp = sig1;
				*(temp+1)=sig2;
				fputs(temp,diss_file);
				fputs(":",diss_file);
				fputs(" ",diss_file);
			} else if(intindex<1000){
				char sig1 = '0'+intindex/100;
				char sig2 = '0'+intindex/10;
				char sig3 = '0'+intindex%10;
				*temp = sig1;
				*(temp+1)=sig2;
				*(temp+2)=sig3;
				fputs(temp,diss_file);
				fputs(":",diss_file);
			} else {
				fputs("X",diss_file);
			}
			intiter++;
			if(state==HALTEDB)
				state=HALTED;
		} else {
			fputs("     ",diss_file);
		}
		fputs(" ",diss_file);
		if(strlen(instr_array->instr)>2 &&state!=HALTED)
			fputs(str,diss_file);
		else if(strlen(instr_array->instr)>2 &&state==HALTED)
			fputs(".word",diss_file);
		fputs("\n",diss_file);
		if(strcasecmp(instr_array->instr,"0000 ")==0&&len>2&&state!=HALTED){
			state = HALTEDB;
			}
		len++;
		intindex++;
	}
  }
  fclose(diss_file);
  fclose(assembly_file);
  return 1;
}

struct instruction get_instruction(char *s){
  struct instruction *instr;
  instr = (struct instruction*) malloc(sizeof(int)*2+sizeof(char)*4+sizeof(char)*6);
  char* ipx = calloc(6,sizeof(char));
  char* instrx = calloc(6,sizeof(char));
  ipx = strtok(s," ");
  instr->ip = ipx;
  instrx = strtok(NULL,"\n");
  instr->instr = instrx;
  return *instr;
}

char *get_str_from_instr(struct instruction inst){
  char *output;
  output = (char*) calloc(9,sizeof(char));
  output = inst.ip;
  output+=3;
  output = inst.instr;
  if(inst.instr==NULL)
	return " ";
  char *dis = process_instr(inst.instr);
  output = dis;
  return output;
}

char *process_instr(char instr[]){    
	char *c = (char*) malloc(15);
	int flag =-1;
	if(instr[0]==HALT){
		c = "halt";
	} else if(instr[0]==LD){
		char*temp = "ld ";
		strcpy(c,temp);
		int len = 3; 
		
		if(instr[1]!='0'||flag==1){
			c[len]=instr[1];
			flag =1;
			len++;
			}
		if(instr[2]!='0'||flag==1){
			c[len]=instr[2];
			flag =1;
			len++;
			}
		if(instr[3]!='0'||flag==1){
			c[len]=instr[3];
			flag =1;
			len++;
			}
	} else if(instr[0]==ST){
		char*temp = "st ";
		strcpy(c,temp);
		int len = 3;
		if(instr[1]!='0'||flag==1){
			c[len]=instr[1];
			flag =1;
			len++;
			}
		if(instr[2]!='0'||flag==1){
			c[len]=instr[2];
			flag =1;
			len++;
			}
		if(instr[3]!='0'||flag==1){
			c[len]=instr[3];
			flag =1;
			len++;
			}
	} else if(instr[0]==ADD){
		char*temp = "add ";
		strcpy(c,temp);
		int len = 4; 
		if(instr[1]!='0'||flag==1){
			c[len]=instr[1];
			flag =1;
			len++;
			}
		if(instr[2]!='0'||flag==1){
			c[len]=instr[2];
			flag =1;
			len++;
			}
		if(instr[3]!='0'||flag==1){
			c[len]=instr[3];
			flag =1;
			len++;
			}
	} else if(instr[0]==SUB){
		char*temp = "sub ";
		strcpy(c,temp);
		int len = 4; 
		if(instr[1]!='0'||flag==1){
			c[len]=instr[1];
			flag =1;
			len++;
			}
		if(instr[2]!='0'||flag==1){
			c[len]=instr[2];
			flag =1;
			len++;
			}
		if(instr[3]!='0'||flag==1){
			c[len]=instr[3];
			flag =1;
			len++;
			}
	} else if(instr[0]==LDA){
		char*temp = "lda ";
		strcpy(c,temp);
		int len = 4; 
		if(instr[1]!='0'||flag==1){
			c[len]=instr[1];
			flag =1;
			len++;
			}
		if(instr[2]!='0'||flag==1){
			c[len]=instr[2];
			flag =1;
			len++;
			}
		if(instr[3]!='0'||flag==1){
			c[len]=instr[3];
			flag =1;
			len++;
			}
	} else if(instr[0]==JMP){
		char*temp = "jmp ";
		strcpy(c,temp);
		c[4] = 'L';
		int len = 5; 
		if(instr[1]!='0'||flag==1){
			c[len]=instr[1];
			flag =1;
			len++;
			}
		c[len] = ':';
		if(instr[2]!='0'||flag==1){
			c[len]=instr[2];
			flag =1;
			len++;
			}
		if(instr[3]!='0'||flag==1){
			c[len]=instr[3];
			flag =1;
			len++;
			}
	} else if(instr[0]==SKIP){
		if(instr[1]==SKP){
			c = "skip ";
		} else if(instr[1]==SKEQ){
			char*temp = "skeq";
			strcpy(c,temp);
			c[5]=' ';
			c[6]='%';
			c[7] = 'r';
			c[8]=instr[3];
		} else if(instr[1]==SKNE){
			char*temp = "skne";
			strcpy(c,temp);
			c[4]=' ';
			c[5]='%';
			c[6] = 'r';
			c[7]=instr[3];
		} else if(instr[1]==SKGT){
			char*temp = "skgt";
			strcpy(c,temp);
			c[5]=' ';
			c[6]='%';
			c[7] = 'r';
			c[8]=instr[3];
		} else if(instr[1]==SKGE){
			char*temp = "skge";
			strcpy(c,temp);
			c[5]=' ';
			c[6]='%';
			c[7] = 'r';
			c[8]=instr[3];
		} else if(instr[1]==SKLT){
			char*temp = "sklt";
			strcpy(c,temp);
			c[5]=' ';
			c[6]='%';
			c[7] = 'r';
			c[8]=instr[3];
		} else if(instr[1]==SKLE){
			char*temp = "skle";
			strcpy(c,temp);
			c[5]=' ';
			c[6]='%';
			c[7] = 'r';
			c[8]=instr[3];
		}
	} else if(instr[0]==ACC){
		if(instr[1]==IN){
			char*temp = "in ";
			strcpy(c,temp);
			c[3] = '%';
			c[4] = 'r';
			c[5] = instr[3];
		} else if(instr[1]==OUT){
			char*temp = "out ";
			strcpy(c,temp);
			c[4] = '%';
			c[5] = 'r';
			c[6] = instr[3];
		} else if(instr[1]==CLR){
			char*temp = "clr ";
			strcpy(c,temp);
			c[4] = '%';
			c[5] = 'r';
			c[6] = instr[3];
		} else if(instr[1]==INC){
			char*temp = "inc ";
			strcpy(c,temp);
			c[4] = '%';
			c[5] = 'r';
			c[6] = instr[3];
		} else if(instr[1]==DEC){
			char*temp = "dec ";
			strcpy(c,temp);
			c[4] = '%';
			c[5] = 'r';
			c[6] = instr[3];
		} else if(instr[1]==NEG){
			char*temp = "neg ";
			strcpy(c,temp);
			c[4] = '%';
			c[5] = 'r';
			c[6] = instr[3];
		} else if(instr[1]==SHL){
			char*temp = "shl ";
			strcpy(c,temp);
			c[4] = '%';
			c[5] = 'r';
			c[6] = instr[3];
		} else if(instr[1]==SHR){
			char*temp = "shr ";
			strcpy(c,temp);
			c[4] = '%';
			c[5] = 'r';
			c[6] = instr[3];
		}
	} else if(instr[0]==TWR){
		if(instr[1]==MVRR){
			char*temp = "mvrr ";
			strcpy(c,temp);
			c[5] = '%';
			c[6] = 'r';
			c[7] = instr[2];
			c[8] = ',';
			c[9] = '%';
			c[10] = 'r';
			c[11] = instr[3];
		}
		if(instr[1]==MVMR){
			char*temp = "mvmr ";
			strcpy(c,temp);
			c[5] = '(';
			c[6] = '%';
			c[7] = 'r';
			c[8] = instr[2];
			c[9] = ')';
			c[10] = ',';
			c[11] = '%';
			c[12] = 'r';
			c[13] = instr[3];
		}
		if(instr[1]==MVRM){
			char*temp = "mvrm ";
			strcpy(c,temp);
			c[5] = '%';
			c[6] = 'r';
			c[7] = instr[2];
			c[8] = ',';
			c[9] = '(';
			c[10] = '%';
			c[11] = 'r';
			c[12] = instr[3];
			c[13] = ')';
		}
		if(instr[1]==EXCH){
			char*temp = "exch ";
			strcpy(c,temp);
			c[5] = '%';
			c[6] = 'r';
			c[7] = instr[2];
			c[8] = ',';
			c[9] = '%';
			c[10] = 'r';
			c[11] = instr[3];
		}
		if(instr[1]==ADDR){
			char*temp = "addr ";
			strcpy(c,temp);
			c[5] = '%';
			c[6] = 'r';
			c[7] = instr[2];
			c[8] = ',';
			c[9] = '%';
			c[10] = 'r';
			c[11] = instr[3];
		}
		if(instr[1]==SUBR){
			char*temp = "subr ";
			strcpy(c,temp);
			c[5] = '%';
			c[6] = 'r';
			c[7] = instr[2];
			c[8] = ',';
			c[9] = '%';
			c[10] = 'r';
			c[11] = instr[3];
		}
	} else {
		return " ";
	}
	return c;
	}
	
int has_int(int i, int* array){
	int x = 0;
	while(array[x]!=-1){
		if(array[x]==i)
			return 1;
		x++;
	}
	return 0;
}
