#include<bits/stdc++.h>

using namespace std;

const int N = 505;
vector<vector<pair<int, int>>> grid(N);
bool visited[N];
int minDist[N];
int n, m;

void prim() {
    fill(minDist, minDist+N, 0x3f3f3f3f);
    memset(visited, false, sizeof(visited));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    minDist[1] = 0;
    pq.push({0, 1});
    while(!pq.empty()) {
        int cur = pq.top().second;  // 找到 【非生成树节点】 中 距离 【树】 最近的节点
        pq.pop();
        visited[cur] = true;  // 将该节点加入树
        for(pair<int, int> edge : grid[cur]) {
            if(!visited[edge.first] && edge.second < minDist[edge.first]) {
                minDist[edge.first] = edge.second;  // 更新非生成树节点到树的距离
                pq.push({edge.second, edge.first});  // 压入堆中
            }
        }
    }
}

int main() {
    cin >> n >> m;
    int s, t, val;
    while(m--) {
        cin >> s >> t >> val;
        grid[s].emplace_back(t, val);
        grid[t].emplace_back(s, val);
    }
    prim();
    int sum = 0;
    for(int i = 1; i <=n; i++) {
        if(minDist[i] == 0x3f) {
            cout << "FALSE" << endl;
            return 0;
        }
        sum += minDist[i];
    }
    cout << sum << endl;
    return 0;
}
