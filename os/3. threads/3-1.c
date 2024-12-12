#include <stdio.h>          // Standard input/output header
#include <unistd.h>         // Provides sleep() function
#include <time.h>           // Time utilities (not used in this code, included unnecessarily)
#include <pthread.h>        // Library for creating and managing threads in C

/*
    This program demonstrates basic thread creation and synchronization using POSIX threads (pthreads).
    
    Key Requirements for a thread routine:
    1. The routine must return a void pointer (void *).
    2. The routine must accept a void pointer as an argument (void *).

    To compile the code, you need to link the pthread library using the '-pthread' flag:
    Example:
        gcc 3-1.c -o 3-1 -pthread
*/

// Function executed by the thread
void* my_routine(void* args) {
    int i;

    // Loop to simulate some task performed by the thread
    for (i = 0; i < 5; i++) {
        printf("Y: %d\n", i);  // Print the iteration number prefixed with 'Y'
        sleep(1);              // Pause execution for 1 second
    }

    // Thread returns NULL after finishing execution
    return NULL;
}

int main() {
    pthread_t tid;  // Declare a thread identifier of type pthread_t

    // Create and start a new thread
    // Arguments:
    // 1. &tid: Pointer to the thread identifier
    // 2. NULL: Default thread attributes
    // 3. my_routine: Function to be executed by the thread
    // 4. NULL: Argument passed to the thread function (not used here)
    pthread_create(&tid, NULL, my_routine, NULL);

    int i;

    // Main thread performs its own task in parallel with the created thread
    for (i = 0; i < 5; i++) {
        printf("x: %d\n", i);  // Print the iteration number prefixed with 'x'
        sleep(1);              // Pause execution for 1 second
    }

    // Wait for the created thread to finish execution
    // Arguments:
    // 1. tid: Thread identifier of the thread to wait for
    // 2. NULL: Pointer to store the return value of the thread (not used here)
    pthread_join(tid, NULL);

    // Program ends after both main thread and created thread complete execution
    return 0;
}
