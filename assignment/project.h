#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define HASH_LEN 1000

/*
 * all functions used in main.c
 */


// functions for input data
void input(char op); // input operation and do proper act.

// functions for hash table
typedef int HashFunc(char *str);
typedef int HashComp(char *str1, char *str2);

void HTinit(TABLE *e, HashFunc *f, HashComp *c);
void putHT(TABLE *e, char *lkey, int lvalue);
Body getHT(TABLE *e, char *lkey);
int deleteHT(TABLE *e, char *lkey, Body *dataPos);
int countHT(TABLE *e);

int fileHT(TABLE *e, FILE *output);

// functions for hash string to integer
int hashString(char *str);

// functions for search data
Node *searchHT(TABLE *e, char *find);

// FREE : functions for implement each functions above.
int isAlpha(char ch);
int isNum(char ch);
int numToString(char *des, int src);

