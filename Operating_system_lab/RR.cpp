#include <iostream>
#include <queue>
using namespace std;

void RoundRobin(int burstTimes[], int n, int quantum) {
    int remainingTime[n], startTime[n], endTime[n], waitingTime[n], turnaroundTime[n];
    queue<int> q;
    int currentTime = 0;
    bool isFirstExecution[n] = {false};
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTimes[i];
        startTime[i] = -1;
        q.push(i); // Add all processes to the queue
    }

    // Process execution in round-robin fashion
    while (!q.empty()) {
        int i = q.front();
        q.pop();

        // If it's the first execution of a process, record the start time
        if (!isFirstExecution[i]) {
            startTime[i] = currentTime;
            isFirstExecution[i] = true;
        }

        // Execute the process for the time quantum or until completion
        int executionTime = min(remainingTime[i], quantum);
        remainingTime[i] -= executionTime;
        currentTime += executionTime;

        // If the process has finished, calculate its end time, waiting, and turnaround times
        if (remainingTime[i] == 0) {
            endTime[i] = currentTime;
            turnaroundTime[i] = endTime[i] - startTime[i];
            waitingTime[i] = turnaroundTime[i] - burstTimes[i];
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += turnaroundTime[i];
        } else {
            q.push(i); // If the process is not finished, add it back to the queue
        }
    }

    // Output results
    cout << "\nPID\tBurst\tStart\tEnd\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << burstTimes[i] << "\t"
             << startTime[i] << "\t" << endTime[i] << "\t"
             << waitingTime[i] << "\t" << turnaroundTime[i] << "\n";
    }

    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << "\n";
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << "\n";
}

int main() {
    int n, quantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    int burstTimes[n];
    cout << "Enter the burst times of the processes:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> burstTimes[i];
    }

    cout << "Enter the time quantum: ";
    cin >> quantum;

    RoundRobin(burstTimes, n, quantum);

    return 0;
}
