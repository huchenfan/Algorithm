#include<bits/stdc++.h>

using namespace std;

const int N = 5005, MOD = 80112002;
int indgree[N] = {0};
int outdgree[N] = {0};
vector<vector<int>> grid(N);
int dp[N];
int n, m;



int main() {
    cin >> n >> m;
    int s, t;
    while(m--) {
        cin >> s >> t;
        grid[s].push_back(t);
        indgree[t]++;
        outdgree[s]++;
    }

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(indgree[i] == 0) {
            q.push(i);
            dp[i] = 1;
        }
    }

    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int r: grid[cur]) {
            dp[r] = (dp[r] + dp[cur]) % MOD;
            indgree[r]--;
            if (indgree[r] == 0) {
                q.push(r);
            }
        }
    }


    long long ans = 0;
    for (int i = 1; i <= n; ++i) if (!outdgree[i]) ans = (ans + dp[i]) % 80112002;
    cout << ans << '\n';

    return 0;
}

/*
 * 题解：
 *      拓扑排序 + 动态数组
 *      为什么有拓扑排序？
 *          因为食物链天然的DAG(有向无环图)， 且本题求的是食物链的条数
 *              可能多起点多终点， 怎么来表示 --> 一个入度为零， 一个出度为零
 *      为什么用动态数组？
 *          用来统计食物链数量
 *              dp[r] = dp[r] + dp[cur]
 *              没有重复的， 因为终点一定不同， 这就是一个分支并入一个跟大的分支
 *
 *      如果本题你可以看出：
 *          就是一个图 --> 【入度为零】到【出度为零】的 路径总数;
 *      那你就会了
 * */

