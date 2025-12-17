#include <iostream>
#include <vector>
using namespace std;

enum dir {up, right, down, left};

void solve(vector<vector<int>>& maze, vector<string> path, int posX, int posY) {
    ;
}

vector<string> ratInMaze(vector<vector<int>>& maze) {
    vector<string> path;
    int n = maze.size();
    if (maze[n-1][n-1] == 0) return {};
    int posX = 0, posY = 0;
    solve(maze, path, posX, posY);
    return path;
}

int main(void) {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    vector<vector<int>> maze(n, vector<int>(n));
    cout << "Enter the maze pattern:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> maze[i][j];
        }
    }
    vector<string> ans = ratInMaze(maze);
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
}
