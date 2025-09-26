#include<bits/stdc++.h>

using namespace std;
const int N = 20;

int state[N];
int n;

void dfs(int cur) {
    if(cur > n) {
        for(int i = 1; i <= n; i++){
           if(state[i] == 1) cout << i << " ";
        }
        cout << endl;
        return;
    }

    // 不选
    state[cur] = 2;
    dfs(cur + 1);
    state[cur] = 0;  // 复原
    // 选
    state[cur] = 1;
    dfs(cur + 1);
    state[cur] = 0;  // 复原
}

int main() {
    cin >> n;
    dfs(1);
    return 0;
}