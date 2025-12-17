#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    pid_t wait_result;
    int stat_loc;

    child_pid = fork();

    if (child_pid == 0) {
        printf("### Child ###\nCurrnet PID: %d\nChild PID: %d\n", getpid(), child_pid);
        sleep(1); // Sleep for one second
    } else {
        wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
        printf("### Parent ###\nCurrnet PID: %d\nChild PID: %d\n", getpid(), child_pid);
    }
    return 0;
}
