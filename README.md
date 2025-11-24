# BankersAlgorithm
C++ file to emulate bankers algorithm, txt file holds the resources for alorithm

To run the program
g++ banker.cpp
./a.out

Bankers algorithm works when you have a preset number of processes that each have a max number of resources they need to complete. The algorithm will see which processes can be complete with its available resources in order to avoid deadlock by seeing if the process will be complete after it gives its resources which frees up resources for other processes.
