//#include<bits/stdc++.h>
//
//using namespace std;
//
//
//int n, m;
//
//int main() {
//    cin >> n >> m;
//    int grid[n+1][n+1];
//    int minDist[n+1];
//    bool visited[n+1];
//
//    fill(minDist, minDist+n+1, 0x3f3f3f3f);
//    fill(grid, grid + (n+1)*(n+1), 0x3f3f3f3f);
//    memset(visited, false, sizeof(visited));
//
//    int s, t, val;
//    while(m--) {
//        cin >> s >> t >>val;
//        grid[s][t] = grid[t][s] = val;  // 无向图
//    }
//
//    minDist[1] = 0;
//    int cnt = 0;
//
//    for(int round = 1; round <= n; round++) {
//        int cur = -1;
//        int min = 0x3f;
//        for(int i = 1; i <= n; i++) {
//            if(!visited[i] && minDist[i] < min) {
//                min = minDist[i];
//                cur = i;
//            }
//        }
//
//        if(cur == -1) break;
//
//        visited[cur] = true;
//        cnt++;
//
//        for(int i = 1; i <= n; i++) {
//            if(!visited[i] && minDist[i] > grid[cur][i]) {
//                minDist[i] = grid[cur][i];
//            }
//        }
//    }
//    if(cnt < n)  {
//        cout << "orz" << endl;
//        return 0;
//    }
//    int sum = 0;
//    for(int i = 1; i <= n; i++) {
//        sum += minDist[i];
//    }
//    cout << sum << endl;
//    return 0;
//}

/*
朴素版：
    问题（不是思路问题）：
        变量名 min 跟 <algorithm>
        数组开在 main 里，n≤5000 时 int grid[n+1][n+1] 约 100 MB，栈空间超限，会 SEGV。
        没关流同步，cin 读 2×10^5 条边超时。
    优化方法：
        1. min改名成 min_
        2. 数组开再 全局变量中
        3. 关流， 在 cin 前加上：     std::ios::sync_with_stdio(false);
                                   std::cin.tie(nullptr);          // 有时也写作 0
 * */


#include<bits/stdc++.h>

using namespace std;

const int N = 5005;
int minDist[N];
int visited[N];
vector<vector<pair<int, int>>> grid(N);

int n, m;

int main() {
    fill(minDist, minDist+N, 0x3f3f3f3f);
    memset(visited, false, sizeof(visited));

    // 关流
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);          // 有时也写作 0

    cin >> n >> m;
    int s, t, val;
    while(m--) {
        cin >> s >> t >> val;
        grid[s].emplace_back(t, val);
        grid[t].emplace_back(s, val);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    minDist[1] = 0;
    pq.emplace(0, 1);
    int cnt = 0;
    while(!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();

        visited[cur.second] = true;
        cnt++;

        for(pair<int, int> edge : grid[cur.second]) {
            if(!visited[edge.first] && minDist[edge.first] > edge.second) {
                minDist[edge.first] = edge.second;
                pq.emplace(edge.second, edge.first);
            }
        }
    }
    if(cnt < n) {
        cout << "orz" << endl;
        return 0;
    }
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += minDist[i];
    }
    cout << sum << endl;
    return 0;
}


















