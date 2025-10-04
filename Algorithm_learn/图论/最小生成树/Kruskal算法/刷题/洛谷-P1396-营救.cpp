#include<bits/stdc++.h>

using namespace std;

const int N = 10005;

int father[N];
int rk[N];

void init() {
    for(int i = 0; i < N; i++) {
        father[i] = i;
        rk[i] = 0;
    }
}

int find(int cur) {
    if(cur == father[cur]) return cur;
    return father[cur] = find(father[cur]);
}

void join(int a, int b) {
    a = find(a);
    b = find(b);
    if(rk[a] <= rk[b]) father[a] = b;
    else father[b] = a;

    if(rk[a] == rk[b] && a != b) rk[b]++;
}

bool same(int a, int b) {
    return find(a) == find(b);
}

struct Edge{
    int s, t, val;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    int u, v, val;
    Edge edges[m];
    Edge edge_start[n-1];
    int count = 0;
    for(int i = 0; i <m;i++) {
        cin >> u >> v >> val;

        edges[i] = {u, v, val};
    }

    sort(edges, edges+m, [](const Edge &a, const Edge &b) {
        return a.val < b.val;
    });

    init();

    int max_ = 0;

    for(Edge edge : edges) {
        if(!same(edge.s, edge.t)) {
            join(edge.s, edge.t);
            if(max_ < edge.val) max_ = edge.val;
            if(same(s, t)) break;
        }
    }
    cout << max_ << endl;
    return 0;
}

/*
  关键在于读懂题意， 不必非得 s 开始， 对于 Kruskal算法而言， 重点不是点， 而是边， 但结果可以理解为从任意边开始
  prim算法， 可以更为直观的表现出 从 s 开始的情况（但算法角度上没有什么意义）
 */