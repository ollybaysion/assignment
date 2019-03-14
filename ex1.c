#include <stdio.h>

int max(int a, int b)
{
	return a >= b ? a : b;
}
int main()
{
	int a[3];
	int lcd;
	for(int i=0; i<3; i++)
	{
		scanf("%d", &a[i]);
		lcd = max(lcd, a[i]);
	}

	while(1)
	{
		int is = 1;
		for(int i=0; i<3; i++)
		{
			is = is && !(lcd % a[i]);
		}

		if(is) break;
		lcd++;
	}

	printf("%d\n", lcd);
}
