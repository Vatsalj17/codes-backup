#include "memes.h"

// External declarations
extern char** environ;
extern void add_to_history(char* cmd);
extern void print_success();

// Function declarations
int execute_command(char** args);
int execute_with_redirection(char** args, char* input_file, char* output_file, int append);
char* find_command_path(char* cmd);
void setup_signal_handlers();

static int last_exit_code = 0;
static pid_t* background_jobs = NULL;
static int bg_job_count = 0;

int execute_command(char** args) {
    if (!args || !args[0]) {
        print_error(ERR_SYNTAX);
        return 1;
    }
    
    // Add to history (keeping receipts)
    char full_cmd[256] = "";
    for (int i = 0; args[i]; i++) {
        strcat(full_cmd, args[i]);
        if (args[i+1]) strcat(full_cmd, " ");
    }
    add_to_history(full_cmd);
    
    // Check if command exists (no cap)
    char* cmd_path = find_command_path(args[0]);
    if (!cmd_path && access(args[0], X_OK) != 0) {
        print_error(ERR_NOT_FOUND);
        return 127;
    }
    
    // Fork and execute (the sigma way)
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process (the chosen one)
        if (execvp(args[0], args) == -1) {
            print_error(ERR_NOT_FOUND);
            exit(127);
        }
    } else if (pid > 0) {
        // Parent process (the patient one)
        int status;
        waitpid(pid, &status, 0);
        last_exit_code = WEXITSTATUS(status);
        
        // Flex on successful commands
        if (last_exit_code == 0) {
            if (rand() % 5 == 0) {  // Random motivation
                print_success();
            }
            return 0;
        } else {
            // L command detected
            printf("command took an L (exit code: %d)\n", last_exit_code);
            return last_exit_code;
        }
    } else {
        print_error(ERR_FORK);
        return 1;
    }
    
    return 0;
}

int execute_with_redirection(char** args, char* input_file, char* output_file, int append) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Handle input redirection
        if (input_file) {
            FILE* in = fopen(input_file, "r");
            if (!in) {
                print_error(ERR_NO_FILE);
                exit(1);
            }
            dup2(fileno(in), STDIN_FILENO);
            fclose(in);
        }
        
        // Handle output redirection  
        if (output_file) {
            FILE* out = fopen(output_file, append ? "a" : "w");
            if (!out) {
                print_error("can't create output file (skill issue)");
                exit(1);
            }
            dup2(fileno(out), STDOUT_FILENO);
            fclose(out);
        }
        
        // Execute command
        execvp(args[0], args);
        print_error(ERR_NOT_FOUND);
        exit(127);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    } else {
        print_error(ERR_FORK);
        return 1;
    }
}

char* find_command_path(char* cmd) {
    // Check if it's already a full path
    if (strchr(cmd, '/')) {
        return access(cmd, X_OK) == 0 ? cmd : NULL;
    }
    
    // Search in PATH (sigma detective work)
    char* path_env = getenv("PATH");
    if (!path_env) return NULL;
    
    char* path_copy = strdup(path_env);
    char* dir = strtok(path_copy, ":");
    static char full_path[256];
    
    while (dir) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }
    
    free(path_copy);
    return NULL;
}

int execute_background(char** args) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child: detach from terminal (ghostmode activated)
        setpgid(0, 0);
        execvp(args[0], args);
        exit(127);
    } else if (pid > 0) {
        // Parent: track background job
        printf("[%d] started in ghostmode 👻\n", pid);
        
        // Expand background jobs array if needed
        background_jobs = realloc(background_jobs, sizeof(pid_t) * (bg_job_count + 1));
        background_jobs[bg_job_count++] = pid;
        
        return 0;
    } else {
        print_error(ERR_FORK);
        return 1;
    }
}

void check_background_jobs() {
    // Check for completed background jobs (cleaning up)
    for (int i = 0; i < bg_job_count; i++) {
        int status;
        pid_t result = waitpid(background_jobs[i], &status, WNOHANG);
        
        if (result > 0) {
            printf("[%d] job completed %s\n", 
                   background_jobs[i],
                   WEXITSTATUS(status) == 0 ? "(W)" : "(L)");
            
            // Remove from array (shift left)
            for (int j = i; j < bg_job_count - 1; j++) {
                background_jobs[j] = background_jobs[j + 1];
            }
            bg_job_count--;
            i--;  // Check same index again
        }
    }
}

void setup_signal_handlers() {
    // Ignore Ctrl+C in shell (we're built different)
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

int get_last_exit_code() {
    return last_exit_code;
}

void cleanup_executor() {
    // Clean up background jobs array
    if (background_jobs) {
        free(background_jobs);
        background_jobs = NULL;
    }
    bg_job_count = 0;
}
