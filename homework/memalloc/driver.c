#include <stdio.h>
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
  void *pointer3 = my_malloc(100);
  void* pointer5 = my_malloc(200);
  void* pointer6 = my_malloc(650);
  my_free(pointer3);
  my_free(pointer4);
  void* pointer7 = my_malloc(50);
  my_malloc(-5);
  my_malloc(0);
  return 0;
}
