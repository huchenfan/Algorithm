#include<bits/stdc++.h>

using namespace std;

int n, k;
const int N = 10;
char grid[N][N];
int visited[N];
int res;

void dfs(int cur, int cnt) {
    if(cnt == k) {
        res++;
        return;
    }
    if(cur >= n) {
        return;
    }

    for(int i = 0; i < n; i++) {
        if (visited[i] == -1 && grid[cur][i] == '#') {
            // 放
            visited[i] = i;
            dfs(cur + 1, cnt + 1);
            visited[i] = -1;
        }
    }
    // 不放
    dfs(cur+1, cnt);
}

int main() {
    memset(visited, -1, sizeof(visited));
    cin >> n >> k;
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    dfs(0, 0);
    cout << res << endl;
    return 0;
}

// 不分的情况单独分支即可