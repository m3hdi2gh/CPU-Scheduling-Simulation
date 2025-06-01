# CPU Scheduling Simulation

This project simulates three classic CPU-scheduling algorithms in C, prints their Gantt charts, and checks that the calculated performance metrics match reference values for eight predefined test cases.

---

## Algorithms Implemented

| Algo | Full Name | Pre-emptive? | Highlights |
|------|-----------|--------------|------------|
| FCFS | First-Come-First-Serve | ✗ | simplest; FIFO order |
| SJF  | Shortest-Job-First (non-pre) | ✗ | picks shortest burst among arrived jobs |
| RR   | Round Robin (configurable quantum) | ✓ | fairness via time-slice |

For every algorithm the code calculates:

- **Average Turnaround Time**  
- **Average Waiting Time**  
- **Average Response Time**

---

## File Structure

```

.
├── scheduler.h         # Declarations for structs and scheduling functions
├── scheduler.c         # Implementation of the scheduling algorithms
├── scheduler_test.c    # Test cases and assertions for validating correctness
├── Makefile            # Build automation script
└── README.md           # you are here

````

---

## How to Compile

To build the project, simply use:

```bash
make
```

This compiles the source files and produces an executable named `scheduler_test`.

### How to Run

To run the compiled test program:

```bash
make run
```

This will execute the scheduler tests and print the calculated vs. expected metrics for:
- FCFS
- SJF
- Round Robin (with specified quantum)

If all assertions pass, you will see:

```
>>> Test Case X PASSED.
...
ALL TESTS PASSED.
```

### How to Clean

To remove the compiled binary:

```bash
make clean
```

---

## Input

Each scheduler works on an array of:

| Field            | Meaning                        |
| ---------------- | ------------------------------ |
| `pid`            | process ID                     |
| `arrivalTime`    | arrival timestamp              |
| `burstTime`      | total CPU time needed          |
| `remainingTime`  | (RR only) time still to run    |
| `startTime`      | first CPU entry (for response) |
| `completionTime` | finish timestamp               |

Eight test cases—defined in **`scheduler_test.c`**—cover:

* idle CPU gaps
* simultaneous arrivals
* single-process edge case
* different round-robin quanta (2 – 4)
* up to 6 processes

---

## Output

For every test case the program prints:

1. **Gantt chart** for each algorithm
   Format → `| P<pid> <start>-<end> | … |`
   Example (Test Case 1, RR with q = 4):

   ```
   | P1 0-4 | P2 4-8 | P3 8-12 | P1 12-16 | ... |
   ```

2. **Metrics vs. expected**
   Floating-point comparisons use a tolerance of **0.1**.

   ```
   FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
         Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
   ```

3. **PASS / FAIL banner**
   All eight cases pass on a fresh clone (`ALL TESTS PASSED.`).

### Sample Output

The following sections provide sample outputs for each scheduling algorithm (FCFS, SJF, and RR) across multiple test cases, including Gantt charts and calculated metrics (average turnaround time, waiting time, and response time).

<details>
<summary> Test Case 1 </summary>

```
==== Test Case 1 ====
 FCFS Gantt:
| P1 0-10 | P2 10-15 | P3 15-23 |

 SJF Gantt:
| P1 0-10 | P2 10-15 | P3 15-23 |

 RR Gantt (q=4):
| P1 0-4 | P2 4-8 | P3 8-12 | P1 12-16 | P2 16-17 | P3 17-21 | P1 21-23 |

FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
SJF:  Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
RR (Quantum = 4): Calculated: Turnaround: 19.33, Waiting: 11.67, Response: 3.00
         Expected:   Turnaround: 19.33, Waiting: 11.67, Response: 3.00
>>> Test Case 1 PASSED.
```

</details>

<details>
<summary> Test Case 2 </summary>

```
==== Test Case 2 ====
 FCFS Gantt:
| P1 2-8 | P2 8-10 | P3 10-14 |

 SJF Gantt:
| P1 2-8 | P2 8-10 | P3 10-14 |

 RR Gantt (q=2):
| P1 2-4 | P1 4-6 | P2 6-8 | P1 8-10 | P3 10-12 | P3 12-14 |

FCFS: Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.67
      Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.67
SJF:  Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.67
      Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.67
RR (Quantum = 2): Calculated: Turnaround: 5.67, Waiting: 1.67, Response: 1.00
         Expected:   Turnaround: 5.67, Waiting: 1.67, Response: 1.00
>>> Test Case 2 PASSED.
```

</details>

<details>
<summary> Test Case 3 </summary>

```
==== Test Case 3 ====
 FCFS Gantt:
| P1 0-4 | P2 4-7 | P3 7-8 | P4 8-10 |

 SJF Gantt:
| P1 0-4 | P3 4-5 | P4 5-7 | P2 7-10 |

 RR Gantt (q=2):
| P1 0-2 | P2 2-4 | P3 4-5 | P1 5-7 | P4 7-9 | P2 9-10 |

FCFS: Calculated: Turnaround: 5.75, Waiting: 3.25, Response: 3.25
      Expected:   Turnaround: 5.75, Waiting: 3.25, Response: 3.25
SJF:  Calculated: Turnaround: 5.00, Waiting: 2.50, Response: 2.50
      Expected:   Turnaround: 5.00, Waiting: 2.50, Response: 2.50
RR (Quantum = 2): Calculated: Turnaround: 6.25, Waiting: 3.75, Response: 1.75
         Expected:   Turnaround: 6.25, Waiting: 3.75, Response: 1.75
>>> Test Case 3 PASSED.
```

</details>

<details>
<summary> Test Case 4 </summary>

```
==== Test Case 4 ====
 FCFS Gantt:
| P1 0-3 | P2 3-9 | P3 9-13 | P4 13-18 | P5 18-20 |

 SJF Gantt:
| P1 0-3 | P2 3-9 | P5 9-11 | P3 11-15 | P4 15-20 |

 RR Gantt (q=3):
| P1 0-3 | P2 3-6 | P3 6-9 | P4 9-12 | P2 12-15 | P5 15-17 | P3 17-18 | P4 18-20 |

FCFS: Calculated: Turnaround: 8.60, Waiting: 4.60, Response: 4.60
      Expected:   Turnaround: 8.60, Waiting: 4.60, Response: 4.60
SJF:  Calculated: Turnaround: 7.60, Waiting: 3.60, Response: 3.60
      Expected:   Turnaround: 7.60, Waiting: 3.60, Response: 3.60
RR (Quantum = 3): Calculated: Turnaround: 10.60, Waiting: 6.60, Response: 2.60
         Expected:   Turnaround: 10.60, Waiting: 6.60, Response: 2.60
>>> Test Case 4 PASSED.
```

</details>

<details>
<summary> Test Case 5 </summary>

```
==== Test Case 5 (Single Process) ====
 FCFS Gantt:
| P1 0-5 |

 SJF Gantt:
| P1 0-5 |

 RR Gantt (q=2):
| P1 0-2 | P1 2-4 | P1 4-5 |

FCFS: Calculated: Turnaround: 5.00, Waiting: 0.00, Response: 0.00
      Expected:   Turnaround: 5.00, Waiting: 0.00, Response: 0.00
SJF:  Calculated: Turnaround: 5.00, Waiting: 0.00, Response: 0.00
      Expected:   Turnaround: 5.00, Waiting: 0.00, Response: 0.00
RR (Quantum = 2): Calculated: Turnaround: 5.00, Waiting: 0.00, Response: 0.00
         Expected:   Turnaround: 5.00, Waiting: 0.00, Response: 0.00
>>> Test Case 5 (Single Process) PASSED.
```

</details>

<details>
<summary> Test Case 6 </summary>

```
==== Test Case 6 (Two Processes, Same Arrival) ====
 FCFS Gantt:
| P1 0-4 | P2 4-10 |

 SJF Gantt:
| P1 0-4 | P2 4-10 |

 RR Gantt (q=3):
| P1 0-3 | P2 3-6 | P1 6-7 | P2 7-10 |

FCFS: Calculated: Turnaround: 7.00, Waiting: 2.00, Response: 2.00
      Expected:   Turnaround: 7.00, Waiting: 2.00, Response: 2.00
SJF:  Calculated: Turnaround: 7.00, Waiting: 2.00, Response: 2.00
      Expected:   Turnaround: 7.00, Waiting: 2.00, Response: 2.00
RR (Quantum = 3): Calculated: Turnaround: 8.50, Waiting: 3.50, Response: 1.50
         Expected:   Turnaround: 8.50, Waiting: 3.50, Response: 1.50
>>> Test Case 6 (Two Processes, Same Arrival) PASSED.
```

</details>

<details>
<summary> Test Case 7 </summary>

```
==== Test Case 7 (Varying Arrivals) ====
 FCFS Gantt:
| P1 0-8 | P2 8-12 | P3 12-21 | P4 21-26 |

 SJF Gantt:
| P1 0-8 | P2 8-12 | P4 12-17 | P3 17-26 |

 RR Gantt (q=3):
| P1 0-3 | P2 3-6 | P3 6-9 | P4 9-12 | P1 12-15 | P2 15-16 | P3 16-19 | P4 19-21 | P1 21-23 | P3 23-26 |

FCFS: Calculated: Turnaround: 15.25, Waiting: 8.75, Response: 8.75
      Expected:   Turnaround: 15.25, Waiting: 8.75, Response: 8.75
SJF:  Calculated: Turnaround: 14.25, Waiting: 7.75, Response: 7.75
      Expected:   Turnaround: 14.25, Waiting: 7.75, Response: 7.75
RR (Quantum = 3): Calculated: Turnaround: 20.00, Waiting: 13.50, Response: 3.00
         Expected:   Turnaround: 20.00, Waiting: 13.50, Response: 3.00
>>> Test Case 7 (Varying Arrivals) PASSED.
```

</details>

<details>
<summary> Test Case 8 </summary>

```
==== Test Case 8 (Six Processes) ====
 FCFS Gantt:
| P1 0-10 | P2 10-13 | P3 13-20 | P4 20-25 | P5 25-27 | P6 27-35 |

 SJF Gantt:
| P1 0-10 | P5 10-12 | P2 12-15 | P4 15-20 | P3 20-27 | P6 27-35 |

 RR Gantt (q=4):
| P1 0-4 | P2 4-7 | P3 7-11 | P1 11-15 | P4 15-19 | P5 19-21 | P6 21-25 | P3 25-28 | P1 28-30 | P4 30-31 | P6 31-35 |

FCFS: Calculated: Turnaround: 17.00, Waiting: 11.17, Response: 11.17
      Expected:   Turnaround: 17.00, Waiting: 11.17, Response: 11.17
SJF:  Calculated: Turnaround: 15.17, Waiting: 9.33, Response: 9.33
      Expected:   Turnaround: 15.17, Waiting: 9.33, Response: 9.33
RR (Quantum = 4): Calculated: Turnaround: 20.67, Waiting: 14.83, Response: 6.33
         Expected:   Turnaround: 20.67, Waiting: 14.83, Response: 6.33
>>> Test Case 8 (Six Processes) PASSED.
```

</details>

---

## Notes

- The `Process` struct contains fields for tracking all timing metrics.
- All algorithms are non-preemptive except RR which uses time slicing.
- The project is written in standard C and should work on any Unix-like system (Linux, macOS, WSL).

---

## Limitations

* SJF here is **non-preemptive**; a running job cannot be interrupted.
* Input is hard-coded in tests (no file/UI parser).
* Works safely up to 64 processes (static arrays).
* Metrics assume integer arrival/burst times.

---

## Ideas for Extending the Project

* Add **Pre-emptive SJF (SRTF)** or **Priority Scheduling**.
* Read process data from a JSON / CSV file instead of hard-coding.
* Generate a graphical Gantt chart (e.g. Python + Matplotlib).
* Simulate context-switch overhead to make RR results more realistic.

---
