int search(char *src, char *str)
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
