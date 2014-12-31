/* Robert Woods
   Lab 3 */


#include <stdio.h>

unsigned int add(unsigned int, unsigned int);
unsigned int sub(unsigned int, unsigned int);
unsigned int mul(unsigned int, unsigned int);
unsigned int reverse(unsigned int);
int evens(unsigned int);
int is_negative(int);
unsigned int pack_date(int, int, int);
int getMonth(unsigned int);
int getDay(unsigned int);
int getYear(unsigned int);


unsigned int add(unsigned int i, unsigned int j) {
  /* can be done in a total of 7 lines, including one to declare an unsigned int, */
  /* two for a while loop, and one for the return       */
  unsigned int xor = i^j;
  unsigned int and = i&j;
  while(and!=0){
    unsigned int shiftand = and << 1;
    and = xor & shiftand;
    xor = xor^shiftand;
  }
  return xor;
}

unsigned int sub(unsigned int i, unsigned int j) {
  /* Similar 7 lines, although there is a shorter way */
  return(add(i, add(~j,1)));
}

unsigned int mul(unsigned int i, unsigned int j) {
  /* can be done in a total of 8 lines including one to declare unsigned ints */
  /* two for a for loop, and one for the return      */
  int iter;
  unsigned int prod=0;
  for(iter=0;iter<j;iter=add(iter,1)){
    prod=add(prod,i);
  }
  return prod;
}

/* returns the integer whose binary representation is the
   same as that of i in reverse. */
unsigned int reverse(unsigned int i) {
  unsigned int reversed=0;
  unsigned int bitsetter=1;
  int iter;

  for(iter=0;iter<(sizeof(unsigned int)*8);iter=add(iter,1)){
    if((i<<1)<i){
      reversed |=bitsetter;
    }
    bitsetter <<=1;
    i<<=1;
  }
  return reversed;
}

/* returns 1 if x < 0
   returns 0 otherwise */
int is_negative(int x) {
  return (x&(1<<4*sizeof(int)));
}

/* returns 1 if there are an even number of 1's in
   x's binary representation or 0 otherwise */
int evens(unsigned int x) {
  int count = 1;
  int temp = x;
  while(x!=0){
    x=x<<1;
    if(x<temp)
      count=count^1;
    temp = x;
  }
  return count;
}

/* returns 1 if x and y have opposite sign (i.e., one is negative and
   the other is non-negative) or 0 otherwise */
int opposite_signs(int x, int y) {
  return(is_negative(x)&~is_negative(y));
}


/* packs a date as year, month, day into a single unsigned int
   with:
   - the day stored as the 5 low-order bits,
   - the month as the next 4 bits, and 
   - the year as the next 12 bits.

   For example if the date is July 4, 1776:
   - day is 4, i.e., 0 0100 
   - month is 7, i.e. 0111
   - year is 1776, i.e. 110 1111 0000

   The function would therefore return the integer:
   0x000DE0E4, i.e.:
   0000 0000 0000 1101 1110 0000 1110 0100 
*/
unsigned int pack_date(int year, int month, int day) {
  unsigned int pack = day;
  pack |=(month<<5);
  pack |=(year<<9);
  return pack;
}


/* given a date stored in the format described above, returns
   the month stored as an int */
int getMonth(unsigned int date) {
  date>>=5;
  date<<=(sizeof(unsigned int)*8-4);
  date>>=(sizeof(unsigned int)*8-4);
  return date;
}

/* given a date stored in the format described above, returns
   the day stored as an int */
int getDay(unsigned int date) {
  date<<=(sizeof(unsigned int)*8-5);
  date>>=(sizeof(unsigned int)*8-5);
  return date;
}

/* given a date stored in the format described above, returns
   the year stored as an int */
int getYear(unsigned int date) {
  date>>=9;
  return date;
}
