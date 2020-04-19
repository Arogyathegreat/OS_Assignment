#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream inp("hrrn.inp");
std::ofstream out("hrrn.out");

typedef struct Process { // will contain the process data from the input file
    int processNumber = 0;
    int arrivalTime = 0;
    int useTime = 0;
    double priorityNumber = 0;
};

void waitingTime(std::vector<Process> vec,
                 int processCount) { // calculates the total waiting time of the processes in the input file
    int time = vec[0].arrivalTime, wt = 0, tt = 0;

    for (int i = 0; i < processCount; i++) {

        Process i_process = vec[i];

        if (i_process.arrivalTime >= time) {
            wt = 0;
            time += i_process.arrivalTime - time;
        } else
            wt = time - i_process.arrivalTime;

        time += i_process.useTime;
        tt += wt;
    }
    out << tt;
}

bool sortingArrival(const Process &p1, const Process &p2) { // sorts the arrival and if equal sorts the process number
    if (p1.arrivalTime < p2.arrivalTime) return true;
    if (p1.arrivalTime > p2.arrivalTime) return false;

    return p1.processNumber < p2.processNumber;
}

bool sortingPriority(const Process &p1,
                     const Process &p2) { // sorts the priority rank and if equal sorts the arrival and process number if needed
    if (p1.priorityNumber > p2.priorityNumber) return true;
    if (p1.priorityNumber < p2.priorityNumber) return false;

    return sortingArrival(p1, p2);
}

int main() {

    std::vector<Process> processContainer; // vector containing all the processes

    int processCount; // total number of processes
    inp >> processCount;

    for (int i = 0; i < processCount; i++) {

        Process process;

        inp >> process.processNumber >> process.arrivalTime >> process.useTime;
        processContainer.push_back(process);
    }

    std::sort(processContainer.begin(), processContainer.begin() + processCount,
              sortingArrival); // first level sorting according to the arrival time and process number if needed

    int max = processCount, sum_useTime = 0;

    for (int i = 1; i < processCount; i++) { // from the second process

        if (processContainer[i - 1].arrivalTime >
            sum_useTime) // if the previous process' arrival time is after total use time of all processes
            sum_useTime += processContainer[i - 1].arrivalTime -
                           sum_useTime; // add the previous arrival time and reduce total time from that

        sum_useTime += processContainer[i - 1].useTime; // add the usetime of the previous process

        max = processCount;

        for (int j = i; j < processCount; j++) {
            if (sum_useTime <=
                processContainer[j].arrivalTime) { // if the current process' arrival time is greater or equal to the total usetime
                max = j; // max will be the storage for all the processes till then
                break;
            }

            Process *j_process = &processContainer[j];
            j_process->priorityNumber = (sum_useTime - j_process->arrivalTime + j_process->useTime)
                                        / (double) j_process->useTime;  // calculate priority rank
        }
        std::sort(processContainer.begin() + i, processContainer.begin() + max,
                  sortingPriority); // sort from current process to the process stored in max
    }

    waitingTime(processContainer, processCount); // calculate the waiting time

}
