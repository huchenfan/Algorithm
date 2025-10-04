#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, w; };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    const int INF = 1e9;
    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < k; ++i) {
        int s, t, v;
        cin >> s >> t >> v;
        g[s].push_back({t, v});
    }

    vector<int> dist(n + 1, INF);
    vector<bool> vis(n + 1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[1] = 0;
    pq.emplace(0, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;     // ② 显式：已被钉死，跳过
        vis[u] = true;            // ② 显式：现在钉死
        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);   // 让更短的进行下一步的优化
            }
        }
    }

    for (int i = 1; i <= n; ++i) cout << (dist[i] == INF ? -1 : dist[i]) << " \n"[i == n];
    return 0;
}