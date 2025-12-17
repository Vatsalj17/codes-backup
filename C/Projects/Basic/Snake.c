#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

struct termios oldt;

void enableRawMode()
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, 0);
}

int kbhit()
{
    int ch = getchar();
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

typedef enum {STOP = 0, LEFT, RIGHT, UP, DOWN} Direction;

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
Direction dir;
int width = 40;
int height = 25;
int speed = 800;
int highScore = 0;

void printHelp(char *progname) {
    printf("Usage: %s [OPTIONS]\n", progname);
    printf("Terminal Snake Game\n\n");
    printf("Options:\n");
    printf("  -w, --width WIDTH     Set game width (default: 20, range: 10-100)\n");
    printf("  -h, --height HEIGHT   Set game height (default: 20, range: 10-50)\n");
    printf("  -s, --speed SPEED     Set game speed in ms (default: 800)\n");
    printf("  --help                Show this help message\n");
    printf("  -v, --version         Show version information\n\n");
    printf("Controls:\n");
    printf("  w/k - Move up\n");
    printf("  s/j - Move down\n");
    printf("  a/h - Move left\n");
    printf("  d/l - Move right\n");
    printf("  x   - Quit game\n");
}

void printVersion() {
    printf("Snake Game v1.0\n");
}

void updateHighScore() {
    if (score > highScore) {
        highScore = score;
    }
}

void showGameOver() {
    clear();
    printf("\n");
    for (int i = 0; i < width + 2; i++) printf("=");
    printf("\n");
    printf("           GAME OVER!\n");
    for (int i = 0; i < width + 2; i++) printf("=");
    printf("\n\n");
    printf("    Final Score: %d\n", score);
    printf("    High Score:  %d\n", highScore);
    if (score == highScore && score > 0) {
        printf("    NEW HIGH SCORE!\n");
    }
    printf("\n");
    printf("    Press 'r' to restart\n");
    printf("    Press 'q' to quit\n");
    printf("\n");
    for (int i = 0; i < width + 2; i++) printf("=");
    printf("\n");
}

int handleGameOverInput() {
    char ch;
    while (1) {
        if (kbhit()) {
            ch = getchar();
            if (ch == 'r' || ch == 'R') {
                return 1;
            } else if (ch == 'q' || ch == 'Q') {
                return 0;
            }
        }
        usleep(50000);
    }
}

void parseArgs(int argc, char *argv[]) {
    int c;
    static struct option long_options[] = {
        {"width", required_argument, 0, 'w'},
        {"height", required_argument, 0, 'h'},
        {"speed", required_argument, 0, 's'},
        {"help", no_argument, 0, 1000},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, "w:h:s:v", long_options, NULL)) != -1) {
        switch (c) {
            case 'w':
                width = atoi(optarg);
                if (width < 10 || width > 100) {
                    fprintf(stderr, "Width must be between 10 and 100\n");
                    exit(1);
                }
                break;
            case 'h':
                height = atoi(optarg);
                if (height < 10 || height > 50) {
                    fprintf(stderr, "Height must be between 10 and 50\n");
                    exit(1);
                }
                break;
            case 's':
                speed = atoi(optarg);
                if (speed < 100 || speed > 1000) {
                    fprintf(stderr, "Speed must be between 100 and 1000 ms\n");
                    exit(1);
                }
                break;
            case 'v':
                printVersion();
                exit(0);
                break;
            case 1000:
                printHelp(argv[0]);
                exit(0);
                break;
            case '?':
                exit(1);
                break;
        }
    }
}

void Setup()
{
    gameOver = 0;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw()
{
    clear();
    for (int i = 0; i < width + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) printf("#");

            if (i == y && j == x) printf("O");
            else if (i == fruitY && j == fruitX) printf("");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                        break;
                    }
                }
                if (!print) printf(" ");
            }
            if (j == width - 1) printf("#");
        }
        printf("\n");
    }
    for (int i = 0; i < width + 2; i++) printf("#");
    printf("\nScore: %d | High Score: %d\n", score, highScore);
}

void Input()
{
    if (kbhit()) {
        char ch = getchar();

        if (ch == 'a' || ch == 'h') dir = LEFT;
        else if (ch == 'd' || ch == 'l') dir = RIGHT;
        else if (ch == 'w' || ch == 'k') dir = UP;
        else if (ch == 's' || ch == 'j') dir = DOWN;
        else if (ch == 'x') gameOver = 1;
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (dir == LEFT) x--;
    if (dir == RIGHT) x++;
    if (dir == UP) y--;
    if (dir == DOWN) y++;

    if (x >= width || x < 0 || y >= height || y < 0) gameOver = 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = 1;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void sleep_ms(int milliseconds)
{
    usleep(milliseconds * 1000);
}

int main(int argc, char *argv[])
{
    parseArgs(argc, argv);
    srand(time(0)); 
    enableRawMode();

    do {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            sleep_ms(1020 - speed);
        }
        disableRawMode();
        updateHighScore();
        showGameOver();
        enableRawMode();
    } while (handleGameOverInput());

    disableRawMode();
    return 0;
}
