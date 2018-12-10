#include "./project.h"

#define MAX_HASH 1000

typedef int HashFunc(char *str);
typedef int HashComp(char *str1, char *str2);

// body for store data
typedef struct _body {
	char *key;
	int value;
} Body;

// node for hash table
typedef struct _node {
	struct _node *next;
	struct _node *next_alpha;
	Body data;
} Node;

typedef struct _hashList {
	Node *head;
	Node *cur;
	int numOfData;
} HashList;

typedef HashList LIST;

// hash table (UNIQUE)
typedef struct _hashTable {
	List *table;
	Node *super;
	Node *super_alpha;
	HashFunc *hf;	
	HashComp *hc;
	int numOfData;
} HashTable;

typedef HashtTable TABLE;
