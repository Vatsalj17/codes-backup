#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // The Child Process
        printf("### Child ###\nCurrnet PID: %d\nChild PID: %d\n", getpid(), child_pid);
    } else {
        // Parent Process
        sleep(1);
        printf("### Parent ###\nCurrnet PID: %d\nChild PID: %d\n", getpid(), child_pid);
    }
    return 0;
}

// Similarly a sleep_child.c can also be created by adding the sleep function in if instead of else
