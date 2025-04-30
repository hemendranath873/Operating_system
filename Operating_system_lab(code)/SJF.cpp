#include <iostream>
using namespace std;

void SJF(int burstTimes[], int arrivalTimes[], int n) {
    int waitingTime[n], turnaroundTime[n], startTime[n], endTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Sort processes by burst time (non-preemptive)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burstTimes[i] > burstTimes[j]) {
                swap(burstTimes[i], burstTimes[j]);
                swap(arrivalTimes[i], arrivalTimes[j]);
            }
        }
    }

    // Calculate start time, end time, and waiting time
    startTime[0] = arrivalTimes[0];
    endTime[0] = startTime[0] + burstTimes[0];
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++) {
        startTime[i] = max(endTime[i - 1], arrivalTimes[i]);
        endTime[i] = startTime[i] + burstTimes[i];
        waitingTime[i] = startTime[i] - arrivalTimes[i];
        if (waitingTime[i] < 0) waitingTime[i] = 0;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTimes[i] + waitingTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
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

    SJF(burstTimes, arrivalTimes, n);

    return 0;
}
