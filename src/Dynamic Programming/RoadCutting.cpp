#include<iostream>
#include<queue>

#define DUMMY_VAR -1			// dummy variable
 
// to get maximum revenue for rod of length n
// p is an array that contains price for each length of road
// n is the length of the rod
// T(n) = O(2^N)
int rod_cutting_recursive(int* prices, int n) 
{
	if (n == 0)
	{
		return 0;
	} 

	int max_revenue = INT_MIN;
	for (int i = 1; i <= n; ++i)
	{
		max_revenue = std::max(max_revenue, prices[i] + rod_cutting_recursive(prices, n - i));
	}
	return max_revenue;
}








// to get maximum revenue for rod of length n
// p is an array that contains price for each length of road
// n is the length of the rod
// T(n) = O(N^2)
int rod_cutting(int* prices, int n) 
{
	int* revenues = new int[n + 1];							// to store optimal revenue for rod of each length
	revenues[0] = 0;
	int max_revenue = INT_MIN;
	for (unsigned int i = 1; i <= n; i++) 
	{
		// check for possible combination and get the maximum one
		for (unsigned int j = 1; j <= i; ++j)
		{
			max_revenue = std::max(max_revenue, prices[j] + revenues[i - j]);
		}
		revenues[i] = max_revenue;
	}

	if (revenues) delete[] revenues;
	return max_revenue;
}





// to get cuttings
std::queue<int> cutting(int* cuttingList, int n)
{
	int iterator = n;
	std::queue<int> cuttings_que;
	while (iterator >= 0 && cuttingList[iterator] != -1)
	{
		cuttings_que.push(cuttingList[iterator]);
		iterator -= cuttingList[iterator];
	}
	return cuttings_que;
}



// to get maximum revenue for rod of length n and partitions list as well.
// prices is an array that contains price for each length of road
// n is the length of the rod
// T(n) = O(n^2)
int rod_cutting(int* prices, std::queue<int>& cutting_que, int n)
{
	int* revenues = new int[n + 1];							// to store optimal revenue for rod of each length
	int* cuttingList = new int[n + 1];						// to keep record of optimal cuttings for rod of each length 
	cuttingList[0] = -1;
	revenues[0] = 0;
	int max_revenue = INT_MIN;
	for (unsigned int i = 1; i <= n; i++)
	{
		// check for possible combination and get the maximum one
		for (unsigned int j = 1; j <= i; ++j)
		{
			int temp_max = prices[j] + revenues[i - j];
			if (temp_max > max_revenue)
			{
				max_revenue = temp_max;
				cuttingList[i] = j;
			}
		}
		revenues[i] = max_revenue;
	}
	cutting_que = cutting(cuttingList, n);
	
	if (revenues) delete[] revenues;
	if (cuttingList) delete[] cuttingList;

	return max_revenue;
}



int main()
{
	int prices[] = { DUMMY_VAR,  1, 5, 8, 9, 10, 17};
	int n = sizeof(prices) / sizeof(prices[0]) - 1;			// - 1 to ignore the length of dummy varibale
	std::queue<int> cutting_que;			// to get cuttings

	// maximum revenue
	std::cout << "Recursive: Max Revenue[" << n << "] = " << rod_cutting(prices, n) << std::endl;
	std::cout << "DP: Max Revenue[" << n << "] = " << rod_cutting(prices, cutting_que, n) << std::endl;

	// to print cuttings
	std::cout << "Cuttings: ";
	while (!cutting_que.empty())
	{
		std::cout << cutting_que.front() << " ";
		cutting_que.pop();
	}
	return 0;
}
