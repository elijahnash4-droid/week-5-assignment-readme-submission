# Storing Threads

## Project Description

Sorts an array of integers using a merge sort with multi-threaded processing to minimize the time spent on running the application.

## Installation 

Step-by-step instructions on how to install and setup this project locally.

```
# clone the repository
git clone https://github.com/elijahnash4-droid/week-5-assignment-readme-submission.git

# Navigate to the project directory
cd Code
cd start
```

## Usage/Examples
To run the project input `./sorting_threads` in the terminal.

If you want to change the array size, Look for the `MAX_NUMBERS` constant and modify the number and `MAX_THREADS` to change how many threads are used. 

Make sure to recompile using `gcc sorting_threads.c -o sorting_threads` after modifying the constants.

```
// This example shows an array of 20 integers

Array before sorting: 17 7 18 5 14 14 7 11 0 13 2 15 0 6 4 3 11 10 18 
Array after sorting: 0 0 2 2 3 4 5 6 7 7 10 11 11 13 14 14 15 17 18 
The array was successfully sorted!
```