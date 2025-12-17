#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    // Child process
    if (child_pid == 0) {
        printf("### Child ###\nCurrnet PID: %d\nChild PID: %d\n", getpid(), child_pid);
    } else {
        printf("### Parent ###\nCurrnet PID: %d\nChild PID: %d\n", getpid(), child_pid);
    }
    return 0;
}
