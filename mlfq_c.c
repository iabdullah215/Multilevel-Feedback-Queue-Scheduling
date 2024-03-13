#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 5
#define MAX_QUEUES 3

typedef struct {
    int process_id;
    int burst_time;
    int priority;
} Process;

void enqueue(Process* queue, int* rear, Process process) {
    queue[++(*rear)] = process;
}

Process dequeue(Process* queue, int* front) {
    return queue[(*front)++];
}

void displayQueue(Process* queue, int front, int rear, char* queueName) {
    printf("%s Queue: ", queueName);
    for (int i = front; i <= rear; i++) {
        printf("[P%d (Burst: %d, Priority: %d)] ", queue[i].process_id, queue[i].burst_time, queue[i].priority);
    }
    printf("\n");
}

void multilevelFeedbackQueueScheduling(Process processes[], int num_processes) {
    Process queues[MAX_QUEUES][MAX_PROCESSES];
    int front[MAX_QUEUES] = {0};
    int rear[MAX_QUEUES] = {-1};

    for (int time_quantum = 2, queue_index = 0; queue_index < MAX_QUEUES; time_quantum *= 2, queue_index++) {
        int current_time = 0;
        int processed_processes = 0;

        while (processed_processes < num_processes) {
            for (int i = 0; i < num_processes; i++) {
                if (processes[i].burst_time > 0 && processes[i].burst_time <= time_quantum) {
                    processes[i].burst_time = 0;
                    enqueue(queues[queue_index], &rear[queue_index], processes[i]);
                    processed_processes++;
                    current_time += processes[i].burst_time;
                } else if (processes[i].burst_time > time_quantum) {
                    processes[i].burst_time -= time_quantum;
                    current_time += time_quantum;
                }
            }

            displayQueue(queues[queue_index], front[queue_index], rear[queue_index], "Current");

            // Move processes to the next queue
            for (int i = front[queue_index]; i <= rear[queue_index]; i++) {
                if (queues[queue_index][i].burst_time > 0) {
                    enqueue(queues[queue_index + 1], &rear[queue_index + 1], dequeue(queues[queue_index], &front[queue_index]));
                }
            }

            displayQueue(queues[queue_index + 1], front[queue_index + 1], rear[queue_index + 1], "Next");
        }
    }
}

int main() {
    Process processes[MAX_PROCESSES] = {
        {1, 10, 3},
        {2, 6, 5},
        {3, 8, 2},
        {4, 9, 1},
        {5, 7, 4}
    };

    printf("Initial Processes:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("[P%d (Burst: %d, Priority: %d)] ", processes[i].process_id, processes[i].burst_time, processes[i].priority);
    }
    printf("\n\n");

    multilevelFeedbackQueueScheduling(processes, MAX_PROCESSES);

    return 0;
}
