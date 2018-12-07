#include "project.h"

void addRLE(char *des, char ch, int len);
void pullRLE(char *des, char *src, int first, int last);
int searchRLE(char *src, char *cmp);
void deleteRLE(char *src, int first, int last);
void insertRLE(char *src, char *str, int idx);
int RLEinfo(char *src, char *dch, int *dlen);
int RLElen(char *src);
void RLEoptimize(char *src);

