#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int binarySearch(int * mass, int value, int size);

int main(int argc, char **argv)
{
	int idx = 0;
	int search = 0;
	int mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	cout << "Enter search element: ";
	cin >> search;

	idx = binarySearch(mass, search, sizeof(mass) / sizeof(int));

	if (idx == -1)
	{
		cout << "Element was not find" << endl;
	}
	else
	{
		cout << "Index of element: " << idx << endl;
	}

	return 0;
}

int binarySearch(int * mass, int value, int size)
{
	int low = 0;
	int high = size - 1;

	while (low <= high)
	{
		int mid = (low + high) / 2;
		int sugess = mass[mid];

		if (sugess == value)
		{
			return mid;
		}

		if (sugess < value)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return -1;
}