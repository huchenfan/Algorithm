#include<bits/stdc++.h>

using namespace std;

const int N = 505;
vector<vector<pair<int, int>>> edges(N);
int minDist[N];
bool inQueue[N];
int cnt[N] = {0};
int n, m;

int main() {
    memset(minDist, 0x3f, sizeof(minDist));
    memset(inQueue, false, sizeof(inQueue));

    cin >> n >> m;
    int s, t, val;
    while(m--) {
        cin >> s >> t >> val;
        edges[s].emplace_back(t, val);
    }

    int start = 1;
    minDist[start] = 0;
    deque<int> q;
    q.push_back(start);
    inQueue[start] = true;
    cnt[start]++;

    while(!q.empty()) {
        int cur = q.front();
        q.pop_front();
        if(cnt[cur] >= n) {
            cout << "FALSE" << endl;
            return 0;
        }
        inQueue[cur] = false;
        for(pair<int, int> edge : edges[cur]) {
            if(minDist[edge.first] > minDist[cur] + edge.second) {
                minDist[edge.first] = minDist[cur] + edge.second;
                cnt[edge.first]++;
                if(!inQueue[edge.first]) {
                    if (!q.empty() && minDist[q.front()] < minDist[edge.first])
                        q.push_back(edge.first);
                    else
                        q.push_front(edge.first);
                    inQueue[edge.first] = true;
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << minDist[i] << " ";
    }
    cout << endl;
    return 0;
}

