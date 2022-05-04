# OS_Tasks_Simulations
In this repository, I implemented various different tasks accomplished by the operating system using C. Tasks that are simulated are aspects of process control block, batch process scheduling algorithms, Banker's algorithm, memory allocation and disk traversal scheduling. I will give a brief explanation of each task below. 

**Process Control Block**: This file simulates a section of the process control block, specifically the parent-child relationship of processes. In this code, one can initialize their mock "process control block" where they can create and destroy child processes. 

**Batch Process Scheduling**: This file simulates the scheduling of batch processes using various algorithms. The scheduling algorithms demonstrated are First-In-First-Out (FIFO), Shortest-Job-First (SJB), and Shortest-Remaining-Time (SRT). The scheduling of the different algorithms are displayed in a table.

**Banker's Algorithm**: This file simulates Banker's Algorithm for deadlock avoidance. It simulates resource allocation to requesting processes and shows how deadlock is avoided using Banker's algorithm. A big chunk of this code is used to initialize the resources and processes and their respective specifications regarding allocation, maximum claim etc. After initialization, Banker's algorithm can be simulated.

**Memory Allocation**: This file simulates memory allocation of a block and the algorithms used to accomplish that. In the code, the allocation algorithms simulated are First-Fit, Best-Fit and Worst-Fit. Further, deallocation and defragmentation are demonstrated.

**Disk Scheduling**: This file simulates various disk scheduling algorithms used when traversing a disk. The algorithms being simulated are First-In-First-Out (FIFO), Shortest-Seek-Time-First (SSTF), Scan and C-Scan.


All implementations are written in C. These task simulations were programmed for an Operating Systems course.
