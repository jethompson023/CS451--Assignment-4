#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

char command[4];
char processName[2];
char amountMemory[100];
int maxMemory;
char typeOfFit[1];
void parseArgs(char userArgs[]);
void checkInitialArgs(int argc, char* argv[]);


int main(int argc, char* argv[]) {

    checkInitialArgs(argc, argv);
    while(true) {
        char userArgs[100];

        
        printf("Allocator> ");
        fgets(userArgs, sizeof userArgs, stdin);	
        parseArgs(userArgs);

        printf("Command is %s, processName is %s, amount is %s, type is %s\n", command, processName, amountMemory, typeOfFit);
    }
}

void checkInitialArgs(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Necessary arguments are missing, exiting...\n");
        exit(0);
    }
    else {
        maxMemory = atoi(argv[1]);
    }
}

void parseArgs(char userArgs[]) {
    int argCount = 0;
    int charIndex = 0;

    for(int i=0;i<=(strlen(userArgs));i++) {
        // if space or NULL found, assign NULL into newString[ctr]
        if(userArgs[i]== ' ') {
            switch(argCount) {
                case 0:
                    command[charIndex] = '\0';
                    break;
                case 1:
                    processName[charIndex] = '\0';
                    break;
                case 2:
                    amountMemory[charIndex] = '\0';
                    break;
                case 3:
                    typeOfFit[charIndex] = '\0';
                    break;
            }
            argCount++;
            charIndex = 0;
        }
        else if (userArgs[i]=='\0') {
            break;
        }
        else
        {
            switch(argCount) {
                case 0:
                    command[charIndex] = userArgs[i];
                    charIndex++;
                    break;
                case 1:
                    processName[charIndex] = userArgs[i];
                    charIndex++;
                    break;
                case 2:
                    amountMemory[charIndex] = userArgs[i];
                    charIndex++;
                    break;
                case 3:
                    typeOfFit[charIndex] = userArgs[i];
                    charIndex++;
                    break;
            }
        }
    }
}