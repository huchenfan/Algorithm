//#include <bits/stdc++.h>
//
//using namespace std;
//
//struct Edge{
//    int s, t, val;
//};
//
//const int N = 2505;
//int minDist[N];
//
//int n, m, start_, end_;
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    fill(minDist, minDist+N, 1e9);
//    cin >> n >> m >> start_ >> end_;
//    Edge edges[m*2];
//    int count = 0;
//    for(int i = 0; i < m; i++) {
//        int s, t, val;
//        cin >> s >> t >> val;
//        edges[count++] = {s, t, val};
//        edges[count++] = {t, s, val};
//    }
//    minDist[start_] = 0;
//
//    for(int i = 1; i < m; i++) {
//        for(Edge edge: edges) {
//            if(minDist[edge.t] > minDist[edge.s] + edge.val) {
//                minDist[edge.t] = minDist[edge.s] + edge.val;
//            }
//        }
//    }
//
//    cout << minDist[end_] << endl;
//    return 0;
//}

#include<bits/stdc++.h>

using namespace std;

const int N = 2505;
int minDist[N];
vector<vector<pair<int, int>>> grid(N);
bool inQueue[N];
int cnt[N] = {0};
int n, m, start_, end_;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(minDist, minDist+N, 1e9);
    memset(inQueue, false, sizeof(inQueue));
    cin >> n >> m >> start_ >> end_;
    while(m--) {
        int s, t, val;
        cin >> s >> t >> val;
        grid[s].emplace_back(t, val);
        grid[t].emplace_back(s, val);
    }
    queue<int> q;
    minDist[start_] = 0;
    q.push(start_);
    inQueue[start_] = true;
    cnt[start_]++;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        inQueue[cur] = false;
        if(cnt[cur] == n) {
            cout << "FALSE" << endl;
            return 0;
        }
        for(pair<int, int> edge : grid[cur]) {
            if(minDist[edge.first] > minDist[cur]+edge.second) {
                minDist[edge.first] = minDist[cur] + edge.second;
                cnt[edge.first]++;
                if(!inQueue[edge.first]) {
                    q.push(edge.first);
                    inQueue[edge.first] = true;
                }
            }
        }
    }
    cout << minDist[end_] << endl;
    return 0;
}