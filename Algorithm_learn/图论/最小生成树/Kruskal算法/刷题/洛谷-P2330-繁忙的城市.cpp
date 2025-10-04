#include<bits/stdc++.h>

using namespace std;

const int N = 305;
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

bool same(int a, int b) {
    return find(a) == find(b);
}

void join(int a, int b) {
    a = find(a);
    b = find(b);
    if(rk[a] <= rk[b]) father[a] = b;
    else father[b] = a;

    if(rk[a] == rk[b] && a != b) rk[b]++;
}

int n, m;

struct Edge{
    int s, t, val;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    int s, t, val;
    Edge edges[m];
    for(int i = 0; i < m; i++) {
        cin >> s >> t >> val;
        edges[i] = {s, t, val};
    }
    // 按边权从小到大排序
    sort(edges, edges + m, [](const Edge& a, const Edge& b) {
        return a.val < b.val;
    });

    init();

    int cnt = 0;
    int max_ = 0;
    for(Edge edge: edges) {
        if(cnt == n-1) break;
        if(!same(edge.s, edge.t)) {
            join(edge.s, edge.t);
            if(max_ < edge.val) max_ = edge.val;
            cnt++;
        }
    }
    cout << cnt << " " << max_ << endl;
    return 0;
}
