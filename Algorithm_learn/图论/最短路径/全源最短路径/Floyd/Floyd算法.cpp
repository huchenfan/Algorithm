#include<bits/stdc++.h>

using namespace std;

const int N = 55;
int grid[N][N];
int path[N][N] = {0};

int n, m;

void floyd() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                int p = grid[i][j];
                grid[i][j] = min(grid[i][k] + grid[k][j], grid[i][j]);
                if(p != grid[i][j]) path[i][j] = k;  // 路径记录
            }
        }
    }
}

void printPath(int s, int e){
    if(path[s][e] == 0) return;
    printPath(s, path[s][e]);
    cout << path[s][e] << "--> ";
    printPath(path[s][e], e);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(&grid[0][0], &grid[0][0] + N*N, 1e9);
    for(int i = 1; i <= n; i++) {
        grid[i][i] = 0;
    }
    cin >> n >> m;
    while(m--) {
        int s, t, val;
        cin >> s >> t >> val;
        grid[s][t] = grid[t][s] = val;   // 无向图
    }
    floyd();
    // 判断是否存在 【负环】
    for(int i = 1; i <= n; i++) {
        if(grid[i][i] < 0) {
            cout << -1 << endl;
            return 0;
        }
    }

    int start_, end_;
    cin >> start_ >> end_;

    cout << start_ << "--> " << end_ << "最短距离::: " << grid[start_][end_] << endl;
    cout << "路径::: " << start_ << "--> ";
    printPath(start_, end_);
    cout << end_ << endl;
    return 0;
}

