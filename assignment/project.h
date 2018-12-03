#include <stdio.h>
#include <stdlib.h>

// functions for hash table
void HTinit(LIST *e, HashFunc *f);
void putHT(LIST *e, char *lkey, int lvalue);
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
