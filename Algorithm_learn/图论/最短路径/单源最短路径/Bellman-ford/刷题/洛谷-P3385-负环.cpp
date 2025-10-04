#include<bits/stdc++.h>

using namespace std;

const int N = 2005;
int minDist[N];
int inQueue[N];
int cnt[N];
int T, n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while(T--) {
        fill(minDist, minDist+N, 1e9);
        memset(inQueue, false, sizeof(inQueue));
        fill(cnt, cnt+N, 0);
        vector<vector<pair<int, int>>> grid(N);
        bool flag = true;
        cin >> n >> m;
        while(m--) {
            int s, t, val;
            cin >> s >> t >> val;
            if(val < 0) {
                grid[s].emplace_back(t, val);
            } else{
                grid[s].emplace_back(t, val);
                grid[t].emplace_back(s, val);
            }
        }
        deque<int> q;
        minDist[1] = 0;
        inQueue[1] = true;
        cnt[1]++;
        q.push_back(1);
        while(!q.empty()) {
            int cur = q.front();
            q.pop_front();
            inQueue[cur] = false;
            if(cnt[cur] >= n) {
                cout << "YES" << endl;
                flag = false;
                break;
            }
            for(pair<int, int> edge : grid[cur]) {
                if(minDist[edge.first] > minDist[cur] + edge.second) {
                    minDist[edge.first] = minDist[cur] + edge.second;
                    if(!inQueue[edge.first]) {
                        if (!q.empty() && minDist[q.front()] < minDist[edge.first])
                            q.push_back(edge.first);
                        else
                            q.push_front(edge.first);
                        inQueue[edge.first] = true;
                        cnt[edge.first]++;
                    }
                }
            }
        }
        if(flag) cout << "NO" << endl;
    }
    return 0;
}

