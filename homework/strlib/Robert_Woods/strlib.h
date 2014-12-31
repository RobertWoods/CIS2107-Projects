#include <stdlib.h>
int is_blank(char *s);
void drop_left(char *s, int n);
void drop_right(char *s, int n);
int index_of(char *h, char *n);
char* address_of(char *h, char *n);
char* make_space(int width);
char* distinct(char *s);
char* center(char *s, int width);
int begins_with_ignore_case(char *s, char *pre);
int ends_with_ignore_case(char *s, char *stuff);
char *remove_chars(char *s1, char *s2);
char *repeat(char *s, int x);
char *intersect(char *s1, char *s2);
int strcmp_ign_case(char *s1, char *s2);
char *ellipsize(char *s, int nw);
char *replace(char *s, char *pat, char *rep);
char **chop(char *s, char c);
int is_unique(char *s, char c);
