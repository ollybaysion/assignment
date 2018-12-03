#include <stdio.h>
#include <stdlib.h>

// body for store data
typedef struct _body {
	char *key;
	int value;
} Body;

// node for hash table
typedef struct _node {
	struct _node *next;
	Body data;
} Node;

// I : hash table
typedef  struct _hashTable {

} HashTable;

typedef HashTable LIST;

// functions for hash table
void HTinit(List *e);
void putHT(LIST *e, char *key, int value);
Body getHT(LIST *e, char *lkey);
int deleteHT(LIST *e, char *lkey, Body *dataPos);
int countHT(LIST *e);

int searchHT(LIST *e, char *lkey, Body *dataPos);
int fileHT(LIST *e, FILE *output);

// functions for hash string to integer
int hashString(char *str);

// functions for dealing with RLE
int numToString(char *des, int src);
void addRLE(char *des, char ch, int len);
void pullRLE(char *des, char *src, int first, int last);
int searchRLE(char *src, char *cmp);
void deleteRLE(char *src, int first, int last);
void insertRLE(char *src, char *str, int idx);
int RLEinfo(char *src, char *dch, int *dlen);
int RLElen(char *src);
void RLEoptimize(char *src);

// FREE : functions for implement each functions above.
int isAlpha(char ch);
int isNum(char ch);
