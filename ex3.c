#include <stdio.h>

int main()
{
	int weight;
	int numOfBox = 0;

	while(1)
	{
		printf("Input the weight of the egg = ");
		scanf("%d", &weight);
		if(weight > 300) numOfBox++;
		printf("I have %d eggs in my eggBox!\n", numOfBox);
		if(numOfBox == 30) break;
	}

	printf("The eggbox is full!\n");
}
