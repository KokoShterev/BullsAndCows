#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void findBullsAndCows(int n1, int n2, int *bulls, int *cows)
{
	char n1str[5] = {0}, n2str[5] = {0};
	sprintf(n1str, "%i", n1);
	sprintf(n2str, "%i", n2);
	for (int i = 0; i < 4; i++)
	{
		if (n1str[i] == n2str[i])
			(*bulls)++;
		else if (strchr(n1str, n2str[i]))
			(*cows)++;
	}
}

int main()
{
	int possibleNumbers[9 * 9 * 8 * 7] = {0}, c = 0, turns = 0;
	for (int i = 1023; i < 9877; i++)
	{
		char itos[5];
		sprintf(itos, "%i", i);
		if (itos[0] != itos[1] && itos[0] != itos[2] &&
			itos[0] != itos[3] && itos[1] != itos[2] &&
			itos[1] != itos[3] && itos[2] != itos[3])
		{
			possibleNumbers[c] = i;
			c++;
		}
	}
	srand((unsigned) time(0));
	while (c > 1)
	{
		turns++;
		int supposed = possibleNumbers[rand() % c];
		printf("%i\nBulls & Cows in format bc\n", supposed);
		int bcAnswer;
		scanf("%i", &bcAnswer);
		int bulls = bcAnswer / 10;
		int cows = bcAnswer % 10;
		if (bulls == 4)
		{
			printf("I won in %i turns!", turns);
			break;
		}
		int newPossibleNumbers[c], c1 = 0;
		for (int i = 0; i < c; i++)
		{
			int currentBulls = 0, currentCows = 0;
			findBullsAndCows(possibleNumbers[i], supposed, &currentBulls, &currentCows);
			if (currentBulls == bulls && currentCows == cows)
			{
				newPossibleNumbers[c1] = possibleNumbers[i];
				c1++;
			}
		}
		memset(possibleNumbers, 0, c * sizeof(int));
		for (int i = 0; i < c1; i++)
			possibleNumbers[i] = newPossibleNumbers[i];
		printf("Deleted %i numbers\n", c - c1);
		printf("Remaining %i numbers\n", c1);
		c = c1;
		if (c > 1 && c < 10)
		{
			printf("The Possible Numbers are ");
			for (int i = 0; i < c; i++)
				printf("%i ", possibleNumbers[i]);
			printf("\n");
		}
		if (c == 1)
			printf("I won in %i turns! Your number is %i\n", turns + 1, possibleNumbers[0]);
		else if (c == 0)
			printf("You lied!");
	}
	return 0;
}