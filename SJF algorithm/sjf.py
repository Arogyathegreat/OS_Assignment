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


def sorting(container, count):  # for sorting with arrival and later with the duration

    container.sort(key=operator.attrgetter('arrival'))  # sorting for arrival first
    max_count, use_time, j = count, 0, 0

    for i in range(1, count):

        use_time += container[i - 1].duration

        max_count = count
        for j in range(i, count):
            print(j)
            if use_time < container[j].arrival:
                max_count = j
                break

        # then sorting for duration
        container[0 + i: 0 + max_count] = sorted(container[0 + i: 0 + max_count], key=operator.attrgetter('duration'))

    return container


if __name__ == '__main__':

    processes, answer = [], 0

    with open('sjf.inp') as input_fp, open('sjf.out', 'w') as output_fp:

        process_count = int(input_fp.readline())  # reads the first line which contains the process count

        for line in input_fp:
            num, arr, dur = map(int, line.split())
            processes.append(Process(num, arr, dur))  # the incoming data is divided into three parts

        answer = waiting_time(sorting(processes, process_count), process_count)
        output_fp.write(str(answer))

        print(vars(Process))

