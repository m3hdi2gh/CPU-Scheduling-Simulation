#include "scheduler.h"
#include <stdio.h>

#define MAX_N   64          // max processes
#define INF     1000000000  // used once in SJF

// quick copy helper
static void clone(const Process *in, Process *out, int n) {
    for (int i = 0; i < n; ++i) out[i] = in[i];
}

// ---------------- Scheduling Algorithms ----------------

// FCFS Scheduling
Metrics fcfs_metrics(Process proc[], int n) {

    Process p[MAX_N];
    clone(proc, p, n);

    // sort by arrival then PID
    for (int i = 1; i < n; ++i) {
        Process key = p[i];
        int j = i - 1;
        while (j >= 0 &&
              (p[j].arrivalTime > key.arrivalTime ||
              (p[j].arrivalTime == key.arrivalTime && p[j].pid > key.pid))) {
            p[j+1] = p[j];
            --j;
        }
        p[j+1] = key;
    }

    int cur = 0;
    float sumTAT = 0, sumWT = 0, sumRT = 0;

    puts(" FCFS Gantt:");
    for (int i = 0; i < n; ++i) {
        if (cur < p[i].arrivalTime) cur = p[i].arrivalTime;

        p[i].startTime      = cur;
        p[i].completionTime = cur + p[i].burstTime;
        cur                += p[i].burstTime;

        printf("| P%d %d-%d ", p[i].pid, p[i].startTime, p[i].completionTime);

        int tat = p[i].completionTime - p[i].arrivalTime;
        int wt  = p[i].startTime      - p[i].arrivalTime;
        int rt  = wt; // non-preemptive

        sumTAT += tat; sumWT += wt; sumRT += rt;
    }
    puts("|\n");

    return (Metrics){ sumTAT/n, sumWT/n, sumRT/n };
}

// SJF Scheduling (Non-preemptive)
Metrics sjf_metrics(Process proc[], int n) {

    Process p[MAX_N];
    clone(proc, p, n);

    int done[MAX_N] = {0};
    int finished = 0, cur = 0;
    float sumTAT = 0, sumWT = 0, sumRT = 0;

    puts(" SJF Gantt:");
    while (finished < n) {
        int idx = -1;

        // pick shortest break ties by earlier arrival then PID
        for (int i = 0; i < n; ++i) {
            if (done[i] || p[i].arrivalTime > cur) continue;
            if (idx == -1 ||
                p[i].burstTime  <  p[idx].burstTime ||
               (p[i].burstTime == p[idx].burstTime &&
                (p[i].arrivalTime <  p[idx].arrivalTime ||
                (p[i].arrivalTime == p[idx].arrivalTime && p[i].pid < p[idx].pid))))
                idx = i;
        }

        if (idx == -1) { cur++; continue; }   // still waiting for someone

        p[idx].startTime      = cur;
        p[idx].completionTime = cur + p[idx].burstTime;
        cur                   = p[idx].completionTime;
        done[idx]             = 1;
        finished++;

        printf("| P%d %d-%d ", p[idx].pid, p[idx].startTime, p[idx].completionTime);

        int tat = p[idx].completionTime - p[idx].arrivalTime;
        int wt  = p[idx].startTime      - p[idx].arrivalTime;
        int rt  = wt;

        sumTAT += tat; sumWT += wt; sumRT += rt;
    }
    puts("|\n");

    return (Metrics){ sumTAT/n, sumWT/n, sumRT/n };
}

// Round Robin Scheduling (Revised)
Metrics rr_metrics(Process proc[], int n, int q) {

    Process p[MAX_N];
    clone(proc, p, n);

    // circular queue
    int Q[MAX_N]; int head = 0, tail = 0;
    int seen[MAX_N] = {0};

    #define ENQ_NEW() \
        for (int i = 0; i < n; ++i) \
            if (!seen[i] && p[i].arrivalTime <= cur) { \
                Q[tail++] = i; tail %= MAX_N; seen[i] = 1; \
            }

    int cur = 0, done = 0;
    float sumTAT = 0, sumWT = 0, sumRT = 0;

    ENQ_NEW();
    printf(" RR Gantt (q=%d):\n", q);
    int sliceBeg = cur;

    while (done < n) {

        if (head == tail) { cur++; sliceBeg = cur; ENQ_NEW(); continue; }

        int idx = Q[head++]; head %= MAX_N;

        if (p[idx].remainingTime == 0) p[idx].remainingTime = p[idx].burstTime;
        if (p[idx].remainingTime == p[idx].burstTime) {      /* first touch */
            p[idx].startTime = cur;
            sumRT += cur - p[idx].arrivalTime;
        }

        int run = (p[idx].remainingTime < q) ? p[idx].remainingTime : q;
        p[idx].remainingTime -= run;
        cur += run;

        ENQ_NEW();

        if (p[idx].remainingTime) {
            Q[tail++] = idx; tail %= MAX_N;
            printf("| P%d %d-%d ", p[idx].pid, sliceBeg, cur);
            sliceBeg = cur;
        } else {
            p[idx].completionTime = cur;
            done++;

            printf("| P%d %d-%d ", p[idx].pid, sliceBeg, cur);
            sliceBeg = cur;

            int tat = p[idx].completionTime - p[idx].arrivalTime;
            int wt  = tat - p[idx].burstTime;
            sumTAT += tat; sumWT += wt;
        }
    }
    puts("|\n");

    return (Metrics){ sumTAT/n, sumWT/n, sumRT/n };
}
