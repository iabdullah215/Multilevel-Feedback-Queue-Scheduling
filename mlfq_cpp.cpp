#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int process_id;
    int burst_time;
    int priority;
};

void enqueue(vector<Process>& queue, Process process) {
    queue.push_back(process);
}

Process dequeue(vector<Process>& queue) {
    Process front = queue.front();
    queue.erase(queue.begin());
    return front;
}

void displayQueue(const vector<Process>& queue, const string& queueName) {
    cout << queueName << " Queue: ";
    for (const auto& process : queue) {
        cout << "[P" << process.process_id << " (Burst: " << process.burst_time << ", Priority: " << process.priority << ")] ";
    }
    cout << endl;
}

void multilevelFeedbackQueueScheduling(vector<Process>& processes) {
    vector<Process> queues[3];
    int time_quantum = 2;

    for (int queue_index = 0; queue_index < 3; time_quantum *= 2, queue_index++) {
        int current_time = 0;
        int processed_processes = 0;

        while (processed_processes < processes.size()) {
            for (auto& process : processes) {
                if (process.burst_time > 0 && process.burst_time <= time_quantum) {
                    process.burst_time = 0;
                    enqueue(queues[queue_index], process);
                    processed_processes++;
                    current_time += process.burst_time;
                } else if (process.burst_time > time_quantum) {
                    process.burst_time -= time_quantum;
                    current_time += time_quantum;
                }
            }

            displayQueue(queues[queue_index], "Current");

            // Move processes to the next queue
            for (auto& process : queues[queue_index]) {
                if (process.burst_time > 0) {
                    enqueue(queues[queue_index + 1], process);
                }
            }

            displayQueue(queues[queue_index + 1], "Next");
        }
    }
}

int main() {
    vector<Process> processes = {
        {1, 10, 3},
        {2, 6, 5},
        {3, 8, 2},
        {4, 9, 1},
        {5, 7, 4}
    };

    cout << "Initial Processes:" << endl;
    for (const auto& process : processes) {
        cout << "[P" << process.process_id << " (Burst: " << process.burst_time << ", Priority: " << process.priority << ")] ";
    }
    cout << "\n\n";

    multilevelFeedbackQueueScheduling(processes);

    return 0;
}
