#include <bits/stdc++.h>

using namespace std;

const int N = 712;
int arr[4] = {0};
int nums[N] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int n,res;

void dfs(int cur, int sum) {
    if(sum > n) return;
    if(cur > 3) {
        if(arr[1] + arr[2] == arr[3] && sum == n) {
            res++;
        }
            return;
    }

    for(int i = 0; i < N; i++) {
        arr[cur] = i;
        dfs(cur+1, sum + nums[i]);
    }
}

int main() {
    cin >> n;
    n -= 4;
    for(int i = 10; i < N; i++){
        nums[i] = nums[i%10] + nums[i/10];
    }   // 记忆化存储， 前面的计算结果为后面的计算提供帮助
    dfs(1, 0);
    cout << res << endl;
    return 0;
}
