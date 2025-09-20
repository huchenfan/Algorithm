#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> QUE;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int start_x, start_y;
    cin >> start_x >> start_y;
    vector<vector<int>> grid(n+1, vector<int>(m+1, -1));
    vector<vector<bool>> visited(n+1, vector<bool>(m+1, false));

    vector<pair<int, int>> direction{{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    QUE p[n * m];
    int hh = 0;
    int tt = -1;
    p[++tt] = {start_x, start_y};
    visited[start_x][start_y] = true;
    grid[start_x][start_y] = 0;
    int step = 0;
    while(tt - hh >= 0) {
        int sz = tt - hh + 1;
        step++;
        for(int i = 0; i < sz; i++) {
            pair<int, int> cur = p[hh]; hh++;
            int next_x, next_y;
            for(int j = 0; j < 8; j++){
                next_x = cur.first + direction[j].first;
                next_y = cur.second + direction[j].second;
                if(1 <= next_x && next_x <= n && 1 <= next_y && next_y <= m && !visited[next_x][next_y]) {
                    visited[next_x][next_y] = true;
                    p[++tt] = {next_x, next_y};
                    grid[next_x][next_y] = step;
                }
            }
        }
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            cout << grid[i][j] << " \n"[j==m];
        }
    }
    return 0;
}
