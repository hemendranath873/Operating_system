#include <iostream>
#include <climits>
using namespace std;

void SRT(int burstTimes[], int arrivalTimes[], int n) {
    int remainingTime[n], startTime[n], endTime[n], completionTime[n];
    int waitingTime[n], turnaroundTime[n];
    int currentTime = 0, completed = 0, minProcess = -1;
    bool isFirstExecution[n] = {false};
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Initialize remaining times and start times
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTimes[i];
        startTime[i] = -1;
    }

    // Process until all processes are completed
    while (completed != n) {
        // Find the process with the shortest remaining time at current time
        int minTime = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (arrivalTimes[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minTime) {
                minTime = remainingTime[i];
                minProcess = i;
            }
        }

        if (minProcess == -1) {
            currentTime++; // Idle time
            continue;
        }

        // Start time for the process (only set once)
        if (!isFirstExecution[minProcess]) {
            startTime[minProcess] = currentTime;
            isFirstExecution[minProcess] = true;
        }

        // Process execution for 1 unit of time
        remainingTime[minProcess]--;
        currentTime++;

        // If the process finishes
        if (remainingTime[minProcess] == 0) {
            completed++;
            completionTime[minProcess] = currentTime;
            endTime[minProcess] = currentTime;

            // Calculate waiting and turnaround times
            turnaroundTime[minProcess] = completionTime[minProcess] - arrivalTimes[minProcess];
            waitingTime[minProcess] = turnaroundTime[minProcess] - burstTimes[minProcess];
            totalWaitingTime += waitingTime[minProcess];
            totalTurnaroundTime += turnaroundTime[minProcess];
        }
    }

    // Output results
    cout << "\nPID\tArrival\tBurst\tStart\tEnd\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << arrivalTimes[i] << "\t" << burstTimes[i] << "\t"
             << startTime[i] << "\t" << endTime[i] << "\t" << waitingTime[i] << "\t" << turnaroundTime[i] << "\n";
    }

    cout << "Average Waiting Time: " << (float)totalWaitingTime / n << "\n";
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << "\n";
}

int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    int burstTimes[n], arrivalTimes[n];
    cout << "Enter the arrival and burst times of the processes:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> arrivalTimes[i];
        cout << "Burst Time: ";
        cin >> burstTimes[i];
    }

    SRT(burstTimes, arrivalTimes, n);

    return 0;
}
