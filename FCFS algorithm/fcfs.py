import operator  # operator for sorting


# creating a simple class structure for incoming data about processes
class Process:
    def __init__(self, number, arrival, duration):
        self.number = number  # process number
        self.arrival = arrival  # process arrival time
        self.duration = duration  # process cpu usage duration

    def __str__(self):
        return str(self.__class__) + ": " + str(self.__dict__)


def waiting_time(container, count):
    # our starting time will be the first arrival time
    time = container[0].arrival
    # waiting time and total time, wt for each iteration tt for total
    wt, tt = 0, 0

    for i in range(count):
        proc = container[i]  # taking a process from the process container

        if proc.arrival >= time:  # if the arrival time is after the process is done
            wt = 0
            time += proc.arrival - time
        else:
            wt = time - proc.arrival

        time += proc.duration
        tt += wt

    return tt


if __name__ == '__main__':

    output_fp = open('fcfs.out', 'w')

    processes, answer = [], 0
    # processes[] will contain all the incoming processes,
    # answer is the final answer we will print

    with open('fcfs.inp') as input_fp:

        process_count = int(input_fp.readline())  # reads the first line which contains the process count

        for line in input_fp:
            data = line.split()
            num, arr, dur = map(int, line.split())
            processes.append(Process(num, arr, dur))  # the incoming data is divided into three parts

        # sorting based on arrival time and if needed process number
        processes.sort(key=operator.attrgetter('arrival', 'number'))

        answer = waiting_time(processes, process_count)
        output_fp.write(str(answer))

    output_fp.close()
