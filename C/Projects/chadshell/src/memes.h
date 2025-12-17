#ifndef MEMES_H
#define MEMES_H

// Enable POSIX & GNU functions *before* any #include
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

// Shell info
#define SHELL_NAME "chadsh"
#define VERSION "1.0-sigma"
#define MAX_INPUT 1024
#define MAX_ARGS 64

// Prompts (absolute fire)
#define PROMPT_CHAD "[skibidi@ohio]$ "
#define PROMPT_SIGMA "[sigma@grindset]$ "
#define PROMPT_NPC "[NPC@L]$ "
#define PROMPT_W "[chad@W]$ "

// Welcome banner
#define BANNER \
"   _____ _               _  _____ _     \n" \
"  / ____| |             | |/ ____| |    \n" \
" | |    | |__   __ _  __| | (___ | |__  \n" \
" | |    | '_ \\ / _` |/ _` |\\___ \\| '_ \\ \n" \
" | |____| | | | (_| | (_| |____) | | | |\n" \
"  \\_____|_| |_|\\__,_|\\__,_|_____/|_| |_|\n" \
"\n💀 The most sigma shell fr fr 💀\n" \
"Type 'rizz' for help, 'periodt' to exit\n\n"

// Error messages (pure brainrot)
#define ERR_NOT_FOUND "bruh that command is sus 💀"
#define ERR_PERMISSION "nah fam, you ain't got the rizz for that"
#define ERR_NO_FILE "no cap, that file ghosted you 👻"
#define ERR_SYNTAX "that's not very sigma of you chief"
#define ERR_FORK "fork() said 'nah i'd win' and failed"

// Success vibes
#define SUCCESS_MSGS 3
static const char* success_vibes[] = {
    "W command fr 🔥",
    "that was bussin ngl",
    "sigma move right there"
};

// Gen-Z command mappings
typedef struct {
    char* genz_cmd;
    char* real_cmd;
    char* desc;
} MemeCmd;

// Forward declarations
int parse_and_execute(char* input);
int execute_builtin(char** args);
int execute_command(char** args);
void add_to_history(char* cmd);
int get_last_exit_code(void);
void check_background_jobs(void);

static MemeCmd meme_commands[] = {
    {"yeet", "rm", "delete files (no mercy)"},
    {"flex", "ls -la", "show off your files"},
    {"nocap", "echo", "speak facts only"},
    {"vibe", "cd", "change your location energy"},
    {"sus", "ps", "check what's running (sus behavior)"},
    {"rizz", "help", "get some assistance"},
    {"periodt", "exit", "leave with drama"},
    {"ghostmode", "jobs", "see background processes"},
    {"based", "pwd", "where you at rn"},
    {"cringe", "history", "your L command history"},
    {NULL, NULL, NULL}
};

// Utility functions
static inline void print_success() {
    printf("%s\n", success_vibes[rand() % SUCCESS_MSGS]);
}

static inline void print_error(const char* msg) {
    printf("❌ %s\n", msg);
}

static inline void print_banner() {
    printf("%s", BANNER);
}

#endif
