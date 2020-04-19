//
// Created by arogya.Gurkha on 2020-04-19.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define _min 21000000

std::ifstream inp("srtf.inp");
std::ofstream out("srtf.out");

typedef struct Process { // will contain the process data from the input file
    int processNumber = 0;
    int arrivalTime = 0;
    int useTime = 0;
    int waitTime = 0; // later when the process might need to wait
};

bool sortingArrival(const Process &p1, const Process &p2) {

    if (p1.arrivalTime < p2.arrivalTime) return true; // first sort by arrival
    if (p1.arrivalTime > p2.arrivalTime) return false;

    if (p1.useTime < p2.useTime) return true; // second by use time
    if (p1.useTime > p2.useTime) return false;

    return p1.processNumber < p2.processNumber; // and lastly with process number
}

void calculation(std::vector<Process> &vec, int count) {

    int processID = -1, r_process = count; // current processID and remaining process

    for (int i = 0; r_process > 0; i++) {
        std::sort(vec.begin(), vec.end(), sortingArrival);
        int min = _min; // smallest use time

        for (int j = 0; j < count; j++) {
            Process *c_process = &vec[j]; // current process
            if (c_process->arrivalTime > i) break; // if the current process arrives later than current time then break
            if (c_process->useTime > 0 && c_process->arrivalTime <= i) { // if there is time left in the process and arrival time is in present
                if (min > c_process->useTime) { // check if the current process' use time is the min
                    min = c_process->useTime; // if yes then the min is current process
                    processID = j; // save the current process id in processID
                }
            }
        }
        if (processID != -1) { // if the processID is valid
            vec[processID].useTime--; // then reduce the use time by 1
            if (vec[processID].useTime == 0) // check if use time is 0 for the process
                r_process--; // if yes then that process can be removed
        }
        for (int j = 0; j < count; j++) {
            if (j != processID && vec[j].arrivalTime <= i && vec[j].useTime > 0) // j is a process that is selected if it fits all the criteria
                vec[j].waitTime++; // then increase the waiting time for j
        }
    }
}

int main() {

    std::vector<Process> processContainer;

    int processCount;
    inp >> processCount;

    int totalTime = 0, sum_waitTime = 0; // total time taken by all the processes

    for (int i = 0; i < processCount; i++) {
        Process process;
        inp >> process.processNumber >> process.arrivalTime >> process.useTime;

        if (totalTime < process.arrivalTime)
            totalTime += process.arrivalTime - totalTime;

        totalTime += process.useTime;

        processContainer.push_back(process); // get data from the input file and store them all in a vector
    }

    calculation(processContainer, processCount);

    for (int i = 0; i < processCount; i++)
        sum_waitTime += processContainer[i].waitTime; // add all the wait times to get the final answer

    out << sum_waitTime;
}
