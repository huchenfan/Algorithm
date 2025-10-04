#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
int father[N];
int rk[N];          // 秩（树高）

void init() {
    for (int i = 0; i < N; ++i) {
        father[i] = i;
        rk[i] = 0;      // 初始高度为 0
    }
}

int find(int cur) {
    if(cur == father[cur]) return cur;
    return father[cur] = find(father[cur]);
}

void join(int a, int b) {
    // 按秩合并
    a = find(a);
    b = find(b);
    if(rk[a] <= rk[b])  father[a] = b;
    else father[b] = a;
    if(rk[a] == rk[b] && a != b) rk[b]++;
}

bool same(int a, int b) {
    return find(a) == find(b);
}

int n, m;

struct Edge {
    int u, v, val;
};

int main() {
    cin >> n >> m;
    int s, t, val;
    Edge edges[m];
    for(int i = 0; i < m; i++){
        cin >> s >> t >> val;
        edges[i] = {s, t, val};
    }
    // 按边权从小到大排序
    sort(edges, edges + m, [](const Edge& a, const Edge& b) {
        return a.val < b.val;
    });

    init(); // 初始化并查集

    int sum = 0;
    int cnt = 0;
    // 遍历边
    for(Edge edge : edges) {
        if(cnt == n - 1) break;
        if(!same(edge.u, edge.v)) {
            join(edge.u, edge.v);
            cnt++;
            sum += edge.val;
        }

    }

    if(cnt != n - 1) {
        cout << "Graph is not connected!" << endl;
        return 0;
    }

    cout << sum << endl;
    return 0;
}
