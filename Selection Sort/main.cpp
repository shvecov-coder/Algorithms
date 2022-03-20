#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const int NUMBER = 10;

void printMass(int * mass, int size);
void selectionSort(int * mass, int size);

int main(int argc, char **argv)
{
	int mass[NUMBER] = {0};

	for (int i = 0; i < NUMBER; i++)
	{
		mass[i] = rand() % NUMBER + 1;
	}

	cout << "not sort mass = ";
	printMass(mass, NUMBER);
	selectionSort(mass, NUMBER);

	cout << "sort mass = ";
	printMass(mass, NUMBER);

	return 0;
}

void selectionSort(int * mass, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min_idx = i;

		for (int j = i + 1; j < size; j++)
		{
			if (mass[j] < mass[min_idx])
			{
				min_idx = j;
			}
		}

		if (min_idx != i)
		{
			int temp = mass[i];
			mass[i] = mass[min_idx];
			mass[min_idx] = temp;
		}
	}
}

void printMass(int * mass, int size)
{
	cout << "[";
	for (int i = 0; i < size; i++)
	{
		if (i == size - 1)
		{
			cout << mass[i];
		}
		else
		{
			cout << mass[i] << ", ";
		}
	}
	cout << "];" << endl;
}