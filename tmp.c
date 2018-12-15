#include <stdio.h>

#define swap(a, b); (a) = (a) ^ (b); (b) = (a) ^ (b); (a) = (a) ^ (b);
int main()
{
	int T;
	scanf("%d", &T);
	for (int repeat = 1; repeat <= T; repeat++)
	{
		int num[10];
		char buf[10];
		int digit = 0;
		int change;
		int ans = 0;

		scanf("%s", buf);

		char *s = buf;
		while (*s)
		{
			num[digit] = *s - '0';
			digit++;
			s++;
		}
		scanf("%d", &change);

		int maxIdx;
		for (int i = 0; change && i<digit; i++)
		{
			maxIdx = i;
			for (int j = digit; j > i; j--)
			{
				if (num[maxIdx] < num[j]) maxIdx = j;
			}

			if (maxIdx != i)
			{
				swap(num[i], num[maxIdx]);
				change--;
			}
		}

		for (int i = 0; i < digit; i++)
		{
			ans *= 10;
			ans += num[i];
		}

		printf("#%d %d\n", repeat, ans);
	}
}
