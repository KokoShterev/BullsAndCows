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
	int computerNumber = possibleNumbers[rand() % c], myGuess;
//	printf ("computerNumber = %i\n", computerNumber);
	while (1)
	{
		turns++;
		int currentBulls = 0, currentCows = 0;
		printf("Make your guess\n");
		scanf("%i", &myGuess);
		findBullsAndCows(computerNumber, myGuess, &currentBulls, &currentCows);
		if (currentBulls == 4)
		{
			printf("You won in %i turns! My number is %i\n", turns, computerNumber);
			break;
		}
		else
		{
			printf("You have %i bulls and %i cows\n", currentBulls, currentCows);
		}
		if (c == 1)
		{
			printf("I won in %i turns! Your number is %i\n", turns, possibleNumbers[0]);
			break;
		}
		else if (c == 0)
		{
			printf("You lied!");
			break;
		}
		int supposed = possibleNumbers[rand() % c];
		printf("Computer's guess is %i\nBulls & Cows in format bc\n", supposed);
		int bcAnswer;
		scanf("%i", &bcAnswer);
		int bulls = bcAnswer / 10;
		int cows = bcAnswer % 10;
		if (bulls == 4)
		{
			printf("I won in %i turns!\n", turns);
			break;
		}
		int newPossibleNumbers[c], c1 = 0;
		for (int i = 0; i < c; i++)
		{
			currentBulls = 0;
			currentCows = 0;
			findBullsAndCows(possibleNumbers[i], supposed, &currentBulls, &currentCows);
			if (currentBulls == bulls && currentCows == cows)
				newPossibleNumbers[c1++] = possibleNumbers[i];
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
	}
	return 0;
}