#include<bits/stdc++.h>

using namespace std;

const int N = 105;
int inDegree[N];
int outDegree[N];
long long C[N];
vector<vector<pair<int, int>>> grid(N);

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int c, u;
        cin >> c >> u;
        if(c != 0) C[i] = c;
        else C[i] = c - u;
    }
    int s, t, val;
    while(m--) {
        cin >> s >> t >> val;
        grid[s].emplace_back(t, val);
        inDegree[t]++;
        outDegree[s]++;
    }

    queue<int> q;

    for(int i = 1; i <= n; i++) {
        if(inDegree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        if(C[cur])
        for(pair<int, int> edge : grid[cur]) {
            if(C[cur] > 0) C[edge.first] += edge.second * C[cur];
            inDegree[edge.first]--;
            if(inDegree[edge.first] == 0) {
                q.push(edge.first);
            }
        }
    }

    int count = 0;
    for(int i = 1; i <= n; i++ ) {
        if(outDegree[i] == 0) {
            if(C[i] > 0) {
                cout << i << " " << C[i] << endl;
                count++;
            }
        }
    }
    if(count == 0) cout << "NULL" << endl;

    return 0;
}

