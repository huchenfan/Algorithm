#include <bits/stdc++.h>

using namespace std;

int n;
int val[10] = {0};
int state[10] = {0};

void dfs(int cur) {
    if(cur > n) {
        for(int i = 1; i <= n; i++){
            cout << val[i] << " ";
        }
        cout << endl;
        return;
    }
    for(int i = 1; i <= n; i++) {
        if(state[i] == 0) {
            val[cur] = i;
            state[i] = 1;
            dfs(cur+1);
            state[i] = 0;  // 复原
        }

    }
}

int main() {
    cin >> n;
    dfs(1);
    return 0;
}