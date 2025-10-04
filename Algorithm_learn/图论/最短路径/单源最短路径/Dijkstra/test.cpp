#include <bits/stdc++.h>

using namespace std;

//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    int n, m;
//    int INF = 1e9;
//    cin >> n >> m;
//    vector<vector<int>> grid(n+1, vector<int> (n+1, INF));
//    while(m--) {
//        int s, t, val;
//        cin >> s >> t >> val;
//        grid[s][t] = val;
//    }
//    vector<bool> visited(n+1, false);
//    vector<int> minDistance(n+1, INF);
//    int start = 1;
//    minDistance[start] = 0;
//    int sum = 0;
//    for(int i = 1; i < n+1; i++){
//        int min = INF;
//        int cur = -1;
//        for (int t = 1; t < n + 1; t++) {
//            if (!visited[t] && minDistance[t] < min) {
//                min = minDistance[t];
//                cur = t;
//            }
//        }
//        if (cur == -1) break; // 所有可达节点已访问, 退出循环
//
//        visited[cur] = true;
//        for (int j = 1; j < n + 1; j++) {
//            if (!visited[j] && minDistance[j] > min + grid[cur][j]) {
//                minDistance[j] = min + grid[cur][j];
//            }
//        }
//    }
//    for(int i = 1; i < n+1; i++){
//        cout << minDistance[i] << " ";
//    }
//    cout << endl;
//    return 0;
//}


struct Edge {
    int node;
    int val;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> grid(n+1);
    while(m--) {
        int s, t, val;
        cin >> s >> t >> val;
        grid[s].emplace_back(Edge{t, val});
    }
    int INF = 1e9;
    vector<int> minDistance(n+1, INF);
    vector<bool> visited(n+1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pair<int, int> start = {1, 0};
    minDistance[start.first] = 0;
    while(!pq.empty()) {
        pair<int, int> cur = pq.top(); pq.pop();
        if(visited[cur.first]) continue;
        visited[cur.first] = true;
        for(Edge edge: grid[cur.first]) {
            if(minDistance[edge.node] > minDistance[cur.first] + edge.val) {
                minDistance[edge.node] = minDistance[cur.first] + edge.val;
                pq.push({edge.node, minDistance[edge.node]});
            }
        }
    }
}






