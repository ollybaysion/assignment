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
void input(TABLE *e, char op, Body *data);

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
int isAlpha(char ch);
int isNum(char ch);
int numToString(char *des, int src);

void addRLE(char *des, char ch, int len);
void pullRLE(char *des, char *src, int first, int last);
int searchRLE(char *src, char *cmp);
void deleteRLE(char *src, int first, int last);
void insertRLE(char *src, char *str, int idx);
int RLEinfo(char *src, char *dch, int *dlen);
int RLElen(char *src);
void optimizeRLE(char *src);

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

int isAlpha(char ch)
{
	if (ch >= 'a' && ch <= 'z') return 1;
	if (ch >= 'A' && ch <= 'Z') return 1;
	return 0;
}

int numToString(char *des, int src)
{
	int d[10];
	int len;
	for (len = 0; src; len++)
	{
		d[len] = src % 10;
		src /= 10;
	}
	for (int i = len; i > 0; i--)
	{
		*des++ = d[i - 1] + '0';
	}
	*des = '\0';
	return len;
}

void addRLE(char *des, char ch, int len)
{
	char num[10];
	char onechar[2] = { ch, '\0' };
	numToString(num, len);
	strcat(des, onechar);
	strcat(des, num);
}

void pullRLE(char *des, char *src, int first, int last)
{
	char chs[MAX_WORD];
	int lens[MAX_WORD];
	int cnt = RLEinfo(src, chs, lens);

	int idx = 0;
	int num = 0;
	int sum = lens[0];

	while (first > sum)
	{
		idx++;
		sum += lens[idx];
	}
	for (int cur = first; cur <= last; cur++)
	{
		num++;
		if (cur == sum || cur == last)
		{
			if (num) addRLE(des, chs[idx], num);
			idx++;
			sum += lens[idx];
			num = 0;
		}
	}
}

int searchRLE(char *src, char *cmp)
{
	int len_src = RLElen(src);
	int len_cmp = RLElen(cmp);
	for (int i = 1; i <= len_src - len_cmp + 1; i++)
	{
		char tmp[300] = "";
		pullRLE(tmp, src, i, i + len_cmp - 1);
		if (!strcmp(cmp, tmp)) return i;
	}

	return 0;
}

void deleteRLE(char *src, int first, int last)
{
	char str1[100] = "";
	char str2[100] = "";
	char buf[300] = "";

	pullRLE(str1, src, 1, first - 1);
	pullRLE(str2, src, last + 1, RLElen(src));

	strcat(buf, str1);
	strcat(buf, str2);
	strcpy(src, buf);

	optimizeRLE(src);
}

void insertRLE(char *src, char *str, int idx)
{
	char str1[100] = "";
	char str2[100] = "";
	char buf[100] = "";

	pullRLE(str1, src, 1, idx);
	pullRLE(str2, src, idx + 1, RLElen(src));

	strcat(buf, str1);
	strcat(buf, str);
	strcat(buf, str2);
	strcpy(src, buf);
	optimizeRLE(src);
}

int RLEinfo(char *src, char *dch, int *dlen)
{
	char *ch = dch; int *len = dlen;
	while (*src)
	{
		*len = 0;
		if (isAlpha(*src))
		{
			*ch = *src;
			ch++; src++;
		}
		while (isNum(*src))
		{
			*len *= 10;
			*len += *src++ - '0';
			if (isAlpha(*src) || !(*src)) len++;
		}
	}
	*ch = '\0';
	return (ch - dch) / sizeof(char);
}

int RLElen(char *src)
{
	char ch[MAX_WORD];
	int len[MAX_WORD];
	int cnt = RLEinfo(src, ch, len);
	int sum = 0;
	for (int i = 0; i < cnt; i++) sum += len[i];
	return sum;
}

void optimizeRLE(char *src)
{
	char ch[MAX_WORD];
	int len[MAX_WORD];
	int cnt = RLEinfo(src, ch, len);

	char buf[300] = "";
	char nch[10];
	int nlen[10];
	int j = 0;

	nch[0] = ch[0];
	nlen[0] = len[0];
	for (int i = 1; i < cnt; i++)
	{
		if (ch[i] != ch[i - 1])
		{
			j++;
			nch[j] = ch[i];
			nlen[j] = len[i];
		}
		else
		{
			nlen[j] += len[i];
		}
	}

	for (int i = 0; i <= j; i++)
	{
		addRLE(buf, nch[i], nlen[i]);
	}
	strcpy(src, buf);
}

// ab
// ab

int alphaCompare(char *src, char *str)
{
	if (strcmp(src, str) < 0) return 0;
	return 1;
}

int powerCompare(char *src, char *str)
{
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

void input(TABLE *e, char op, Body *data, FILE *outputFile)
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
		start = e->super_alpha;
		while (start)
		{
			char *key = start->data.key;
			int value = start->data.value;
			fprintf(outputFile, "%s %d\n", key, value);
			start = start->next_alpha;
		}
	}
}

int main(int argc, char *argv)
{
	FILE *inputFile;
	FILE *outputFile;
	inputFile = fopen(argv[1], "r");
	char buf[300] = "";
	int data = 0 = ""; 
	char FileName[300];
	Body inputData; 

	TABLE myHT;
	HTinit(&myHT, hashString, alphaCompare);

	while (fscanf(inputFile, "%s %d", buf, &data) != EOF)
	{
		inputData.key = buf;
		inputData.value = data;
		if (getHT(&myHT, inputData.key) == NULL)
		{
			putHT(&myHT, &inputData);
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

		input(&myHT, op, &inputData, outputFile);
	}

	return 0;
}
