#
# Created by arogya.Gurkha on 2020-04-19.
#
import operator


class Process:
    def __init__(self, process_number, arrival_time, use_time,
                 waiting_time):  # will contain the process data from the input file
        self.process_number = process_number
        self.arrival_time = arrival_time
        self.use_time = use_time
        self.waiting_time = waiting_time  # later when the process might need to wait


def calculation(container, count):
    process_id, r_process, sum_wait_time = -1, count, 0  # current process id, remaining processes, total waiting time
    i = 0
    while r_process > 0:  # if there are processes left to be processed
        container.sort(key=operator.attrgetter('arrival_time', 'use_time',
                                               'process_number'))  # sort with arrival time, use time and process num
        min_time = 2100000  # min time for processing

        for j in range(0, count):
            if container[j].arrival_time > i:  # if the process arrives too late
                break
            if container[j].use_time > 0 and container[j].arrival_time <= i:
                # if the process still needs time and has already arrived
                if min_time > container[j].use_time:
                    min_time = container[j].use_time  # change the small amount of time
                    process_id = j  # current iteration will be the process to have its use time reduced

        if process_id != -1:  # if the process is valid
            container[process_id].use_time -= 1  # then reduce the use time
            if container[process_id].use_time == 0:  # if the process is finished then reduce the number of process
                r_process -= 1

        for j in range(0, count):
            if j != process_id and container[j].arrival_time <= i and container[j].use_time > 0:
                # if the current iteration isn't the current process, if the process has already arrived and
                # still needs to be processed
                container[j].waiting_time += 1  # increase the waiting time

        i += 1  # increase the time by 1

    for i in range(0, count):
        sum_wait_time += container[i].waiting_time  # add all the waiting times

    return sum_wait_time


if __name__ == '__main__':
    process_container = []
    with open('srtf.inp') as inp, open('srtf.out', 'w') as out:

        process_count = int(inp.readline())

        for line in inp:
            num, arr, dur = map(int, line.split())
            process_container.append(Process(num, arr, dur, 0))

        out.write(str(calculation(process_container, process_count)))  # output
