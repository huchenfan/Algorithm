#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;

    vector<vector<int>> array(n + 1, vector<int>(n + 1, INF));
    for (int i = 0; i < k; ++i) {
        int s, t, value;
        cin >> s >> t >> value;
        array[s][t] = value; // 有向图
    }

    vector<int> minDistance(n + 1, INF);
    vector<bool> visited(n + 1, false);

    minDistance[1] = 0; // 假设从节点1出发

    for (int i = 1; i <= n; ++i) {
        int cur = -1;
        int minvalue = INF;

        // 第一步: 找到离原点最近的且非被访问的节点
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && minDistance[j] < minvalue) {
                minvalue = minDistance[j];
                cur = j;
            }
        }

        if (cur == -1) break; // 所有可达节点已访问, 退出循环

        // 第二步: 标记被访问
        visited[cur] = true;

        // 第三步: 更新所有为访问节点的minDistance
        for (int t = 1; t <= n; ++t) {
            if (!visited[t] && minDistance[t] > minvalue + array[cur][t]) {
                minDistance[t] = minvalue + array[cur][t];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (minDistance[i] == INF) minDistance[i] = -1; // 不可达
        cout << minDistance[i] << " ";
    }
    cout << endl;

    return 0;
}