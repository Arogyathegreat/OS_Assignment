import operator


class Process:
    def __init__(self, process_number, arrival_time, burst_count, burst_type, burst_container, ready_type, wait_time,
                 ready_time, total_burst_time):
        self.process_number = process_number  # id for process, according to their entry
        self.arrival_time = arrival_time  # first arrival time for the process
        self.burst_count = burst_count  # number of cpu and io bursts combined
        self.burst_type = burst_type  # used to identify the type of burst i.e. cpu or io
        self.burst_container = burst_container  # list containing all the bursts
        self.ready_type = ready_type  # 1: first arriving 2: io burst done 3: cpu burst remaining 4: process is done
        self.wait_time = wait_time  # waiting time in the ready queue
        self.ready_time = ready_time  # time when the process was last ready
        self.total_burst_time = total_burst_time  # total burst amount including both cpu and io bursts


def calculation(container, count, time_slice):  # main calculation function
    ready_queue = []  # list for ready processes

    c_id, r_process, tick, c_time = -1, count, 0, 0
    # c_id is current process id being processed
    # r_process remaining number of processes used for the main loop
    # tick is the remaining time slice provided to a process
    # c_time is the current time in the processing timeline

    while r_process > 0:  # loop breaks when all the processes are done

        for i in range(0, count):  # checks if the process is just arriving and adds to ready queue if true
            if container[i].ready_type == 4:
                continue
            if container[i].arrival_time == c_time:
                container[i].ready_type = 1
                container[i].ready_time = c_time  # sets the current time as the process's ready time
                ready_queue.append(container[i])

        for i in range(0, count):
            if container[i].ready_type == 4:
                continue
            if container[i].process_number == c_id and container[i].burst_container[container[i].burst_type] < 1:
                # if the process is to be processed and if there are no bursts for the current burst type
                tick = 0  # set the timeslice to 0

                if container[i].burst_type >= container[i].burst_count - 1:  # if all the bursts are done
                    r_process -= 1  # one process is done
                    container[i].ready_type = 4
                    container[i].wait_time = c_time - container[i].arrival_time - container[i].total_burst_time
                    # its process wait time is current time reduced by process's arrival time and its total burst amt

            elif container[i].burst_container[container[i].burst_type] == 0 and container[i].burst_type % 2 == 1:
                # if the current burst is empty and the burst type is io burst then
                container[i].ready_type = 2
                container[i].ready_time = c_time
                ready_queue.append(container[i])
                container[i].burst_type += 1  # sets the burst to next type i.e. cpu burst

        if tick == 0:  # if the allocated time is all used
            tick = time_slice  # replenish the time
            for i in range(0, count):
                if container[i].ready_type == 4:
                    continue
                if container[i].process_number == c_id:
                    if container[i].burst_container[container[i].burst_type] > 0:  # if there is burst remaining
                        container[i].ready_type = 3
                        container[i].ready_time = c_time
                        ready_queue.append(container[i])
                    else:
                        container[i].burst_type += 1  # if not then move to the next burst type

            ready_queue.sort(key=operator.attrgetter('ready_time', 'ready_type', 'process_number'))
            # sort by ready_time then ready_type and process_number
            if len(ready_queue) == 0:  # if the ready queue is empty
                c_id = -1
            else:
                c_id = ready_queue[0].process_number
                # then set the current id as ready queue's first process's id as c_id
                ready_queue.pop(0)  # remove it from ready queue

        for i in range(0, count):  # checks if the process is done and if not reduces burst time
            if container[i].ready_time == 4:
                continue
            if container[i].process_number == c_id or container[i].burst_type % 2 == 1:
                container[i].burst_container[container[i].burst_type] -= 1

        if c_id != -1:  # if there is a process being executed
            tick -= 1  # reduce its time by 1
        else:
            tick = 0

        ready_queue.sort(key=operator.attrgetter('process_number'))  # final sorting by the process number
        c_time += 1  # increase the timeline by 1

    for process in container:
        out.write(str(process.process_number) + " " + str(process.wait_time) + '\n')  # print it out


if __name__ == '__main__':
    process_container = []
    with open('rr.inp') as inp, open('rr.out', 'w') as out:

        process_count, time_slice = map(int, inp.readline().split())
        # first line includes the no. of process and timeslice for them
        total_bur, i = 0, 1  # total_bur will hold the total burst amount of a process i will hold the process number
        for line in inp:
            arr, bur = map(int, line.split())  # arrival time and burst count
            c_bur = list(map(int, inp.readline().split()))  # burst amounts
            total_bur += sum(c_bur)  # add the burst to the total burst amount
            process_container.append(Process(i, arr, bur, 0, c_bur, 0, 0, 0, total_bur))
            # add the process to the container
            i += 1
            total_bur = 0

        calculation(process_container, process_count, time_slice) 
