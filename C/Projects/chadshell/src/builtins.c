#include "memes.h"

// Builtin command function pointers
typedef int (*builtin_func)(char** args);

typedef struct {
    char* name;
    builtin_func func;
    char* desc;
} Builtin;

// Builtin function declarations
int builtin_vibe(char** args);    // cd
int builtin_based(char** args);   // pwd  
int builtin_periodt(char** args); // exit
int builtin_flex(char** args);    // ls
int builtin_yeet(char** args);    // rm
int builtin_nocap(char** args);   // echo
int builtin_rizz(char** args);    // help
int builtin_sigma(char** args);   // sigma mode
int builtin_cringe(char** args);  // history (basic)

// Builtin commands table (the VIP list)
static Builtin builtins[] = {
    {"vibe", builtin_vibe, "change directory vibes"},
    {"based", builtin_based, "show current location"},
    {"periodt", builtin_periodt, "exit with drama"},
    {"flex", builtin_flex, "show off files"},
    {"yeet", builtin_yeet, "delete files (no mercy)"},
    {"nocap", builtin_nocap, "speak pure facts"},
    {"rizz", builtin_rizz, "get assistance"},
    {"sigma", builtin_sigma, "toggle sigma energy"},
    {"cringe", builtin_cringe, "your command history"},
    {"cd", builtin_vibe, "change directory (normie version)"},
    {"pwd", builtin_based, "print working directory"},
    {"exit", builtin_periodt, "quit shell"},
    {"echo", builtin_nocap, "print text"},
    {"help", builtin_rizz, "show help"},
    {NULL, NULL, NULL}
};

static int sigma_mode = 0;
static char* history[100];  // Simple history
static int hist_count = 0;

int execute_builtin(char** args) {
    if (!args || !args[0]) return 0;
    
    // Find and execute builtin
    for (int i = 0; builtins[i].name; i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            return builtins[i].func(args);
        }
    }
    return 0;  // Not a builtin
}

int builtin_vibe(char** args) {
    char* path = args[1] ? args[1] : getenv("HOME");
    
    if (!path) {
        print_error("no home directory? that's sus 🏠");
        return 1;
    }
    
    if (chdir(path) != 0) {
        print_error("can't vibe to that location chief");
        return 1;
    }
    
    if (sigma_mode) printf("location energy changed 🌟\n");
    return 1;  // Handled
}

int builtin_based(char** args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) {
        printf("%s\n", cwd);
        if (sigma_mode) printf("you're here and that's based 📍\n");
    } else {
        print_error("lost in the sauce (pwd failed)");
    }
    return 1;
}

int builtin_periodt(char** args) {
    printf(sigma_mode ? "sigma grind complete 💪\n" : "chadsh logging off 😤\n");
    exit(0);
}

int builtin_flex(char** args) {
    // Execute ls with style
    printf("💅 flexing your files 💅\n");
    system(args[1] ? "ls -la" : "ls --color=auto");
    if (sigma_mode) printf("those files are looking clean ngl\n");
    return 1;
}

int builtin_yeet(char** args) {
    if (!args[1]) {
        print_error("yeet what exactly? specify target");
        return 1;
    }
    
    // Confirm deletion (safety first, even for chads)
    printf("about to yeet '%s' - you sure? (y/N): ", args[1]);
    char confirm;
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "rm %s", args[1]);
        if (system(cmd) == 0) {
            printf("yeeted successfully 🗑️\n");
        } else {
            print_error("yeet failed (file said nah)");
        }
    } else {
        printf("yeet cancelled (probably smart tbh)\n");
    }
    return 1;
}

int builtin_nocap(char** args) {
    // Print all arguments (facts only)
    for (int i = 1; args[i]; i++) {
        printf("%s", args[i]);
        if (args[i+1]) printf(" ");
    }
    printf("\n");
    
    if (sigma_mode && rand() % 3 == 0) {
        printf("📠 facts were spoken\n");
    }
    return 1;
}

int builtin_rizz(char** args) {
    printf("🔥 ChadSh Commands (the good stuff) 🔥\n\n");
    
    for (int i = 0; builtins[i].name; i++) {
        if (builtins[i].desc) {  // Skip duplicates without desc
            printf("  %-12s - %s\n", builtins[i].name, builtins[i].desc);
        }
    }
    
    printf("\nPro Tips:\n");
    printf("- Use 'sigma' to toggle motivational mode\n");
    printf("- Pipes work: flex | nocap 'files:'\n"); 
    printf("- Background jobs: flex &\n");
    printf("- Redirects: nocap hello > file.txt\n");
    printf("\nStay based! 👑\n");
    return 1;
}

int builtin_sigma(char** args) {
    sigma_mode = !sigma_mode;
    printf(sigma_mode ? 
           "🗿 SIGMA MODE ACTIVATED - extra motivation enabled 🗿\n" :
           "back to regular chad energy (still fire tho)\n");
    return 1;
}

int builtin_cringe(char** args) {
    printf("📜 Your Command History (the receipts):\n");
    
    if (hist_count == 0) {
        printf("no history yet (clean slate energy)\n");
        return 1;
    }
    
    for (int i = 0; i < hist_count; i++) {
        printf("%3d  %s\n", i+1, history[i]);
    }
    
    if (sigma_mode) printf("learning from the past = sigma mindset\n");
    return 1;
}

// Add command to history
void add_to_history(char* cmd) {
    if (hist_count < 100) {
        history[hist_count] = strdup(cmd);
        hist_count++;
    }
}
