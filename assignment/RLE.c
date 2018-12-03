#include "project.h"
#include <string.h>

// RLE functions
/*
 * If you use sscanf, sprintf, you can implement these functoins more easily.
 */

#define MAX_WORD 10

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
		*des++ = d[i-1] + '0';
	}
	*des = '\0';
	return len;
}

void addRLE(char *des, char ch, int len)
{
	char num[10];
	char onechar[2] = {ch, '\0'};
	numToString(num, len);
	strcat(des, onechar);
	strcat(des, num);
}

void pullRLE(char *des, char *src, int first, int last)
{
	char chs[MAX_WORD];
	int lens[MAX_WORD];
	int cnt = toString(src, chs, lens);

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
		if(cur == sum || cur == last)
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
	for (int i = 1;  i <= len_src - len_cmp + 1; i++)
	{
		char tmp[300] = "";
		pullRLE(tmp, src, i, i+len_cmp - 1);
		if (!strcmp(cmp, tmp)) return i;
	}

	return 0;
}

void deleteRLE(char *src, int first, int last)
{
	char str1[100] = "";
	char str2[100] = "";
	char buf[300] = "";

	pullRLE(str1, src, 1, first-1);
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
	while(*src)
	{
		*len = 0;
		if (isAlpha(*src))
		{
			*ch = *src;
			ch++; src++;
		}
		while(isNum(*src))
		{
			*len *= 10;
			*len += *src++ - '0';
			if(isAlpha(*src) || !(*src)) len++;
		}
	}
	*ch = '\0';
	return (ch - dch) / sizeof(char);
}

int RLElen(char *src)
{
	char ch[MAX_WORD];
	int len[MAX_WORD];
	int cnt = toString(src, ch, len);
	int sum = 0;
	for(int i = 0; i < cnt; i++) sum += len[i];
	return sum;
}

void optimizeRLE(char *src)
{
	char ch[MAX_WORD];
	int len[MAX_WORD];
	int cnt = toString(src, ch, len);

	char buf[300] = "";
	char nch[10];
	int nlen[10];
	char onech;
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

	for (int i = 0; i<= j; i++)
	{
		addRLE(buf, nch[i], nlen[i]);	
	}
	strcpy(src, buf);
}
