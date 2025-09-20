#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int> (m + 1, 0));

    for (int i = 0; i < n * m; ++i) {
        int s, t, val;
        cin >> s >> t >> val;
        grid[s][t] = val;
    }

    vector<vector<bool>> visited(n + 1, vector<bool> (m + 1, false));
    vector<pair<int, int>> direction{{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    queue<pair<int, int>> que;
    pair<int, int> start = {1, 1};
    cout << grid[start.first][start.second];
    que.push(start);
    visited[start.first][start.second] = true;
    while(!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();
        for(int i = 0; i < 4; i++){
          int  next_x = cur.first + direction[i].first;
          int  next_y = cur.second + direction[i].second;
            if (1 <= next_x && next_x <= n && 1 <= next_y && next_y <= m && !visited[next_x][next_y]){
              que.push({next_x, next_y});
              visited[next_x][next_y] = true;
              cout <<  "->"<< grid[next_x][next_y];
          }
        }
    }
    cout << '\n';   // 3. 换行防 PE
    return 0;
}

