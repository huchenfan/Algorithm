//#include <bits/stdc++.h>
//
//using namespace std;
//
//int dix[] = {0, 1, 0, -1};
//int diy[] = {1, 0, -1, 0};
//
//int main() {
//    int n, m;
//    cin >> n >> m;
//    char grid[n][m];
//    int sx, sy, ex, ey;
//    cin >> sx >> sy >> ex >> ey;
//    char val;
//    bool visited[n][m];
//    for(int i = 0; i < n; i++) {
//        for(int j = 0; j < m ;j++) {
//            cin >> val;
//            grid[i][j] = val;
//            visited[i][j] = false;
//        }
//    }
//    deque<pair<int, int>> pq;
//    pq.emplace_front(sx, sy);
//    visited[sx][sy] = true;
//    int step = 0;
//    pair<int, int> later = {sx, sy};
//    while(!pq.empty()) {
//        pair<int, int> cur = pq.front(); pq.pop_front();
//        if(grid[cur.first][cur.second] != grid[later.first][later.second]) {
//            step++;
//        }
//        if(cur.first == ex && cur.second == ey) {
//            cout << step << endl;
//            return 0;
//        }
//        int next_x, next_y;
//        for(int i = 0; i < 4; i++) {
//            next_x = cur.first + dix[i];
//            next_y = cur.second + diy[i];
//            if(next_x < 0 || next_x >=n ||next_y < 0 || next_y >= m) continue;
//            if(visited[next_x][next_y]) continue;
//            if(grid[cur.first][cur.second] == grid[next_x][next_y]) {
//                visited[next_x][next_y] = true;
//                pq.emplace_front(next_x, next_y);
//            }
//            if(grid[cur.first][cur.second] != grid[next_x][next_y]) {
//                visited[next_x][next_y] = true;
//                pq.emplace_back(next_x, next_y);
//            }
//
//        }
//        later = cur;
//    }
//    return 0;
//}

#include <bits/stdc++.h>

using namespace std;

int dix[] = {0, 1, 0, -1};
int diy[] = {1, 0, -1, 0};

int main() {
    int n, m;
    cin >> n >> m;
    char grid[n][m];
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    char val;
    int dist[n][m];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m ;j++) {
            cin >> val;
            grid[i][j] = val;
            dist[i][j] = -1;
        }
    }
    deque<pair<int, int>> pq;
    pq.emplace_front(sx, sy);
    dist[sx][sy] = 0;
    while(!pq.empty()) {
        pair<int, int> cur = pq.front(); pq.pop_front();
        if(cur.first == ex && cur.second == ey) {
            cout << dist[ex][ey] << endl;
            return 0;
        }
        int next_x, next_y;
        for(int i = 0; i < 4; i++) {
            next_x = cur.first + dix[i];
            next_y = cur.second + diy[i];
            if(next_x < 0 || next_x >=n ||next_y < 0 || next_y >= m) continue;
            if(dist[next_x][next_y] > 0) continue;
            if(grid[cur.first][cur.second] == grid[next_x][next_y]) {
                dist[next_x][next_y] = dist[cur.first][cur.second];
                pq.emplace_front(next_x, next_y);
            }
            if(grid[cur.first][cur.second] != grid[next_x][next_y]) {
                dist[next_x][next_y] = dist[cur.first][cur.second] + 1;
                pq.emplace_back(next_x, next_y);
            }

        }
    }
    return 0;
}