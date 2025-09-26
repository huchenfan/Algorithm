#include <bits/stdc++.h>

using namespace std;


const int K = 7;
int val[K] = {0};
int n, k;
int res = 0;


// 其中的start的参数可以看成一种剪枝， 也可以看成一个判断是否重复的条件
void dfs(int cur, int start, int sum) {
    if (cur > k) {
        if (sum == n) {
            res++;
            return;
        }
        return;
    }

    for (int i = start; sum + i * (k - cur + 1) <= n; i++) {   // 这里剪枝了
        val[cur] = i;
        dfs(cur + 1, val[cur], sum + i);
        val[cur] = 0;
    }

}

int main() {
    cin >> n >> k;
    dfs(1, 1, 0);
    cout << res << endl;
    return 0;
}