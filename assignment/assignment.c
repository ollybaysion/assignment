#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_LEN 1000
#define MAX_HASH 1000
#define MAX_WORD 10

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

// list for hash table
typedef struct _hashList {
	Node *head;
	Node *cur;
	int numOfData;
} HashList;

typedef HashList LIST;

// hash table (UNIQUE)
typedef struct _hashTable {
	LIST *table;
	Node *super;
	Node *super_alpha;
	HashFunc *hf;
	HashComp *hc;
	int numOfData;
} HashTable;

typedef HashTable TABLE;

// functions for input data
void input(TABLE *e, char op, Body *data, FILE *outputFile, char *fileName);

// functions for hash table
Node *putList(LIST *k, Body *bd);
void HTinit(TABLE *e, HashFunc *f, HashComp *c);
void putHT(TABLE *e, Body *bd);
Body *getHT(TABLE *e, char *lkey);
int deleteHT(TABLE *e, char *lkey);
int countHT(TABLE *e);

int fileHT(TABLE *e, FILE *output);

// functions for hash string to integer
int hashString(char *str);

// functions for search data
Body *searchHT(TABLE *e, char *find);

// FREE : functions for implement each functions above.
void decompressRLE(char *des, char *src);
int powerCompare(char *src, char *com);

// for hash List in hash table.
void ListInit(LIST *k)
{
	k->head = (Node *)malloc(sizeof(Node));
	k->cur = k->head;
	k->numOfData = 0;
}

Node *putList(LIST *k, Body *bd)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	int len = strlen(bd->key);
	newNode->data.key = (char *)malloc(sizeof(char) * (len + 1));
	newNode->next = NULL;
	newNode->next_alpha = NULL;
	strcpy(newNode->data.key, bd->key);
	newNode->data.value = bd->value;


	k->cur->next = newNode;
	k->cur = k->cur->next;
	k->numOfData++;

	return newNode;
}

// for hash table
void HTinit(TABLE *e, HashFunc *f, HashComp *c)
{
	e->table = (LIST *)malloc(sizeof(LIST) * HASH_LEN);
	for (int i = 0; i < HASH_LEN; i++)
	{
		LIST *l = &(e->table[i]);
		ListInit(l);
	}
	e->hf = f;
	e->hc = c;
	e->super = (Node *)malloc(sizeof(Node));
	e->super_alpha = (Node *)malloc(sizeof(Node));
	e->super_alpha->next_alpha = NULL;
	e->numOfData = 0;
}

void putHT(TABLE *e, Body *bd)
{
	e->numOfData++;
	int valhash = e->hf(bd->key);
	LIST *pos = &(e->table[valhash]);

	Node *newNode = putList(pos, bd);

	if (e->super_alpha->next_alpha == NULL)
	{
		e->super_alpha->next_alpha = newNode;
	}
	else
	{
		Node *pre = e->super_alpha;
		Node *curAlpha = e->super_alpha->next_alpha;
		char *keyAlpha = newNode->data.key;
		char *keyCurAlpha;
		while (1)
		{
			keyCurAlpha = curAlpha->data.key;
			if (e->hc(keyCurAlpha, keyAlpha)) break;
			if ((curAlpha->next_alpha) == NULL)
			{
				pre = pre->next_alpha; break;
			}

			curAlpha = curAlpha->next_alpha;
			pre = pre->next_alpha;
		}

		newNode->next_alpha = pre->next_alpha;
		pre->next_alpha = newNode;
	}
}

Body *getHT(TABLE *e, char *lkey)
{
	int i = 0;
	int valhash = e->hf(lkey);
	LIST *pos = &(e->table[valhash]);
	if (pos->numOfData == 0) return NULL;

	Node *ffind = pos->head->next;
	while (i < (pos->numOfData))
	{
		if (!strcmp(lkey, ffind->data.key))
		{
			return &(ffind->data);
		}
		ffind = ffind->next;
		i++;
	}

	return NULL;
}


int countHT(TABLE *e)
{
	return e->numOfData;
}

int deleteHT(TABLE *e, char *lkey)
{
	int i = 0;
	int valhash = e->hf(lkey);
	LIST *pos = &(e->table[valhash]);
	if (pos->numOfData == 0) return 0;

	Node *pre = pos->head;
	Node *ffind = pos->head->next;
	while (i < (pos->numOfData))
	{
		if (!strcmp(lkey, ffind->data.key))
		{
			pre->next = ffind->next;
			free(ffind);
			e->numOfData--;
			pos->numOfData--;
			return 1;
		}
		ffind = ffind->next;
		pre = pre->next;
		i++;
	}

	return 0;
}

Body *searchHT(TABLE *e, char *find)
{
	int i = 0;
	LIST *pos = &(e->table[0]);
	for (i = 0; i < 1000; i++)
	{
		pos = &(e->table[i]);
		Node *search = pos->head->next;
		while (1)
		{
			if (powerCompare(search->data.key, find))
			{
				return &(search->data);
			}
			if (search->next == NULL) break;
			search = search->next;
		}
	}

	return NULL;
}

int hashString(char *str)
{
	int sum = 0;
	char *s = str;
	while (*s)
	{
		sum += *s;
		s++;
	}

	return sum % 1000;
}

int isNum(char ch)
{
	if (ch >= '0' && ch <= '9') return 1;
	return 0;
}


void decompressRLE(char *des, char *src)
{
	char *s = src;
	char result[300] = "";
	int num = 0;
	char ch;
	while (1)
	{
		ch = *s;
		s++;

		if (isNum(*s))
		{
			while (isNum(*s))
			{
				num *= 10;
				num += *s - '0';
				s++;
			}
			while (num)
			{
				num--;
				char onech[2] = { ch, '\0' };
				strcat(result, onech);
			}
		}
		else
		{
			char onech[2] = { ch, '\0' };
			strcat(result, onech);
		}

		if (*s == '\0') break;
	}

	strcat(des, result);
}

int alphaCompare(char *src, char *str)
{
	if (strcmp(src, str) < 0) return 0;
	return 1;
}

int powerCompare(char *src, char *com)
{
	char str[100] = "";
	decompressRLE(str, com);
	char *s = str;
	char *d = src;
	int is = 0;
	int ans = strlen(str);

	while (*s)
	{
		if (*s == '*')
		{
			char next = *(s + 1);
			d++; is++;
			while (*d != next)
			{
				if (*d == '\0') break;
				d++;
			}
			s++;
		}
		else
		{
			if (*s == *d)
			{
				is++;
			}
			s++;
			d++;
		}
	}

	if (is == ans) return 1;
	return 0;
}

void input(TABLE *e, char op, Body *data, FILE *outputFile, char *fileName)
{
	Body *sPos;
	Node *start;

	printf("[%c] ", op);
	switch (op)
	{
	case 'P':
		if (getHT(e, data->key) == NULL)
		{
			putHT(e, data);
			printf("%s\n", data->key);
		}
		else
		{
			printf("ERROR\n");
		}
		break;
	case 'G':
		sPos = getHT(e, data->key);
		if (sPos != NULL) printf("%d\n", sPos->value);
		else printf("ERROR\n");
		break;
	case 'C':
		printf("%d\n", countHT(e));
		break;
	case 'D':
		if (deleteHT(e, data->key)) printf("%s\n", data->key);
		else printf("ERROR\n");
		break;
	case 'F':
		start = e->super_alpha->next_alpha;
		while (start)
		{
			char *key = start->data.key;
			int value = start->data.value;
			fprintf(outputFile, "%s %d\n", key, value);
			start = start->next_alpha;
		}
		printf("%s\n", fileName);
		break;
	case 'S':
		sPos = searchHT(e, data->key);
		if (sPos != NULL)
		{
			printf("%d\n", sPos->value);
		}
		else
		{
			printf("NONE\n");
		}
		break;
	}
}

int main(int argc, char *argv[])
{
	char buf[300] = "";
	int data = 0;
	char FileName[300] = "";
	Body inputData;

	TABLE myHT;
	HTinit(&myHT, hashString, alphaCompare);
	if (argc == 1)
	{
		FILE *inputFile;
		FILE *outputFile;
		inputFile = fopen(argv[1], "r");

		while (fscanf(inputFile, "%s %d", buf, &data) != EOF)
		{
			inputData.key = buf;
			inputData.value = data;
			if (getHT(&myHT, inputData.key) == NULL)
			{
				putHT(&myHT, &inputData);
			}
		}
	}

	int N;
	char op;
	scanf("%d", &N);

	while (N--)
	{
		scanf(" %c", &op);
		switch (op)
		{
		case 'P':
			scanf("%s", buf);
			scanf("%d", &data);
			break;
		case 'G':
		case 'D':
		case 'S':
		case 'F':
			scanf("%s", FileName);
			outputFile = fopen(FileName, "w");
			break;
		case 'C':
			break;
		}


		inputData.key = buf;
		inputData.value = data;

		input(&myHT, op, &inputData, outputFile, FileName);
	}
	return 0;
}
