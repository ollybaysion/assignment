#include <stdio.h>
#include "project.h"

/*
 * this is for test RLE functions.
 * If you want to check if RLE functions work properly,
 * please use this.
 */

int main()
{
	char src[300]  = "";
	char delStr[100] = "";
	char insert[100] = "";
	int ta, tb, tc;
	char ch;
	int num;

	char chs[10];
	int lens[10];

	scanf("%d %d %d", &ta, &tb, &tc);
	while (ta--) { scanf(" %c %d", &ch, &num); addRLE(src, ch, num); }
	while (tb--) { scanf(" %c %d", &ch, &num); addRLE(delStr, ch, num); }
	while (tc--) { scanf(" %c %d", &ch, &num); addRLE(insert, ch, num); }

	int search = searchRLE(src, delStr);
	int len_del = RLElen(delStr);
	while(search)
	{
		deleteRLE(src, search, search + len_del - 1);
		insertRLE(src, insert, search - 1);
		optimizeRLE(src);
		search = searchRLE(src, delStr);
	}

	int cnt = RLEinfo(src, chs, lens);
	for (int i = 0; i < cnt; i++)
	{
		if(i == cnt - 1) { printf("%c %d", chs[i], lens[i]); break; }
		printf("%c %d ", chs[i], lens[i]);
	}
	printf("\n");
	
	return 0;
}
