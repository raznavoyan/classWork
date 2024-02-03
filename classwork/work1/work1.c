#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void executeCommand(char *command) {
    // Ստանում ենք հրամանը որպես տող
    char *args[100];
    int i = 0;

    // Բաժանում ենք հրամանը բացատրակազմերի՝ տողում գտնվող բոլոր բառերին
    char *token = strtok(command, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL; // Կատարման ավարտի համար NULL-ը վերագրում ենք

    // Ասենք, որ օգտվողը չի մուտքագրել "exit" հրամանը
    if (strcmp(args[0], "exit") != 0) {
        pid_t pid = fork(); // Ստեղծում է child պրոցես

        if (pid == 0) {
            // Child պրոցեսի մասին
            execvp(args[0], args);
            perror("Սխալ կատարման ընթացքում");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Խնդիր է ստեղծել child պրոցեսը
            perror("Չի հաջողվել fork կատարելու");
        } else {
            // Parent պրոցեսի մասին
            wait(NULL); // Սպասում է child պրոցեսի ավարտին
        }
    } else {
        printf("Աղբյուրը արգելված է։ Կատարված հրամանը՝ exit\n");
    }
}

int main() {
    char command[100];

    while (1) {
        printf("Մուտքագրեք հրաման (exit-ը դուրս գալու համար): ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0'; // Հեռացնում է վերջին սիմվոլը (հորիզոնթալու համար)

        if (strcmp(command, "exit") == 0) {
            printf("Հրամանը դուրս գալու է։ Կատարում ավարտված է\n");
            break;
        }

        executeCommand(command);
    }

    return 0;
}

