#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> QUE;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n+2, vector<int>(m+2, 0));
    vector<vector<bool>> visited(n+2, vector<bool>(m+2, false));
    int total = n*m;
    int s, t, val;
    while(total--){
        cin >> s >> t >> val;
        grid[s][t] = val;
    }
    vector<pair<int, int>> direction{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    QUE pq[(n+2)*(m+2)];
    int hh = 0;
    int tt = -1;
    pq[++tt] = {0, 0};
    visited[0][0] = true;
    pair<int, int> start;
    while(tt-hh >=0) {
        pair<int, int> cur = pq[hh]; hh++;
        int next_x, next_y;
        for(int i = 0; i < 4; i++) {
            next_x = cur.first + direction[i].first;
            next_y = cur.second + direction[i].second;
            if(next_x < 0 || next_x >= n + 2 || next_y < 0 || next_y >= m + 2) continue;
            if(visited[next_x][next_y]) continue;
            if(grid[next_x][next_y] == 0) {
                visited[next_x][next_y] = true;
                pq[++tt] = {next_x, next_y};
            }
            if(grid[next_x][next_y] == 1) {
                start = {next_x, next_y};
            }
        }
    }
    pq[++tt] = start;
    while(tt-hh >=0) {
        pair<int, int> cur = pq[hh]; hh++;
        int next_x, next_y;
        for(int i = 0; i < 4; i++) {
            next_x = cur.first + direction[i].first;
            next_y = cur.second + direction[i].second;
            if(next_x < 0 || next_x >= n + 2 || next_y < 0 || next_y >= m + 2) continue;
            if(visited[next_x][next_y]) continue;
            if(grid[next_x][next_y] == 0) {
                visited[next_x][next_y] = true;
                grid[next_x][next_y] = 2;
                pq[++tt] = {next_x, next_y};
            }
            if(grid[next_x][next_y] == 1) {
                visited[next_x][next_y] = true;
                pq[++tt] = {next_x, next_y};
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

