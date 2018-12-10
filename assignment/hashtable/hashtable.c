#include "project.h"
#include "hashtable.h"

// for hash List in hash table.
void ListInit(LIST *k)
{
	k->head = (Node *)malloc(sizeof(Node));
	k->cur = k->head;
	k->numOfData = 0;
}

void putList(LIST *k, Body *bd)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	int len = strlen(bd->key);
	newNode->data->key = (char *)malloc(sizeof(char) * (len+1));
	strcpy(newNode->data->key, bd->key);
	newNode->data->value = bd->value;

	k->cur->next = newNode;
	k->cur = k->cur->next;
	k->numOfData++;
}

// for hash table
void HTinit(TABLE *e, HashFunc *f, HashComp *c)
{
	e->table = (LIST *)malloc(sizeof(LIST) * HASH_LEN);
	e->hf = f;
	e->hc = c;
	e->super = (Node *)malloc(sizeof(Node));
	e->super_alpha = (Node *)malloc(sizeof(Node);
	e->super_alpha->next = NULL;
	e->numOfData = 0;
}

void putHT(TABLE *e, Body *bd)
{
	e->numOfData++;
	int valhash = hf(bd->key);
	LIST *pos = e->table[valhash];

	if(pos == NULL)
	{
		ListInit(pos);
	}

	putList(pos, bd);

	Node *cural = e->super_alpha->next_alpha;
	while(hc(cural->data->key, bd->key)) cural = cural->next_alpha;
	pos->cur->next_alpha = cural->next_alpha;
	cural->next_alpha = pos->cur;
}

Body *getHT(TABLE *e, char *lkey)
{
	int valhash = hf(lkey);
	LIST *pos = e->table[valhash];
	Node *ffind = pos->head->next;

	while(ffind != NULL)
	{
		if(strcmp(lkey, ffind->data->key)) return &(ffind->data);
		ffind = ffind->next;
	}

	return NULL;
}
