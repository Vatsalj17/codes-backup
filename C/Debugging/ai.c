
#include <stdio.h>

// Define states
enum States { IDLE, RECEIVING, SENDING };

// Define actions
enum Actions { WAIT, START_SENDING, STOP_SENDING };

typedef struct {
    enum States currentState;
    enum Actions action;
} AI;

AI ai = { .currentState = IDLE };

void nextState(enum Actions action) {
    switch (ai.currentState) {
        case IDLE:
            if (action == START_SENDING)
                ai.currentState = RECEIVING;
            break;
        case RECEIVING:
            // Add logic for receiving data here
            ai.currentState = IDLE;
            break;
        case SENDING:
            // Add logic for sending data here
            ai.currentState = IDLE;
            break;
    }
}

int main() {
    while (1) {
        printf("Current state: %s\n", ai.currentState == IDLE ? "IDLE" :
                                          ai.currentState == RECEIVING ? "RECEIVING" : "SENDING");

        nextState(WAIT); // Assume some external event triggers the action
    }

    return 0;
}

