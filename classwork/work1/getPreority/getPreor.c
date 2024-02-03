#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    // Obtain the PID of the current process
    id_t current_pid = getpid();

    // Obtain the nice value (priority) of the current process
    int current_priority = getpriority(PRIO_PROCESS, current_pid);

    // Print the current process PID and its nice value (priority)
    printf("Current process PID: %d\n", current_pid);
    printf("Nice value (priority): %d\n", current_priority);

    return 0;
}
