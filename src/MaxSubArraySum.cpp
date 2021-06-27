#include<iostream>


#define DUMMY_VAR	-1			// dummy variable


// Assuming array starts from index = 1
// return max sub array sum

int MaxSubArraySum(int* A, int n)
{
	int globalStart = 1, globalEnd = 1;			// to store start and end of max sub array
	int* MaxSum = new int[n + 1];				// to store sum of max sub array end at ith index

	int globalSum = A[1];
	MaxSum[1] = A[1];
	
	for (int i = 2; i <= n; ++i) 
	{
		if (MaxSum[i - 1] + A[i] > A[i]) 
		{
			MaxSum[i] = MaxSum[i - 1] + A[i];
		}
		else 
		{
			MaxSum[i] = A[i];
			globalStart = i;				// update start of max sub array
		}
		if (globalSum < MaxSum[i]) 
		{
			globalSum = MaxSum[i];
			globalEnd = i;					// update end of max sub array
		}
	}

	// to print sub array that contains maximum sum
	std::cout << "Max Sum Sub Array: ";
	for (int i = globalStart; i <= globalEnd; ++i) {
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;

	return globalSum;
}


int main()
{
	int A[] = { DUMMY_VAR, 2, -4, 3, 4, -3, 5, -5, 6, -1 };
	int n = (sizeof(A) / sizeof(A[0])) - 1;		// -1 to ignore the length of dummy variable

	std::cout << "Max Sub Array Sum: " << MaxSubArraySum(A, n);
}
