#include <bits/stdc++.h>
using namespace std;

int W, H, res = 1;
char g[20][20];
bool vis[20][20];
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void dfs(int x, int y) {
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
        if (g[nx][ny] != '.' || vis[nx][ny]) continue;
        vis[nx][ny] = true;
        ++res;
        dfs(nx, ny);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> W >> H;
    int sx = 0, sy = 0;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j) {
            cin >> g[i][j];
            if (g[i][j] == '@') sx = i, sy = j;
        }
    vis[sx][sy] = true;
    dfs(sx, sy);
    cout << res << '\n';
    return 0;
}