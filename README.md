# OpenMP-with-example
Using the OpenMP interface designed to divide the program into separate threads, solve the task of searching through a matrix of integers.
When the program is launched, it should generate a matrix of integers ranging from -1000 to +1000. The size of the matrix should be entered by the user. To ensure repeatability of the results, the srand() subroutine should not be called.
Next, the user should be prompted to specify the range of numbers to search for in the matrix. Multiple ranges should be allowed.
Then, the program should automatically change the number of threads from 0 to 10 to which the task will be divided. The program should search the matrix for the number of occurrences of numbers belonging to each of the specified ranges, dividing the task into a specified number of threads.
Each time, the search should start from the beginning (previous results should be cleared).
The program should display the time it takes to perform the calculations and a table of results (range from-to and number of occurrences). The results should be displayed only when the last of the threads finishes working and the timer is stopped.
## Usage/Examples
Check if the compiler is installed, use --version. For this example gcc is used
```bash
    g++ --version
```
Example output. The output doesn't matter, that is only for checking if the compiler is installed.
```
    g++ (Debian 12.2.0-14) 12.2.0
    Copyright (C) 2022 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
To compile the code. "$your_provided_name" can be any name that you want for the executable.
```bash
    g++ -fopenmp -o "$your_provided_name" main.cpp
```
Example with $your_provided_name = "OMP Jakub Praszkowski":
```bash
    g++ -fopenmp -o "OMP Jakub Praszkowski" main.cpp
```
In general to run program use:
```bash
    ./"$your_provided_name"
```
Example with $your_provided_name = "OMP Jakub Praszkowski":

```bash
    ./"OMP Jakub Praszkowski"
```
Example output of the program:
```
    Enter matrix size: 100
    Enter range to search for (e.g. -500 500): -500 500
    Enter another range? (y/n) n
    4
    Time taken with 0 threads: 474 microseconds
    Time taken with 1 threads: 526 microseconds
    Time taken with 2 threads: 1093 microseconds
    Time taken with 3 threads: 500 microseconds
    Time taken with 4 threads: 377 microseconds
    Time taken with 5 threads: 405 microseconds
    Time taken with 6 threads: 422 microseconds
    Time taken with 7 threads: 377 microseconds
    Time taken with 8 threads: 488 microseconds
    Time taken with 9 threads: 385 microseconds
    Time taken with 10 threads: 393 microseconds
    Range	Count	Threads
    -500-500	35122	0
    -500-500	10116	1
    -500-500	2590	2
    -500-500	1651	3
    -500-500	1297	4
    -500-500	1262	5
    -500-500	1120	6
    -500-500	1196	7
    -500-500	1284	8
    -500-500	0	    9
    -500-500	0	    10
```
