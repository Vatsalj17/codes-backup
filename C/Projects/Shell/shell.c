/*
 * chad_shell.c - A Gen Z themed shell with meme references
 * Compilation: gcc -o chadshell chad_shell.c
 * Usage: ./chadshell
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_TOKENS 100
#define HISTORY_SIZE 10

// Color codes for terminal output
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Gen Z reactions array
const char* genz_reactions[] = {
    "no cap fr fr",
    "that's so based",
    "sheesh, ok I guess",
    "bussin command ngl",
    "slay!",
    "yikes, that command ain't it chief",
    "living for this command",
    "idk that's kinda mid",
    "rent free in my command history",
    "absolutely unhinged command",
    "this command passes the vibe check",
    "certified rizz command",
    "big yikes",
    "sus command but we move",
    "this command ate and left no crumbs"
};

// Meme quotes array
const char* meme_quotes[] = {
    "It's giving... system process vibes",
    "Chad shell doesn't simply exit. It YEETS itself out",
    "Tell me you're a Linux user without telling me you're a Linux user",
    "POV: You're using the most based shell ever",
    "The feminine urge to execute every command flawlessly",
    "Not me successfully executing your commands",
    "*Chad shell noises intensify*",
    "This command will be legendary!",
    "This is the way... to execute commands",
    "You wouldn't get these errors in other shells",
    "Chad shell: I'm built different",
    "Touch grass? After I execute this command",
    "We do a little trolling with your filesystem",
    "Skill issue? Try 'help'",
    "Chad shell: exists, other shells: and I took that personally"
};

// Function prototypes
void display_welcome();
char* read_command();
char** parse_command(char* command);
int execute_command(char** args);
int check_builtin(char** args);
void execute_builtin(char** args, int builtin_index);
void display_history(char* history[], int history_count);
void free_tokens(char** tokens);
char* get_random_reaction();
char* get_random_meme();

// Built-in commands
const char* builtins[] = {
    "exit",
    "help",
    "history",
    "vibe",
    "meme",
    "chad",
    "cd"
};

int main() {
    char* command;
    char** args;
    int status = 1;
    int history_count = 0;
    char* command_history[HISTORY_SIZE];
    
    // Initialize random number generator
    srand(time(NULL));
    
    // Initialize history
    for (int i = 0; i < HISTORY_SIZE; i++) {
        command_history[i] = NULL;
    }

    // Display welcome message
    display_welcome();

    // Main shell loop
    while (status) {
        printf(ANSI_COLOR_CYAN "chad_shell" ANSI_COLOR_RESET ":" 
               ANSI_COLOR_BLUE "~$" ANSI_COLOR_RESET " ");
        
        command = read_command();
        
        // Skip empty commands
        if (command[0] == '\0') {
            free(command);
            continue;
        }

        // Add to history
        if (history_count < HISTORY_SIZE) {
            command_history[history_count++] = strdup(command);
        } else {
            free(command_history[0]);
            for (int i = 1; i < HISTORY_SIZE; i++) {
                command_history[i-1] = command_history[i];
            }
            command_history[HISTORY_SIZE-1] = strdup(command);
        }
        
        args = parse_command(command);
        status = execute_command(args);
        
        free_tokens(args);
        free(command);
    }
    
    // Free history
    for (int i = 0; i < HISTORY_SIZE; i++) {
        if (command_history[i] != NULL) {
            free(command_history[i]);
        }
    }

    return 0;
}

void display_welcome() {
    printf("\n");
    printf(ANSI_COLOR_MAGENTA "╔══════════════════════════════════════════════════════════╗\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║                                                          ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_CYAN "  _____ _               _  _____ _          _ _       " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_CYAN " / ____| |             | |/ ____| |        | | |      " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_CYAN "| |    | |__   __ _  __| | (___ | |__   ___| | |      " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_CYAN "| |    | '_ \\ / _` |/ _` |\\___ \\| '_ \\ / _ \\ | |      " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_CYAN "| |____| | | | (_| | (_| |____) | | | |  __/ | |      " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_CYAN " \\_____|_| |_|\\__,_|\\__,_|_____/|_| |_|\\___|_|_|      " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║                                                          ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_GREEN "The most based shell fr fr no cap                     " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║  " ANSI_COLOR_YELLOW "Type 'help' to see available commands                 " ANSI_COLOR_MAGENTA "  ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "║                                                          ║\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "╚══════════════════════════════════════════════════════════╝\n" ANSI_COLOR_RESET);
    printf("\n");
}

char* read_command() {
    char* command = malloc(MAX_COMMAND_LENGTH * sizeof(char));
    if (!command) {
        perror("chad_shell: allocation error");
        exit(EXIT_FAILURE);
    }
    
    // Get input
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        // Handle EOF (Ctrl+D)
        printf("\nChadding out... bye bestie!\n");
        free(command);
        exit(EXIT_SUCCESS);
    }
    
    // Remove trailing newline
    size_t length = strlen(command);
    if (length > 0 && command[length-1] == '\n') {
        command[length-1] = '\0';
    }
    
    return command;
}

char** parse_command(char* command) {
    int position = 0;
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));
    char* token;
    
    if (!tokens) {
        perror("chad_shell: allocation error");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(command, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;
        
        if (position >= MAX_TOKENS) {
            fprintf(stderr, "chad_shell: too many arguments\n");
            exit(EXIT_FAILURE);
        }
        
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

int execute_command(char** args) {
    if (args[0] == NULL) {
        // Empty command
        return 1;
    }
    
    // Check if it's a built-in command
    int builtin_index = check_builtin(args);
    if (builtin_index >= 0) {
        execute_builtin(args, builtin_index);
        
        // Exit shell if exit command was executed
        if (strcmp(args[0], "exit") == 0) {
            return 0;
        }
        
        return 1;
    }
    
    // Not a built-in command, fork and execute
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            printf(ANSI_COLOR_RED "chad_shell: command not found: %s\n" ANSI_COLOR_RESET, args[0]);
            printf("that's lowkey cringe, bestie. try something else 💀\n");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Error forking
        perror(ANSI_COLOR_RED "chad_shell: forking error" ANSI_COLOR_RESET);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        
        // 20% chance to print a random reaction
        if (rand() % 5 == 0) {
            printf("%s\n", get_random_reaction());
        }
    }
    
    return 1;
}

int check_builtin(char** args) {
    int num_builtins = sizeof(builtins) / sizeof(char*);
    
    for (int i = 0; i < num_builtins; i++) {
        if (strcmp(args[0], builtins[i]) == 0) {
            return i;
        }
    }
    
    return -1;
}

void execute_builtin(char** args, int builtin_index) {
    switch (builtin_index) {
        case 0: // exit
            printf("aight imma head out... *chad leaves*\n");
            break;
        
        case 1: // help
            printf(ANSI_COLOR_GREEN "Chad Shell - Help Menu (absolutely bussin fr fr)\n" ANSI_COLOR_RESET);
            printf("Built-in commands:\n");
            printf("  %-10s - Exit the shell (no cap)\n", "exit");
            printf("  %-10s - Display this help menu (skill issue solved)\n", "help");
            printf("  %-10s - Show command history (receipts)\n", "history");
            printf("  %-10s - Get random Gen Z reaction (it's giving validation)\n", "vibe");
            printf("  %-10s - Get random meme quote (based)\n", "meme");
            printf("  %-10s - Display chad ASCII art (gigachad energy)\n", "chad");
            printf("  %-10s - Change directory (teleport fr)\n", "cd");
            printf("\nAny other command will be passed to the system.\n");
            break;
        
        case 2: // history
            printf(ANSI_COLOR_YELLOW "Command History (the receipts):\n" ANSI_COLOR_RESET);
            // Placeholder for history functionality
            printf("history feature coming soon besties, stay tuned! 💅\n");
            break;
        
        case 3: // vibe
            printf("%s\n", get_random_reaction());
            break;
        
        case 4: // meme
            printf("%s\n", get_random_meme());
            break;
        
        case 5: // chad
            printf(ANSI_COLOR_CYAN);
            printf("⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠛⠋⠉⠉⠉⠉⠉⠉⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⡏⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿\n");
            printf("⣿⣿⣿⢏⣴⣿⣷⠀⠀⠀⠀⠀⢾⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿\n");
            printf("⣿⣿⣟⣾⣿⡟⠁⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣷⢢⠀⠀⠀⠀⠀⠀⠀⢸⣿\n");
            printf("⣿⣿⣿⣿⣟⠀⡴⠄⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⣿\n");
            printf("⣿⣿⣿⠟⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⢴⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⣿\n");
            printf("⣿⣁⡀⠀⠀⢰⢠⣦⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⡄⠀⣴⣶⣿⡄⣿\n");
            printf("⣿⡋⠀⠀⠀⠎⢸⣿⡆⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⠗⢘⣿⣟⠛⠿⣼\n");
            printf("⣿⣿⠋⢀⡌⢰⣿⡿⢿⡀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣧⢀⣼\n");
            printf("⣿⣿⣷⢻⠄⠘⠛⠋⠛⠃⠀⠀⠀⠀⠀⢿⣧⠈⠉⠙⠛⠋⠀⠀⠀⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣧⠀⠈⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠀⠀⠀⠀⢀⢃⠀⠀⢸⣿⣿⣿⣿\n");
            printf("⣿⣿⡿⠀⠴⢗⣠⣤⣴⡶⠶⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡸⠀⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⡀⢠⣾⣿⠏⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠉⠀⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣧⠈⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⡄⠈⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣿⣦⣄⣀⣀⣀⣀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠙⣿⣿⡟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠁⠀⠀⠹⣿⠃⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢐⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
            printf("⣿⣿⣿⣿⠿⠛⠉⠉⠁⠀⢻⣿⡇⠀⠀⠀⠀⠀⠀⢀⠈⣿⣿⡿⠉⠛⠛⠛⠉⠉\n");
            printf("⣿⡿⠋⠁⠀⠀⢀⣀⣠⡴⣸⣿⣇⡄⠀⠀⠀⠀⢀⡿⠄⠙⠛⠀⣀⣠⣤⣤⠄⠀\n" ANSI_COLOR_RESET);
            printf("Gigachad has entered the chat 💯\n");
            break;
        
        case 6: // cd
            if (args[1] == NULL) {
                // No argument provided, go to home directory
                if (chdir(getenv("HOME")) != 0) {
                    perror("chad_shell: cd error");
                } else {
                    printf("teleported to home base 🏠\n");
                }
            } else {
                if (chdir(args[1]) != 0) {
                    perror("chad_shell: cd error");
                    printf("yikes, can't go there bestie 🚫\n");
                } else {
                    printf("teleported to %s ✨\n", args[1]);
                }
            }
            break;
    }
}

void display_history(char* history[], int history_count) {
    printf(ANSI_COLOR_YELLOW "Command History (the receipts):\n" ANSI_COLOR_RESET);
    
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

void free_tokens(char** tokens) {
    // We don't free individual tokens since they point to parts of the command string
    free(tokens);
}

char* get_random_reaction() {
    int num_reactions = sizeof(genz_reactions) / sizeof(char*);
    int index = rand() % num_reactions;
    return (char*)genz_reactions[index];
}

char* get_random_meme() {
    int num_memes = sizeof(meme_quotes) / sizeof(char*);
    int index = rand() % num_memes;
    return (char*)meme_quotes[index];
}
