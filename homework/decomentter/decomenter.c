#include <stdio.h>

#define IN_STRING 0
#define ON_SLASH 1
#define IN_COMMENT 2
#define DEFAULT 3
#define IN_CHAR 4

int main(void){
	char c;
	int state=DEFAULT;

	char how_does_this_work[] = "";
	char is_this_what_he_means[] = """""""""";
	char maybe_this[] = " " " " " ";
	char not_a_comment[] = " /* This string is not removed! * / ";

	/*  sunlight       *   yellow   *    overdrive   */

	// Even this comment isn't removed!

	printf("%s\n",maybe_this);

	while((c=getchar())!=EOF){
		switch(state){
		case IN_COMMENT:
			if(c=='*'){
			  if((c=getchar())=='/'){
			    state=DEFAULT;
			    break;
			  }
			}
			break;
		case ON_SLASH:
		  if(c=='*'){
		    state = IN_COMMENT;
		    break;
		  }
		  char temp = '/';
		  putchar(temp);
		  putchar(c);
		  state = DEFAULT;
		  break;
		case IN_STRING:
		  if(c=='"')
		    state = DEFAULT;
		  putchar(c);
		  break;
		case IN_CHAR:
		  putchar(c);
		  state = DEFAULT;
		  break;
		case DEFAULT:
		  if(c=='/'){
		    state = ON_SLASH;
		    break;
		  }
		  if(c=='\'')
		    state = IN_CHAR;
		  if(c=='"')
		    state = IN_STRING;
		  putchar(c);
		  break;
		}
	}
}
