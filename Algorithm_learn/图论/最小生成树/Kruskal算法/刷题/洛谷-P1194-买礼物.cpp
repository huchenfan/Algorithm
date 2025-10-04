#include<bits/stdc++.h>

using namespace std;

const int N = 505;
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
    if(m == 1) {
        Edge edges[1];
        int val;
        cin >> val;
        edges[0] = {1, 1, n};
        cout << n << endl;
        return 0;
    }
    int total = m*(m-1)/2;
    int val;
    Edge edges[total];
    int count = 0;

    for(int i = 1; i <= m; i++) {
        bool flag = false;
        for(int j = 1; j <= m; j++) {
            cin >> val;
            if( i == j) {
                flag = true;
                continue;
            }
            if(flag){
                if(val == 0) edges[count++] = {i, j, n};
                else if(val > n) edges[count++] = {i, j, n};
                else edges[count++] = {i, j, val};
            }
        }
    }


    // 按边权从小到大排序
    sort(edges, edges + total, [](const Edge& a, const Edge& b) {
        return a.val < b.val;
    });

    init();

    int cnt = 0;
    long long sum = n;
    for(Edge edge: edges) {
        if(cnt == m-1) break;
        if(!same(edge.s, edge.t)) {
            join(edge.s, edge.t);
            sum += edge.val;
            cnt++;
        }
    }

    cout << sum << endl;
    return 0;
}