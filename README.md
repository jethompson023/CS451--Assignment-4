CS451--Assignment-4
This program displays a user interface to let the user manipulate a static amount of memory with a first, best, and worst fit algorithm. It also allows the compaction and printing of memory.

To Compile:
gcc allocator.c -o allocator

To Run:
./allocator <amountOfTotalMemory>

To Request Memory
Allocator > RQ <Process Name> <Memory Size> <Type of Fit>
Types of Fit include 
First Fit = F
Worst Fit = W
Best Fit = B


To Release Memory
Allocator> RL <Process Name>

To Compact Memory
Allocator> C

To Print Contents of Memory
Allocator> STAT

To Exit
Allocator> X
