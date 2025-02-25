#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h> 

#define BUFF_LEN 1000
#define HEADER_SIZE 4
#define SMALL_BLOCK  16
#define MED_BLOCK  64
#define LARGE_BLOCK  128

void *my_malloc(size_t size);
void my_free(void *p);
size_t determine_size(size_t size);
void coalesce(char* x);

static int *end_link = NULL;
static int *beg_link = NULL;

int main(void){
  void *pointer;
  pointer = my_malloc(5);
  char *kill = (char *)pointer;
  *kill = 5;
  void *pointer1 = my_malloc(5);
  void* pointer2 = my_malloc(5);
  my_free(pointer1);
  my_free(pointer2);
  void* pointer4 = my_malloc(10);
  char *pointer3 = my_malloc(100);
  *pointer3 = 30;
  void* pointer5 = my_malloc(200);
  void* pointer6 = my_malloc(650);
  my_free(pointer3);
  my_free(pointer4);
  void* pointer7 = my_malloc(50);
  my_malloc(0);
  return 0;
}

void *my_malloc(size_t size){

	size_t real_size = determine_size(size);
	if(size<=0){
		fprintf(stderr,"No memory called\n");
		errno = ENOMEM;
		return NULL;
	}  
	char *pointer;

	//first time calling my_malloc
	if(beg_link==NULL){
		pointer = calloc(1,BUFF_LEN);
		beg_link = pointer;
		//set free footer
		end_link = (beg_link+BUFF_LEN/4-1);
		*end_link = BUFF_LEN-real_size;
		//set allocated header
		*pointer = (real_size+1);//+1 because it is allocated
		//set allocated footer
		pointer += real_size-HEADER_SIZE;
		*pointer = (real_size+1);//+1 because it is allocated
		//set free header
		pointer+=4;
		int *ip; 
		ip = (int*) pointer;
		*ip = BUFF_LEN-real_size;
		//go to allocated footer
		pointer = beg_link+real_size/4;
		//return to beggining of block and return
		pointer = (beg_link+1); //beg link is int pointer so +1
		return pointer;
	}						
	//find appropriate free block
	int *intptr = beg_link;
	int free_space = *intptr;
	while(free_space<(int)real_size||((free_space&1)==1)){
		intptr = intptr+*intptr/4;	//traverse through linked list
		free_space = *intptr;	//get size of free block
		if(intptr>=end_link){
			fprintf(stderr,"No memory available\n");
			errno = ENOMEM;
			return NULL;
		}
	}
	//intpointer now points to first free block header	
	//set block header
	*intptr = (real_size+1);//+1 because the block is allocated
	pointer = intptr+1;
	//now set block footer
	intptr+=real_size/4-1;
	*intptr = (real_size+1);
	//set new free block header if entire free block is not used
	if(!(free_space-real_size==0)){
		int free_block_size = (free_space-real_size);
		intptr++; //intptr points to block in front of header
		*intptr = free_block_size;//set it to size of new free block
		intptr+=*intptr/4-1;
		*intptr = free_block_size;
		intptr-=*intptr/4-1;//make it point to free header again
		intptr++;
	}
	//int i;
	//for(i=0;i<BUFF_LEN/4;i++){
//		printf("%d ",*(beg_link+i));
//	}
//	printf("\n\n");
	return pointer;
}

void my_free(void *p){
	int *pointer = (int*) p;
	pointer--;
	if(*(pointer-HEADER_SIZE)&1!=1)	return;	//block is already freed, do nothing
	//make block free
	*pointer = *pointer^1;
	p = (void *) pointer;
	pointer = pointer+*pointer/4-1;
	*pointer = *pointer^1;
	pointer = pointer-*pointer/4+1;
	//coalesce
	coalesce(pointer);
	//int i;
	//for(i=0;i<BUFF_LEN/4;i++){
//		printf("%d ",*(beg_link+i));
//	}
//	printf("\n\n");
}


size_t determine_size(size_t size){
  while(size%8!=0){
    size++;
  }
  size+=8;
  return size;
}


void coalesce(char* x){
	//pointer should be a pointer to a header file of a free block
	int *pointer = (int*) x;
	int *next_header = pointer+*pointer/4;
	int *prev_footer = pointer-1;
	if((*next_header&1)==0&&(next_header<=end_link)){
		//block is free, coalesce
		int *next_footer = (next_header+*next_header/4-1);
		*pointer = *pointer+*next_footer;	//sum current header and next footer and place in header
		*next_footer = *pointer;	//same for next footer
	}
	
	if((*prev_footer&1)==0&&(prev_footer>=beg_link)){
		//block is free, coalesce
		int *prev_header = (prev_footer-*prev_footer/4+1);
		*prev_header = *pointer+*prev_header;	//sum current header and prev header and place in prev header
		int *current_footer = (pointer+*pointer/4-1);
		*current_footer = *prev_header;
	}
	
}




