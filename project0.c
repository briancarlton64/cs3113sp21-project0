#include <stdio.h>
#include <stdlib.h>

#define MAX_PID 32768
#define NUM_IDEN 3
#define PROGRAM_OFFSET 2
#define PID 0
#define BURST 1
#define EMPTY_PROCESS 0


int voluntarySwitches(int processArray[MAX_PID][NUM_IDEN]) {
    int seenPids[MAX_PID] = {};
    int numSwitches = 0;
    for (int index = PROGRAM_OFFSET; index < MAX_PID; index++) {
        if (processArray[index][PID] == EMPTY_PROCESS) {
            break;
        }
        if (!seenPids[processArray[index][PID]]) {
            numSwitches++;
            seenPids[processArray[index][PID]] = 1;
        }
    }
    return numSwitches;
}

int involuntarySwitches(int processArray[MAX_PID][NUM_IDEN]) {
    int seenPids[MAX_PID] = {};
    int numSwitches = 0;
    for (int index = PROGRAM_OFFSET; index < MAX_PID; index++) {
        if (processArray[index][PID] == EMPTY_PROCESS) {
            break;
        }
        if (!seenPids[processArray[index][PID]]) {

            seenPids[processArray[index][PID]] = 1;
        } else if (processArray[index - 1][PID] != processArray[index][PID]) {
            numSwitches++;
        }
    }
    return numSwitches;
}

int waitTimes(int processArray[MAX_PID][NUM_IDEN]) {
    int waitTimes[MAX_PID] = {};
    int currentPid;
    int totalTime = 0;
    for (int index = PROGRAM_OFFSET; index < MAX_PID; index++) {
        currentPid = processArray[index][PID];
        if (currentPid == EMPTY_PROCESS) {
            break;
        }
        if (index == PROGRAM_OFFSET) {
            waitTimes[index] = 0;
        } else {
            for (int backIndex = index - 1; backIndex >= PROGRAM_OFFSET; backIndex--) {
                if (processArray[backIndex][PID] == currentPid) {
                    break;
                }
                waitTimes[index] += processArray[backIndex][BURST];
            }
        }
    }
    for (int index = 0; index < MAX_PID; index++) {
        totalTime += waitTimes[index];
    }
    return totalTime;
}

int responseTimes(int processArray[MAX_PID][NUM_IDEN]) {
    int waitTimes[MAX_PID] = {};
    int seenPids[MAX_PID] = {};
    int currentPid;
    int totalTime = 0;
    for (int index = PROGRAM_OFFSET; index < MAX_PID; index++) {
        currentPid = processArray[index][PID];
        if (currentPid == EMPTY_PROCESS) {
            break;
        }
        if (index == PROGRAM_OFFSET) {
            waitTimes[index] = 0;
            seenPids[currentPid] = 1;
        } else if (!seenPids[currentPid]) {
            for (int backIndex = index - 1; backIndex >= PROGRAM_OFFSET; backIndex--) {

                waitTimes[index] += processArray[backIndex][BURST];
                seenPids[currentPid] = 1;
            }
        }
    }
    for (int index = 0; index < MAX_PID; index++) {
        totalTime += waitTimes[index];
    }
    return totalTime;
}

int turnAroundTimes(int processArray[MAX_PID][NUM_IDEN]) {
    int waitTimes[MAX_PID] = {};
    int currentPid;
    int totalTime = 0;
    for (int index = PROGRAM_OFFSET; index < MAX_PID; index++) {
        currentPid = processArray[index][PID];
        waitTimes[index] += processArray[index][BURST];
        if (currentPid == EMPTY_PROCESS) {
            break;
        }
        for (int backIndex = index - 1; backIndex >= PROGRAM_OFFSET; backIndex--) {
            if (processArray[backIndex][PID] == currentPid) {
                break;
            }
            waitTimes[index] += processArray[backIndex][BURST];
        }
    }
    for (int index = 0; index < MAX_PID; index++) {
        totalTime += waitTimes[index];
    }
    return totalTime;
}

int totalTime(int processArray[MAX_PID][NUM_IDEN]) {
    int time = 0;
    for (int index = PROGRAM_OFFSET; index < MAX_PID; index++) {
        time += processArray[index][BURST];
    }
    return time;
}


int main() {
    int processArray[MAX_PID][NUM_IDEN] = {};
    char currentChar;
    int lineIndex = 0;
    int columnIndex = 0;
    int currentInt;
    while ((currentChar = getchar()) != EOF) {

        if (currentChar == '\n') {
            lineIndex++;
            columnIndex = 0;
        }
        if(currentChar == '\r'){

        }
        else if (currentChar == ' ' ){
            columnIndex++;
        }
        else{
            currentInt = atoi(&currentChar);
            processArray[lineIndex][columnIndex] = currentInt;
        }
    }
    int numElem = processArray[1][0];
    int waitTime = (waitTimes(processArray));
    int volSwitch = voluntarySwitches(processArray);
    int involSwitch = involuntarySwitches(processArray);
    int responseTime = responseTimes(processArray);
    int turnAroundTime = turnAroundTimes(processArray);
    float throughPut = (float) numElem / (float) totalTime(processArray);
    printf("%d \n", volSwitch);
    printf("%d \n", involSwitch);
    printf("%.2f \n", (float) 100);
    printf("%.2f \n", throughPut);
    printf("%.2f \n", (float) turnAroundTime / (float) numElem);
    printf("%.2f \n", (float) waitTime / (float) numElem);
    printf("%.2f \n", (float) responseTime / (float) numElem);
}
