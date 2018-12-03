#include "project.h"

#define MAX_HASH 1000

typedef int HashFunc(char *str);

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

// hash table
typedef struct _hashTable {
	Node **table;
	HashFunc *hf;	
} HashTable;

typedef HashtTable LIST;
