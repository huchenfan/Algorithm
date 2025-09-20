#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n+1, vector<int>(m+1));
    vector<vector<bool>> visited(n+1, vector<bool>(m+1, false));
    int s, t, val;
    int sum = n * m;
    while(sum--){
        cin >> s >> t >> val;
        grid[s][t] = val;
    }
    vector<pair<int, int>> direction{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    queue<pair<int, int>> que;
    que.push({1, 1});
    visited[1][1] = true;
    int step = -1;
    while(!que.empty()) {
        int sz = que.size();
        step++;
        for(int i = 0; i < sz; i++) {
            pair<int, int> cur = que.front(); que.pop();
            int next_x, next_y;
            for(int j = 0; j< 4; j++){
                next_x = cur.first + direction[j].first;
                next_y = cur.second + direction[j].second;
                if(1 <= next_x && next_x <= n && 1 <= next_y && next_y <= m && grid[next_x][next_y] == 0 && !visited[next_x][next_y]) {
                        visited[next_x][next_y] = true;
                        que.push({next_x, next_y});
                        if(next_x == n && next_y == m) {
                            step++;
                            cout << step << endl;
                            return 0;
                        }
                }
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
