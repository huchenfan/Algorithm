//#include<bits/stdc++.h>
//
//using namespace std;
//
//
//
//int main() {
//    int n, m;
//    cin >> n >> m;
//    int dp[n+1][n+1][n+1];
//    memset(dp, 0x3f, sizeof(dp));
//
//    int s, t, val;
//    while(m--) {
//        cin >> s >> t >> val;
//        dp[s][t][0] = dp[t][s][0] = val;  // 无向图
//    }
//    for(int k = 1; k <= n; k++) {
//        for(int i = 1; i <= n; i++) {
//            for(int j = 1; j <= n; j++) {
//                dp[i][j][k] = min(dp[i][k][k-1]+dp[k][j][k-1], dp[i][j][k-1]);
//            }
//        }
//    }
//    int count, start, end;
//    cin >> count;
//    while(count--) {
//        cin >> start >> end;
//        if(dp[start][end][n] >= 0x3f) {
//            cout << -1 << endl;
//        } else{
//            cout << dp[start][end][n] << endl;
//        }
//    }
//
//    return 0;
//}

//---------------------------------------------- 空间优化版 ------------------------------------------------------------//
#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int dp[n + 1][n + 1];
    memset(dp, 0x3f, sizeof(dp));

    int s, t, val;
    while (m--) {
        cin >> s >> t >> val;
        dp[s][t] = dp[t][s] = val;  // 无向图
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);   // 更新动态数组
            }
        }
    }
    int count, start, end;
    cin >> count;
    while (count--) {
        cin >> start >> end;
        if (dp[start][end] >= 0x3f) {
            cout << -1 << endl;
        } else {
            cout << dp[start][end] << endl;
        }
    }

    return 0;
}

