#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

FILE* input_fp, * output_fp;

typedef vector<int> process; // a simple structure for containing process data
// 0: process number 1: arrival time 2: cpu usage time

bool sortingFunction(const vector<int>& v1, const vector<int>& v2) // sorting function for std::sort
{
	if (v1[1] < v2[1]) return true;
	if (v1[1] > v2[1]) return false;

	if (v1[0] < v2[0])return true;
	if (v1[0] > v2[0])return false;
}

void waitingTime(vector<process> vec, int processCount)
{
	int time = vec[0][1], wt = 0, tt = 0; //our starting time will be the first arrival time
	// waiting time and total time, wt for each iteration tt for total

	for(int i = 0; i<processCount; i++)
	{
		if (vec[i][1] >= time) // if the arrival is after all the processes are done
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

int main()
{
	if ((input_fp = fopen("fcfs.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "data.inp");
	}
	if ((output_fp = fopen("fcfs.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "fcfs.out");
	}

	int processCount; //number of processes to be added

	vector<process> storeVector; //vector containing all the processes

	fscanf(input_fp, "%d", &processCount);


	for (int i = 0; i < processCount; i++)
	{
		process process;
		for (int j = 0; j < 3; j++)
		{
			int temp = 0;
			fscanf(input_fp, "%d", &temp);
			process.push_back(temp); // process number, arrival and usage time are added
		}
		storeVector.push_back(process); // the process is then appended to storeVector
	}

	sort(storeVector.begin(), storeVector.end(), sortingFunction); // sorts with arrival time and process number (if necessary)

	waitingTime(storeVector, processCount);
}