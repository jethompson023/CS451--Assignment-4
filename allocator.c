#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

char * command;
char * processName;
int amountMemory;
char * typeOfFit;


int main(int argc, char* argv[]) {

    checkArgs(argc, argv);
    printf("Command is %s, processName is %s, amount is %d, type is %s\n", command, processName, amountMemory, typeOfFit);
}

void checkArgs(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Necessary arguments are missing, exiting...\n");
        exit(0);
    }
    else {
        command = argv[1];
    }

    if (strcmp(command, "RQ") == 0) {
        processName = argv[2];
        amountMemory = atoi(argv[3]);
        typeOfFit = argv[4];
    }
    else if (strcmp(command, "RL") == 0) {
        processName = argv[2];
    }
}