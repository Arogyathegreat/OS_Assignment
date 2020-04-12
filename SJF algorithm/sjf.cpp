#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

FILE* input_fp, * output_fp;

typedef vector<int> process; // a simple structure for containing process data
// 0: process number 1: arrival time 2: cpu usage time

void waitingTime(vector<process> vec, int processCount)
{
	int time = vec[0][1], wt = 0, tt = 0;//our starting time will be the first arrival time
	// waiting time and total time, wt for each iteration tt for total
	for (int i = 0; i < processCount; i++)
	{
		if (vec[i][1] >= time)// if the arrival is after all the processes are done
		{
			wt = 0;
			time += vec[i][1] - time;
		}
		else wt = time - vec[i][1];

		time += vec[i][2];
		tt += wt;
	}

	fprintf(output_fp, "%d", tt);
}

vector<process> sorting(vector<process> storeVector, int processCount) // function for sorting
{
	sort(storeVector.begin(), storeVector.end(), [](const std::vector< int >& a, const std::vector< int >& b) { return a[1] < b[1]; }); // sorting for arrival first

	int maxCount = processCount, useTime = 0;


	for (int i = 1; i < processCount; i++)
	{
		useTime += storeVector[i - 1][2];
		int j;
		for (j = i; j < processCount; j++)
		{
			if (useTime < storeVector[j][1])
			{
				maxCount = j;
				break;
			}
		}
		if (j == processCount)
			maxCount = processCount;
		sort(storeVector.begin() + i, storeVector.begin() + maxCount, [](const std::vector< int >& a, const std::vector< int >& b) { return a[2] < b[2]; }); // sorting for usage
	}
	return storeVector;
}

int main()
{
	if ((input_fp = fopen("sjf.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "sjf.inp");
	}
	if ((output_fp = fopen("sjf.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "sjf.out");
	}

	int processCount;//number of processes to be added

	vector<process> storeVector;//vector containing all the processes

	fscanf(input_fp, "%d", &processCount);


	for (int i = 0; i < processCount; i++)
	{
		process process;
		for (int j = 0; j < 3; j++)
		{
			int temp = 0;
			fscanf(input_fp, "%d", &temp);
			process.push_back(temp);// process number, arrival and usage time are added
		}
		storeVector.push_back(process);// the process is then appended to storeVector
	}
	
	waitingTime(sorting(storeVector, processCount) , processCount);// sorts and computes waiting time
}