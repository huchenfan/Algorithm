#include<bits/stdc++.h>

using namespace std;

const int N = 505;
int grid[N][N];
int minDist[N];
bool visited[N];

int n, m;

int main() {
    memset(grid, 0x3f, sizeof(grid));
    memset(minDist, 0x3f, sizeof(minDist));
    memset(visited, false, sizeof(visited));

    cin >> n >> m;
    int s, t, val;
    while(m--) {
        cin >> s >> t >> val;
        grid[s][t] = grid[t][s] = val;  // 无向图
    }

    minDist[1] = 0;
    for(int round = 1; round <= n; round++) {
        int cur = -1;
        int min_ = 0x3f;
        for(int i = 1; i <= n; i++) {
            if(!visited[i] && minDist[i] < min_) {
                min_ = minDist[i];
                cur = i;
            }
        }

        if(cur == -1) break; // 图不连通

        visited[cur] = true;
        for(int i = 1; i <= n; i++) {
            if(!visited[i] && grid[cur][i] < minDist[i]){
                minDist[i] = grid[cur][i];
            }
        }
    }

    int sum = 0;
    for(int i = 1; i<= n; i++) {
        if(minDist[i] == 0x3f) {
            cout << "Graph is not connected!" << endl;  // 图不连通
            return 0;
        }
        sum += minDist[i];
    }
    cout << sum << endl;
    return 0;
}