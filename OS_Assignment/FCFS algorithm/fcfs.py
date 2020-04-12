import operator


class Process:
    def __init__(self, number, arrival, duration):
        self.number = number
        self.arrival = arrival
        self.duration = duration

    def __str__(self):
        return str(self.__class__) + ": " + str(self.__dict__)


def waiting_time(container, count):
    time = container[0].arrival
    wt, tt = 0, 0
    for i in range(count):

        proc = container[i]

        if proc.arrival >= time:
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
    with open('fcfs.inp') as input_fp:

        process_count = int(input_fp.readline())

        for line in input_fp:
            data = line.split()
            num, arr, dur = map(int, line.split())
            processes.append(Process(num, arr, dur))

        processes.sort(key=operator.attrgetter('arrival', 'number'))

        answer = waiting_time(processes, process_count)
        output_fp.write(str(answer))

    output_fp.close()
