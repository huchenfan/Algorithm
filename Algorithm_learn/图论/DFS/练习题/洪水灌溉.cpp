#include <bits/stdc++.h>

using namespace std;

int dix[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int diy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
int n,m;
const int N = 100;
char grid[N][N];
int visited[N][N] = {0};
int res;
void dfs(int x, int y) {
    for(int i = 0; i < 8; i++) {
        int a = x + dix[i];
        int b = y + diy[i];
        if(a < 0 || a >= n || b < 0 || b >= m) continue;
        if(visited[a][b]) continue;
        if(grid[a][b] != '.') {
            visited[a][b] = 1;
            dfs(a, b);
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    };
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 'W' && !visited[i][j]) {
                dfs(i, j);
                res++;
            }
        }
    };
    cout << res << endl;
    return 0;
}

// 这题的难点在于， 意识到 不是在一个dfs的函数里解决所有问题， 而是dfs仅仅起到一个标记W的作用

