#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

#define VSH_RL_BUFSIZE 1024
#define VSH_TOK_BUFSIZE 64
#define VSH_TOK_DELIM " \t\r\n\a"

char *get_username() {
    struct passwd *pwd;
    pwd = getpwuid(geteuid());
    return pwd->pw_name;
}

int vsh_cd(char **args);
int vsh_help(char **args);
int vsh_exit(char ** args);

char *builtin_str[] = { "cd", "help", "exit" };

int (*builtin_func[])(char **) = {
    vsh_cd,
    vsh_help,
    vsh_exit
};

int vsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

char *vsh_read_line(void) {
	int bufsize = VSH_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;
	if (!buffer) {
		fprintf(stderr, "vsh: Allocation Error\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
		c = getchar();

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position] = c;
		}
		position++;
	}

	// If exceeded the buffer size
	if (position >= bufsize) {
		bufsize += VSH_RL_BUFSIZE;
		buffer = realloc(buffer, bufsize);
		if (!buffer) {
			fprintf(stderr, "vsh: Allocation Error\n");
			exit(EXIT_FAILURE);
		}
	}
}

char **vsh_split_line(char *line) {
	int bufsize = VSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;
	if (!tokens) {
		fprintf(stderr, "vsh: Allocation Error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, VSH_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;
		if (position >= bufsize) {
			bufsize += VSH_TOK_BUFSIZE;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens) {
				fprintf(stderr, "vsh: Allocation Error\n");
				exit(EXIT_FAILURE);
			}
		}
        token = strtok(NULL, VSH_TOK_DELIM);
	}
    tokens[position] = NULL;
    return tokens;
}

int vsh_launch(char **args) {
    pid_t pid, wpid;
    int status;
    
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("vsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("vsh");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int vsh_execute(char **args) {
    if (args[0] == NULL)
        return 1;
    
    for (int i = 0; i < vsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    }
    return vsh_launch(args);
}

void vsh_loop(void) {
	char *line;
	char **args;
	int status;
    char *username = get_username();
    char hostname[256];
    size_t psize = 100;
    char *path = (char*)malloc(psize * sizeof(char));
    gethostname(hostname, sizeof(hostname));

	do {
        if (getcwd(path, psize) == NULL) {
            perror("path");
            free(path);
            exit(EXIT_FAILURE);
        }
		printf("%s@%s %s#> ", username, hostname, path);
		line = vsh_read_line();
        if (line == NULL) {
            printf("\n");
            exit(0);
        }
		args = vsh_split_line(line);
		status = vsh_execute(args);

		free(line);
		free(args);
    } while (status);
    free(path);
}

int main(int argc, char *argv[]) {
	vsh_loop();
	return EXIT_SUCCESS;
}

int vsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "vsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0)
            perror("vsh");
    }
    return 1;
}

int vsh_help(char **args) {
    printf("Vatsal's VSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    for (int i = 0; i < vsh_num_builtins(); i++) 
        printf("    %s\n", builtin_str[i]);
    return 1;
}

int vsh_exit(char **args) {
    return 0;
}
