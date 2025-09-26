#include <bits/stdc++.h>

using namespace std;

int n, m;
int val[10] = {0};
int state[10] = {0};
int arr[10];
int res;


void dfs(int cur, int min) {
    if(cur > m) {
        int sum = 0;

        for(int i = 1; i <= m; i++){
            sum += arr[val[i]];
        }
        for(int i = 2; i < sum / i; i++) {
            if(sum % i == 0){
                return;
            }
        }
        res++;
        return;
    }
    for(int i = min; i <= n; i++) {
        if(state[i] == 0) {
            val[cur] = i;
            state[i] = 1;
            dfs(cur+1, i + 1);
            state[i] = 0;  // 复原
        }
    }
}

int main() {
    cin >> n >> m;
    val[m+1] = 10;
    for(int i = 1; i<=n; i++) {
        int s;
        cin >> s;
        arr[i] = s;
    }
    dfs(1, 1);
    cout << res << endl;
    return 0;
}