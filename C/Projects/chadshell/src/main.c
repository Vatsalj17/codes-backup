#include "memes.h"

// Global state (keeping it simple fr)
static int last_exit_code = 0;
static int sigma_mode = 0;  // 0 = normal, 1 = sigma energy activated

// Function declarations
char* get_prompt();
void handle_builtin_rizz();
int is_meme_command(char* cmd, char** real_cmd);

int main() {
    char input[MAX_INPUT];
    
    // Seed random for success messages
    srand(getpid());
    
    // Drop the banner (no cap)
    print_banner();
    
    // Main shell loop (the grind never stops)
    while (1) {
        // Display that sigma prompt
        printf("%s", get_prompt());
        fflush(stdout);
        
        // Get user input
        if (!fgets(input, sizeof(input), stdin)) {
            printf("\nperiodt (EOF detected) 👋\n");
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Skip empty input (ain't nobody got time)
        if (strlen(input) == 0) continue;
        
        // Handle the command like a chad
        last_exit_code = parse_and_execute(input);
    }
    
    printf("chadsh logging off 😤💪\n");
    return 0;
}

char* get_prompt() {
    if (getuid() == 0) {
        return PROMPT_SIGMA;  // Root = sigma energy
    } else if (get_last_exit_code() == 0) {
        return sigma_mode ? PROMPT_W : PROMPT_CHAD;
    } else {
        return PROMPT_NPC;  // L command = NPC status
    }
}

// int parse_and_execute(char* input) {
//     // Handle exit command (periodt = dramatic exit)
//     if (strcmp(input, "periodt") == 0 || strcmp(input, "exit") == 0) {
//         printf("no cap, this was bussin 🔥👋\n");
//         exit(0);
//     }
//     
//     // Handle help (rizz = getting assistance)
//     if (strcmp(input, "rizz") == 0 || strcmp(input, "help") == 0) {
//         handle_builtin_rizz();
//         last_exit_code = 0;
//         return 0;
//     }
//     
//     // Handle sigma mode toggle
//     if (strcmp(input, "sigma") == 0) {
//         sigma_mode = !sigma_mode;
//         printf(sigma_mode ? "🗿 SIGMA MODE ACTIVATED 🗿\n" : "back to regular chad energy\n");
//         last_exit_code = 0;
//         return 0;
//     }
//     
//     // Parse arguments (basic tokenization)
//     char* args[MAX_ARGS];
//     int argc = 0;
//     char* token = strtok(input, " \t");
//     
//     while (token && argc < MAX_ARGS - 1) {
//         // Check if it's a meme command
//         char* real_cmd;
//         if (is_meme_command(token, &real_cmd)) {
//             args[argc++] = real_cmd;
//         } else {
//             args[argc++] = token;
//         }
//         token = strtok(NULL, " \t");
//     }
//     args[argc] = NULL;
//     
//     if (argc == 0) return 0;
//     
//     // Execute the command (where the magic happens)
//     pid_t pid = fork();
//     if (pid == 0) {
//         // Child process (the chosen one)
//         execvp(args[0], args);
//         print_error(ERR_NOT_FOUND);
//         exit(127);
//     } else if (pid > 0) {
//         // Parent process (the patient one)
//         int status;
//         waitpid(pid, &status, 0);
//         last_exit_code = WEXITSTATUS(status);
//         
//         // Celebrate success (optional flex)
//         if (last_exit_code == 0 && rand() % 4 == 0) {
//             print_success();
//         }
//     } else {
//         print_error(ERR_FORK);
//         last_exit_code = 1;
//     }
//     return 0;
// }
//
int is_meme_command(char* cmd, char** real_cmd) {
    for (int i = 0; meme_commands[i].genz_cmd != NULL; i++) {
        if (strcmp(cmd, meme_commands[i].genz_cmd) == 0) {
            *real_cmd = meme_commands[i].real_cmd;
            return 1;
        }
    }
    return 0;
}

void handle_builtin_rizz() {
    printf("🔥 ChadSh Help Menu (Getting that assistance) 🔥\n\n");
    printf("Gen-Z Commands (the good stuff):\n");
    
    for (int i = 0; meme_commands[i].genz_cmd != NULL; i++) {
        printf("  %-12s -> %-8s (%s)\n", 
               meme_commands[i].genz_cmd,
               meme_commands[i].real_cmd,
               meme_commands[i].desc);
    }
    
    printf("\nSpecial Commands:\n");
    printf("  sigma        -> toggle sigma mode (extra energy)\n");
    printf("  periodt      -> exit with drama\n");
    printf("  rizz         -> show this help (you're here rn)\n");
    
    printf("\nPro Tips:\n");
    printf("- Use regular commands too (we're not gatekeeping)\n");
    printf("- Sigma mode = extra motivational prompts\n");
    printf("- Commands that work = W energy, fails = NPC status\n");
    printf("\nStay based, king! 👑\n");
}
