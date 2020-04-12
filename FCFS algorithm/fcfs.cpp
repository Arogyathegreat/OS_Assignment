#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

FILE* input_fp, * output_fp;

typedef vector<int> process;

bool sortingFunction(const vector<int>& v1, const vector<int>& v2)
{
	if (v1[1] < v2[1]) return true;
	if (v1[1] > v2[1]) return false;

	if (v1[0] < v2[0])return true;
	if (v1[0] > v2[0])return false;
}

void waitingTime(vector<process> vec, int processCount)
{
	int time = vec[0][1], wt = 0, tt = 0;
	for(int i = 0; i<processCount; i++)
	{
		if (vec[i][1] >= time)
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

	int processCount;

	vector<process> storeVector;

	fscanf(input_fp, "%d", &processCount);


	for (int i = 0; i < processCount; i++)
	{
		process process;
		for (int j = 0; j < 3; j++)
		{
			int temp = 0;
			fscanf(input_fp, "%d", &temp);
			process.push_back(temp);
		}
		storeVector.push_back(process);
	}

	sort(storeVector.begin(), storeVector.end(), sortingFunction);

	waitingTime(storeVector, processCount);
}