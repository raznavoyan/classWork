#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>  // Include the necessary header

int main() {

    printf("Nice value: %d\n", getpriority(PRIO_PROCESS, getpid()));
    // Define the new nice value (priority)
    int new_priority = 10;

    // First time, print the new nice value
    printf("New nice value: %d\n", new_priority);

    // Change the nice value (priority) of the current process
    if (setpriority(PRIO_PROCESS, getpid(), new_priority) == -1) {
        perror("Failed to change priority");
        exit(EXIT_FAILURE);
    }

    // Second time, print the updated nice value
    int updated_priority = getpriority(PRIO_PROCESS, getpid());
    printf("Updated nice value: %d\n", updated_priority);

    return 0;
}

