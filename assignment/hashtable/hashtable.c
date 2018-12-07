#include "project.h"
#include "hashtable.h"

// for hash List in hash table.
void ListInit(LIST *k)
{
	k->head = NULL;
	k->cur = NULL;
	k->numOfData = 0;
}

void putList(LIST *k, Body *bd)
{
	k->head->
}

// for hash table
void HTinit(TABLE *e, HashFunc *f, HashComp *c)
{
	e->table = (LIST *)malloc(sizeof(LIST) * HASH_LEN);
	e->hf = f;
	e->hc = c;
	e->super = NULL;
	e->super_alpha = NULL;
	e->numOfData = 0;
}

void putHT(TABLE *e, Body * bd)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data->key = malloc(sizeof(char) * (strlen(lkey) + 1));
	strcat(newNode->data->key, lkey);
	newNode->data->value = lvalue;

	int h = e->hf(lkey);
	if(e->table[h] == NULL)
	{
		e->table[h] = newNode;
	}
	else
	{
		Node *tmp = e->table[h];
		while(tmp->next != NULL) tmp = tmp->next;

		tmp->next = e->table[h];
	}
}
