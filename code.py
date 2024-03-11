class Process:
    def __init__(self, process_id, burst_time, priority):
        self.process_id = process_id
        self.burst_time = burst_time
        self.priority = priority

def enqueue(queue, process):
    queue.append(process)

def dequeue(queue):
    front = queue.pop(0)
    return front

def display_queue(queue, queue_name):
    print(f"{queue_name} Queue:", end=" ")
    for process in queue:
        print(f"[P{process.process_id} (Burst: {process.burst_time}, Priority: {process.priority})]", end=" ")
    print()

def multilevel_feedback_queue_scheduling(processes):
    queues = [[] for _ in range(3)]
    time_quantum = 2

    for queue_index in range(3):
        current_time = 0
        processed_processes = 0

        while processed_processes < len(processes):
            for process in processes:
                if 0 < process.burst_time <= time_quantum:
                    process.burst_time = 0
                    enqueue(queues[queue_index], process)
                    processed_processes += 1
                    current_time += process.burst_time
                elif process.burst_time > time_quantum:
                    process.burst_time -= time_quantum
                    current_time += time_quantum

            display_queue(queues[queue_index], "Current")

            # Move processes to the next queue
            for process in queues[queue_index]:
                if process.burst_time > 0:
                    enqueue(queues[queue_index + 1], process)

            display_queue(queues[queue_index + 1], "Next")

if __name__ == "__main__":
    processes = [
        Process(1, 10, 3),
        Process(2, 6, 5),
        Process(3, 8, 2),
        Process(4, 9, 1),
        Process(5, 7, 4)
    ]

    print("Initial Processes:")
    for process in processes:
        print(f"[P{process.process_id} (Burst: {process.burst_time}, Priority: {process.priority})]", end=" ")
    print("\n")

    multilevel_feedback_queue_scheduling(processes)
