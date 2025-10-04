#include<bits/stdc++.h>

using namespace std;

const int N = 3005;
long long minDist[N];
vector<vector<pair<int, int>>> grid(N);
bool inQueue[N];
int visited[N];
int h[N];
int cnt[N] = {0};

int n, m;

bool Bellman_ford() {
    for(int i = 1; i <= n; i++) {
        grid[0].emplace_back(i, 0);
    }
    deque<int> dq;
    h[0] = 0;
    inQueue[0] = true;
    dq.push_back(0);
    cnt[0]++;
    while(!dq.empty()) {
        int cur = dq.front();
        dq.pop_front();
        inQueue[cur] = false;
        if(cnt[cur] >= n+1) {
            cout << -1 << endl;
            return false;
        }

        for(pair<int, int> edge: grid[cur]) {
            if(h[edge.first] > h[cur] + edge.second) {
                h[edge.first] = h[cur] + edge.second;
                cnt[edge.first]++;
                if(!inQueue[edge.first]) {
                    inQueue[edge.first] = true;
                    if (!dq.empty() && h[dq.front()] > h[edge.first])  // 这里之前我的不等号反过
                        dq.push_front(edge.first);
                    else
                        dq.push_back(edge.first);
                }
            }
        }
    }
    return true;
}

void Dijkstra() {
    long long ans[N] = {0};
    for(int i = 1; i <= n; i++) {
        fill(minDist, minDist+N, 1e9);
        memset(visited, false, sizeof(visited));
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        minDist[i] = 0;
        pq.emplace(0, i);
        while(!pq.empty()) {
            pair<long long, int> cur = pq.top();
            pq.pop();
            if(visited[cur.second]) continue;
            visited[cur.second] = true;
            for(pair<int, int> edge : grid[cur.second]) {
                if(!visited[edge.first] && minDist[edge.first] > cur.first + edge.second) {
                    minDist[edge.first] = cur.first + edge.second;
                    pq.emplace(minDist[edge.first], edge.first);
                }
            }
        }
        for(int j = 1; j <= n; j++) {
            long long real = minDist[j] == 1e9 ? 1e9 : minDist[j] - h[i] + h[j];
            ans[i] += real * j;
        }
        cout << ans[i] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(minDist, minDist+N, 1e9);
    fill(h, h+N, 1e9);
    memset(inQueue, false, sizeof(inQueue));
    memset(visited, false, sizeof(visited));
    cin >> n >> m;
    while(m--) {
        int s, t, val;
        cin>>s>>t>>val;
        grid[s].emplace_back(t, val);
    }
    if(!Bellman_ford()) return 0;

    for(int i = 1; i <= n; i++) {
//        for(pair<int, int> edge: grid[i]) {  // 这是【按值拷贝】，你改的是拷贝变量，原图权重纹丝不动
//            edge.second += minDist[i] - minDist[edge.first];
//        }
        for (auto &[v, w] : grid[i])          // C++17
            w += h[i] - h[v];     // i→v 的新权值
    }
    Dijkstra();
    return 0;
}
