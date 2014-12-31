#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define BUFF_LEN 1000
#define HEADER_SIZE 4
#define SMALL_BLOCK  16
#define MED_BLOCK  64
#define LARGE_BLOCK  128

void *my_malloc(size_t size);
void my_free(void *p);
int is_free(int b);
int is_allocated(int b);
size_t determine_size(size_t size);