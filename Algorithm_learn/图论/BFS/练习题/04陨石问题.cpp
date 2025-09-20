#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> QUE;

int main() {
    int n, m, total;
    cin >> n >> m >> total;
    int grid[n + 1][m + 1];
    bool visited[n + 1][m + 1];
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            visited[i][j] = false;
        }
    }
    int INF = 1e9;
    int dix[] = {0, -1, 0, 1};
    int diy[] = {1, 0, -1, 0};
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            grid[i][j] = INF;
        }
    }
    while (total--) {
        int s, t, val;
        cin >> s >> t >> val;
        grid[s][t] = val;
        int next_x, next_y;
        for (int i = 0; i < 4; i++) {
            next_x = s + dix[i];
            next_y = t + diy[i];
            if (grid[next_x][next_y] >= val) grid[next_x][next_y] = val;
        }
    }

    QUE pq[(n + 1) * (m + 1)];
    int hh = 0;
    int tt = -1;
    pair<int, int> start = {1, 1};
    visited[1][1] = true;
    pq[++tt] = start;
    int step = -1;
    visited[1][1] = true;
    while (tt - hh >= 0) {
        int size = tt - hh + 1;
        step++;
        for (int j = 0; j < size; j++) {
            pair<int, int> cur = pq[hh];
            if (cur.first > 0 && cur.first <= n && cur.second > 0 && cur.second <= m &&
                grid[cur.first][cur.second] == INF) {
                cout << step << endl;
                return 0;
            }
            hh++;
            int next_x, next_y;
            for (int i = 0; i < 4; i++) {
                next_x = cur.first + dix[i];
                next_y = cur.second + diy[i];
                if (next_x <= 0 || next_x >= n + 1 || next_y <= 0 || next_y >= m + 1) continue;
                if (visited[next_x][next_y]) continue;
                if (grid[next_x][next_y] > step) {
                    visited[next_x][next_y] = true;
                    pq[++tt] = {next_x, next_y};
                }
            };
        }
    }
    cout << -1 << endl;
    return 0;
}

