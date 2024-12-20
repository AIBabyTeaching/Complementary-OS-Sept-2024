#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

// Define the number of threads
#define NUM 12

// Thread routine executed by each thread
void* my_routine(void* raw_args) {
    // Cast the void* argument to a char* to access the thread-specific character
    char* c = (char*) raw_args;

    // Loop to simulate thread work
    for (int i = 0; i < 4; i++) {
        // Print the thread's character label and its progress
        printf("%c: %d\n", *c, i);

        // Introduce a random delay to simulate variable task durations
        usleep(rand() % (1000 * 1000)); // Sleep for up to 1 second
    }

    return NULL; // Return NULL to indicate successful execution
}

int main() {
    // Seed the random number generator
    srand(time(0));

    // Array to hold thread IDs
    pthread_t tids[NUM];

    // Array to hold labels for each thread
    char labels[NUM]; // A, B, C and etc ..

    // Create NUM threads
    for (int t = 0; t < NUM; t++) {
        // Assign a unique label to each thread ('A', 'B', ..., 'L')
        labels[t] = 'A' + t;

        // Create the thread, passing its specific label as an argument
        pthread_create(&tids[t], NULL, my_routine, &labels[t]);
    }

    // Main thread performs its own task
    for (int i = 0; i < 4; i++) {
        // Print the main thread's progress
        printf("main: %d\n", i);

        // Introduce a random delay to simulate work
        usleep(rand() % (1000 * 1000)); // Sleep for up to 1 second
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM; i++) {
        pthread_join(tids[i], NULL); // Block until thread i finishes
    }

    return 0; // Indicate successful program termination
}
