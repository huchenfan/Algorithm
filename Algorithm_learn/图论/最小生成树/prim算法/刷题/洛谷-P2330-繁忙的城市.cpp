#include<bits/stdc++.h>

using namespace std;

const int N = 305;
bool visited[N];
int minDist[N];
vector<vector<pair<int, int>>> grid(N);

int n, m;

int main() {
    fill(minDist, minDist+N, 0x3f3f3f3f);
    memset(visited, false, sizeof(visited));
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    int s, t, val;
    while(m--) {
        cin >> s >> t >> val;
        grid[s].emplace_back(t, val);
        grid[t].emplace_back(s, val);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    minDist[1] = 0;
    pq.emplace(0, 1);
    while(!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        visited[cur.second] = true;
        for(pair<int, int> edge : grid[cur.second]) {
            if(!visited[edge.first] && minDist[edge.first] > edge.second) {
                minDist[edge.first] = edge.second;
                pq.emplace(edge.second, edge.first);
            }
        }
    }
    int cnt = -1, max = 0;
    for(int i = 1; i <= n; i++) {
        if(minDist[i] < 0x3f3f3f3f) cnt++;
        if(max < minDist[i]) max = minDist[i];
    }
    cout << cnt << " " << max << endl;
    return 0;
}