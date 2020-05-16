#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void splitNumbers(int numbers[], int n)
{
	for (int i = 3; i >= 0; i--)
	{
		numbers[i] = n % 10;
		n /= 10;
	}
}

int findBulls(int n1, int n2)
{
	int bulls = 0, n1arr[4] = {0}, n2arr[4] = {0};
	splitNumbers(n1arr, n1);
	splitNumbers(n2arr, n2);
	for (int i = 0; i < 4; i++)
	{
		if (n1arr[i] == n2arr[i])
			bulls++;
	}
	return bulls;
}

int findCows(int n1, int n2)
{
	int cows = 0, n1arr[4] = {0}, n2arr[4] = {0};
	splitNumbers(n1arr, n1);
	splitNumbers(n2arr, n2);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				continue;
			if (n1arr[i] == n2arr[j])
				cows++;
		}
	}
	return cows;
}

int main()
{
	int possibleNumbers[9 * 9 * 8 * 7] = {0}, c = 0, turns = 0;
	for (int i = 1023; i < 9877; i++)
	{
		int currentNumber[4] = {0};
		splitNumbers(currentNumber, i);
		if (currentNumber[0] != currentNumber[1] && currentNumber[0] != currentNumber[2] &&
			currentNumber[0] != currentNumber[3] && currentNumber[1] != currentNumber[2] &&
			currentNumber[1] != currentNumber[3] && currentNumber[2] != currentNumber[3])
		{
			possibleNumbers[c] = i;
			c++;
		}
	}

	srand((unsigned) time(0));
	while (1)
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
			int currentBuls = findBulls(possibleNumbers[i], supposed);
			int currentCows = findCows(possibleNumbers[i], supposed);
			if (currentBuls == bulls && currentCows == cows)
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
		{
			printf("I won in %i turns! Your number is %i\n", turns + 1, possibleNumbers[0]);
			break;
		}
		if (c == 0)
		{
			printf("You lied!");
			break;
		}
	}
	return 0;
}