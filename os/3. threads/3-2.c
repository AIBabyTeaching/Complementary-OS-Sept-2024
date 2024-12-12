#include <stdio.h>          // Standard input/output header
#include <unistd.h>         // Provides sleep() function
#include <time.h>           // Time utilities (not used in this code, included unnecessarily)
#include <pthread.h>        // Library for creating and managing threads in C

/*
    This program demonstrates thread creation and how to pass arguments to threads
    using POSIX threads (pthreads).
    
    Key Requirements for a thread routine:
    1. The routine must return a void pointer (void *).
    2. The routine must accept a void pointer as an argument (void *).

    To compile the code, you need to link the pthread library using the '-pthread' flag:
    Example:
        gcc 3-2.c -o 3-2 -pthread
*/

// Thread routine executed by each thread
void* my_routine(void* raw_args) {
    // Cast the void pointer argument to a character pointer
    char* c = (char*) raw_args;
    /*
    void* is a generic pointer type that can hold the address of any type of data.
    Casting ((char*) raw_args) tells the compiler to treat the generic pointer as a specific type (char*).
    This type information is necessary to access the actual value being pointed to. Without casting, dereferencing is not possible.
    */

    int i;

    // Loop to simulate some task performed by the thread
    for (i = 0; i < 5; i++) {
        // Dereference the character pointer to access the passed value
        printf("%c: %d\n", *c, i);  // Print the character and iteration number
        sleep(1);                  // Pause execution for 1 second
    }

    // Thread returns NULL after finishing execution
    return NULL;
}

int main() {
    pthread_t tid1, tid2;  // Declare two thread identifiers of type pthread_t
    char c1 = 'A', c2 = 'B'; // Characters to identify the threads

    // Create and start the first thread
    // Arguments:
    // 1. &tid1: Pointer to the first thread identifier
    // 2. NULL: Default thread attributes
    // 3. my_routine: Function to be executed by the thread
    // 4. &c1: Argument passed to the thread function (pointer to the character 'A')
    pthread_create(&tid1, NULL, my_routine, &c1);

    // Create and start the second thread
    // Arguments:
    // 1. &tid2: Pointer to the second thread identifier
    // 2. NULL: Default thread attributes
    // 3. my_routine: Function to be executed by the thread
    // 4. &c2: Argument passed to the thread function (pointer to the character 'B')
    pthread_create(&tid2, NULL, my_routine, &c2);

    int i;

    // Main thread performs its own task in parallel with the created threads
    for (i = 0; i < 5; i++) {
        printf("main: %d\n", i);  // Print the iteration number prefixed with "main"
        sleep(1);                 // Pause execution for 1 second
    }

    // Wait for the first thread to finish execution
    // Arguments:
    // 1. tid1: Thread identifier of the first thread to wait for
    // 2. NULL: Pointer to store the return value of the thread (not used here)
    pthread_join(tid1, NULL);

    // Wait for the second thread to finish execution
    // Arguments:
    // 1. tid2: Thread identifier of the second thread to wait for
    // 2. NULL: Pointer to store the return value of the thread (not used here)
    pthread_join(tid2, NULL);

    // Program ends after the main thread and both created threads complete execution
    return 0;
}
