#include "memes.h"

// External function declarations
extern int execute_builtin(char** args);
extern int execute_command(char** args);

typedef struct {
    char** args;
    int argc;
    char* input_file;
    char* output_file;
    int background;
    int append_output;
} Command;

// Function declarations
Command* parse_command(char* input);
void free_command(Command* cmd);
int handle_pipes(char* input);

int parse_and_execute(char* input) {
    // Handle empty input (not very sigma)
    if (!input || strlen(input) == 0) {
        return 0;
    }
    
    // Check for pipes (advanced chad behavior)
    if (strchr(input, '|')) {
        return handle_pipes(input);
    }
    
    // Parse single command
    Command* cmd = parse_command(input);
    if (!cmd) {
        print_error(ERR_SYNTAX);
        return 1;
    }
    
    int result = 0;
    
    // Check if it's a builtin (the VIP commands)
    if (execute_builtin(cmd->args)) {
        result = 0;  // Builtins handle their own success/fail
    } else {
        // External command (delegate to executor)
        result = execute_command(cmd->args);
    }
    
    free_command(cmd);
    return result;
}

Command* parse_command(char* input) {
    Command* cmd = malloc(sizeof(Command));
    if (!cmd) return NULL;
    
    // Initialize command structure
    cmd->args = malloc(sizeof(char*) * MAX_ARGS);
    cmd->argc = 0;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->background = 0;
    cmd->append_output = 0;
    
    // Check for background execution (& at end)
    int len = strlen(input);
    if (len > 0 && input[len-1] == '&') {
        cmd->background = 1;
        input[len-1] = '\0';  // Remove &
    }
    
    // Tokenize input (split by spaces)
    char* token = strtok(input, " \t");
    while (token && cmd->argc < MAX_ARGS - 1) {
        // Handle redirection operators
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t");
            if (token) cmd->output_file = strdup(token);
        } else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " \t");
            if (token) {
                cmd->output_file = strdup(token);
                cmd->append_output = 1;
            }
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t");
            if (token) cmd->input_file = strdup(token);
        } else {
            // Regular argument
            cmd->args[cmd->argc++] = strdup(token);
        }
        token = strtok(NULL, " \t");
    }
    
    cmd->args[cmd->argc] = NULL;
    return cmd;
}

int handle_pipes(char* input) {
    // Split by pipe character
    char* commands[10];  // Max 10 piped commands (that's sigma energy)
    int cmd_count = 0;
    
    char* cmd = strtok(input, "|");
    while (cmd && cmd_count < 10) {
        // Trim whitespace
        while (*cmd == ' ' || *cmd == '\t') cmd++;
        commands[cmd_count++] = cmd;
    }
    
    if (cmd_count < 2) {
        print_error("pipe without commands? that's sus");
        return 1;
    }
    
    // Create pipes
    int pipes[cmd_count-1][2];
    for (int i = 0; i < cmd_count-1; i++) {
        if (pipe(pipes[i]) < 0) {
            print_error("pipe creation failed (not very chad)");
            return 1;
        }
    }
    
    // Execute piped commands
    for (int i = 0; i < cmd_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process setup
            if (i > 0) {  // Not first command
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            if (i < cmd_count-1) {  // Not last command  
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            // Close all pipe descriptors
            for (int j = 0; j < cmd_count-1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            // Parse and execute this command
            Command* cmd_struct = parse_command(commands[i]);
            if (cmd_struct) {
                execvp(cmd_struct->args[0], cmd_struct->args);
            }
            exit(127);
        }
    }
    
    // Parent: close pipes and wait
    for (int i = 0; i < cmd_count-1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    // Wait for all children (sigma patience)
    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }
    
    return 0;
}

void free_command(Command* cmd) {
    if (!cmd) return;
    
    for (int i = 0; i < cmd->argc; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
    
    if (cmd->input_file) free(cmd->input_file);
    if (cmd->output_file) free(cmd->output_file);
    free(cmd);
}
