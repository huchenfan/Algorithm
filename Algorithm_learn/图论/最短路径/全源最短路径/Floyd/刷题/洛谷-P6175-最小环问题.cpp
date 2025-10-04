#include<bits/stdc++.h>

using namespace std;

const int N = 105;
long long grid[N][N];
long long edges[N][N];
long long min_ = 1e18;
int n, m;

void Floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                min_ = min(min_, grid[i][j] + edges[i][k] + edges[k][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                grid[i][j] = min(grid[i][k] + grid[k][j], grid[i][j]);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(&grid[0][0], &grid[0][0]+ N*N, 1e18);
    cin >> n >> m;
    while(m--) {
        int s, t, val;
        cin >> s >> t >> val;
        grid[s][t] = grid[t][s] = val;
    }
    for(int i = 1; i <= n; i++) {
        grid[i][i] = 0;
    }
    memcpy(edges, grid, sizeof(edges));
    Floyd();
    if(min_ == 1e18) {
        cout << "No solution." << endl;
        return 0;
    }
    cout << min_ << endl;
    return 0;
}

/*
 * 题解：
 *      核心是利用了Floyd算法的思想 【动态变化， 层层递进】
 *          在 K层 还没有变化之前， 利用 k-1层 找寻最小环
 *              其中 i， j < k, i < j, 为什么？
 *                  i, j 小于 k 是为了防止最小环中出现两次 k
 *                  i 小于 j 是为了防止环含有两个 i，也是为了防止重复运算
 *
 */
