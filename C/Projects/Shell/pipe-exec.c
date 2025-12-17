#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int pipe_counter(char **cmd) {
	int c = 0;
	for (int i = 0; cmd[i] != NULL; i++) {
		if (strcmp(cmd[i], "|") == 0) c++;
	}
	return c;
}

void exec_pipe(char ***ncmds, int i, int n) {
	int fd[2];
	if (pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	int pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		dup2(fd[1], STDOUT_FILENO);	 // redirect stdout to pipe
		close(fd[0]);
		close(fd[1]);
		execvp(ncmds[i][0], ncmds[i]);
		printf("Invalid Command\n");
		exit(EXIT_FAILURE);
	} else {
		dup2(fd[0], STDIN_FILENO);	// redirect stdin to pipe
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);  // wait for the child to prevent zombies
		if (i == n - 2) {
			execvp(ncmds[i + 1][0], ncmds[i + 1]);
			printf("Invalid Command\n");
			exit(EXIT_FAILURE);
		} else
			exec_pipe(ncmds, i + 1, n);
	}
}

int is_invalid_pipe_syntax(char **cmd) {
    if (cmd[0] == NULL || strcmp(cmd[0], "|") == 0) return 1;
    for (int i = 0; cmd[i] != NULL; i++) {
        if (strcmp(cmd[i], "|") == 0 && (cmd[i + 1] == NULL || strcmp(cmd[i + 1], "|") == 0)) {
            return 1;
        }
    }
    return 0;
}

int main() {
	// char *cmd[] = {"tree", "-a", "|", "shuf", "|", "less", "|", "wc", "-l", NULL}; 
    // char *cmd[] = {"tree", "-a", "|", "grep", "-i", "sh", "|", "wc",
	// NULL}; char *cmd[] = {"seq", "10", "|", "tac", NULL};
	// char *cmd[] = {"ls", "|", "|", "head", "-n", "5", NULL};
	char *cmd[] = {"ls", "-a", "|", "wc", "-l", NULL};
    if (is_invalid_pipe_syntax(cmd)) {
        fprintf(stderr, "error: invalid pipe usage\n");
        return 1;
    }
	int count = pipe_counter(cmd);
	printf("No. of pipes: %d\n", count);
	int n = count + 1;
	char ***ncmds = malloc(n * sizeof(char **));
	for (int i = 0; i < n; i++) {
		ncmds[i] = malloc(64 * sizeof(char *));
	}
	int index = 0, sub_i = 0;
	for (int i = 0; cmd[i] != NULL; i++) {
		if (strcmp(cmd[i], "|") == 0) {
			ncmds[index][sub_i] = NULL;
			sub_i = 0;
			index++;
			continue;
		}
		ncmds[index][sub_i++] = cmd[i];
	}
    ncmds[index][sub_i] = NULL;
	for (int i = 0; i < n; i++) {
		printf("Arr[%d]: { ", i);
		for (int j = 0; ncmds[i][j] != NULL; j++) {
			printf("\"%s\" ", ncmds[i][j]);
		}
		printf("}\n");
	}
	exec_pipe(ncmds, 0, n);
	// printf("n = %d", n);
    return 0;
}
