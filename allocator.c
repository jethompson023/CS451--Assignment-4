/*
    Author: Jeremiah Thompson & Reis Ciaramitaro
    Assignment Number: 4
    Date of Submission: 
    Name of this file: allocator.c
    Short description of contents:
    This program is focus on performing some memory allocation in four different methods. 
        1) Request for a contiguous block of membory
        2) Release of a contiguous block of memory
        3) Compact unused holes of memory into one single block
        4) Report the regions of free and allocated memory
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

char command[4];
char processName[2];
char amountMemory[100];
int currProcessMemory;
int maxMemory;
char typeOfFit[1];

void parseArgs(char userArgs[]);
int checkInitialArgs(int argc, char* argv[]);
void setInitialValues(int mainMemory[]);
void requestMemory(int mainMemory[], char processName[], int currProcessMemory, char typeOfFit[]);
void releaseMemory(int mainMemory[], char processName[]);
void compactMemory(int mainMemory[]);
void printStats(int mainMemory[]);
bool determineFit(int mainMemory[], int currProcessMemory);
void bestFit(int mainMemory[], char processName[], int currProcessMemory);
void worstFit(int mainMemory[], char processName[], int currProcessMemory);
void firstFit(int mainMemory[], char processName[], int currProcessMemory);
void resetArgs();



void setInitialValues(int mainMemory[]) {
    for(int i=0;i<=maxMemory;i++) {
        mainMemory[i] = -1;
    }
    mainMemory[0] = -1;
    mainMemory[1] = 2;
    mainMemory[2] = 2;
    mainMemory[3] = 2;
    mainMemory[4] = 2;
    mainMemory[5] = 2;
    mainMemory[6] = -1;
    mainMemory[7] = 3;
    mainMemory[8] = 3;
    mainMemory[9] = 3;
}


bool determineFit(int mainMemory[], int currProcessMemory) {
    return true;
}


void bestFit(int mainMemory[], char processName[], int currProcessMemory) {

}


void worstFit(int mainMemory[], char processName[], int currProcessMemory) {

}


void firstFit(int mainMemory[], char processName[], int currProcessMemory) {

}



void requestMemory(int mainMemory[], char processName[], int currProcessMemory, char typeOfFit[]) {
    if (determineFit(mainMemory, currProcessMemory)) {
        if (strcmp(typeOfFit, "B") == 0) {
            bestFit(mainMemory, processName, currProcessMemory);
        }
        else if (strcmp(typeOfFit, "W") == 0) {
            worstFit(mainMemory, processName, currProcessMemory);
        }
        else if (strcmp(typeOfFit, "F") == 0) {
            firstFit(mainMemory, processName, currProcessMemory);
        }
        else {
            printf("No algorithm specified\n");
        }
    }
    else {
        printf("No memory available for allocation\n");
    }
}


void releaseMemory(int mainMemory[], char processName[]) {
    int processNumber = atoi(processName);
    for(int i=0;i<maxMemory;i++) {
        if (mainMemory[i] == processNumber)
            mainMemory[i] = -1;
    }
}


void compactMemory(int mainMemory[]) {
    bool again = true;
    int beginningOfHole = -1, beginningOfNextProcess = -1; //-1 means no available hole
    int i = 0;

    while (again) {
        if (beginningOfHole == -1) { //when first hole is not found
            if (i == maxMemory - 1) //if no holes were found
                again=false;

            if (mainMemory[i] == -1) { //index of first hole found
                beginningOfHole = i;
            }
        }
        else { //while first hole is found
            if (beginningOfNextProcess == -1) { //while immediate next process is not found
                if (mainMemory[i] != -1) { //index of first next process to be compacted
                    beginningOfNextProcess = i;
                }
                if (i == maxMemory-1)
                    again=false;
            }
            else { //while immediate next process is found begin compacting
                mainMemory[beginningOfHole] = mainMemory[beginningOfNextProcess];
                mainMemory[beginningOfNextProcess] = -1;
                if (beginningOfNextProcess == maxMemory-1) {
                    beginningOfHole = -1;
                    beginningOfNextProcess = -1;
                    i = 0;
                }
                else {
                    beginningOfHole++;
                    beginningOfNextProcess++;
                }
            }
        }
        i++;
    }
}


void printStats(int mainMemory[]) {
    int beginning = 0, prev = mainMemory[0];

    for(int i=1;i<maxMemory;i++) {
        prev = mainMemory[i-1];
        if (prev != mainMemory[i]) {
            if (mainMemory[beginning] == -1) {
                printf("Addresses [%d:%d] Unused\n", beginning, i-1);
            }
            else {
                printf("Addresses [%d:%d] Process P%d\n", beginning, i-1, mainMemory[beginning]);
            }
            
            beginning = i;
        }
    }
    if (mainMemory[beginning] == -1) {
        printf("Addresses [%d:%d] Unused\n", beginning, maxMemory-1);
    }
    else {
        printf("Addresses [%d:%d] Process P%d\n", beginning, maxMemory-1, mainMemory[beginning]);
    }
}

/*
    Function Name: main
    Input to the method: 
    Output(Return value): Print 
    Brief description of the task:
*/
int main(int argc, char* argv[]) {

    bool run = true;
    maxMemory = checkInitialArgs(argc, argv);
    int mainMemory[maxMemory];
    setInitialValues(mainMemory);

    while(run) {
        char userArgs[100];

        
        printf("Allocator> ");
        fgets(userArgs, sizeof userArgs, stdin);	
        parseArgs(userArgs);        
        
        if (strcmp(command, "RQ") == 0) {
            printf("Requesting Memory\n");
            requestMemory(mainMemory, processName, currProcessMemory, typeOfFit);
        }
        else if (strcmp(command, "RL") == 0) {
            printf("Releasing Memory\n");
            releaseMemory(mainMemory, processName);
        }
        else if (strcmp(command, "C") == 0) {
            printf("Compacting Memory\n");
            compactMemory(mainMemory);
        }
        else if (strcmp(command, "STAT") == 0) {
            printf("Printing Stats\n");
            printStats(mainMemory);
        }
        else if (strcmp(command, "X") == 0) {
            printf("Exiting...\n");
            run = false;
        } else {
            printf("Command Not Supported\n");
            compactMemory(mainMemory);
        }
    }
}

int checkInitialArgs(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Necessary arguments are missing, exiting...\n");
        exit(0);
    }
    else {
        return maxMemory = atoi(argv[1]);
    }
}

void resetArgs() {
    for(int i=0;i<=(strlen(command));i++) {
        command[i] = '\0';
    }
    for(int i=0;i<=(strlen(processName));i++) {
        processName[i] = '\0';
    }
    for(int i=0;i<=(strlen(amountMemory));i++) {
        amountMemory[i] = '\0';
    }
    for(int i=0;i<=(strlen(typeOfFit));i++) {
        typeOfFit[i] = '\0';
    }
}

void parseArgs(char userArgs[]) {
    int argCount = 0;
    int charIndex = 0;

    resetArgs();

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
                    currProcessMemory = atoi(amountMemory);
                    break;
                case 3:
                    typeOfFit[charIndex] = '\0';
                    break;
            }
            argCount++;
            charIndex = 0;
        }
        else if (userArgs[i]=='\0' || userArgs[i] == '\n') {
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
                    processName[charIndex] = userArgs[i+1];
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