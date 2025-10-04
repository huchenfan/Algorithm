#include<bits/stdc++.h>

using namespace std;

const int N = 105;
vector<vector<int>> grid(N);
int indgree[N];
int ans[N];

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(indgree, indgree + N, 0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int num = -1;
        while(num != 0) {
            cin >> num;
            grid[i].push_back(num);
            indgree[num]++;
        }
    }

    queue<int> q;

    for(int i = 1; i<=n; i++) {
        if(indgree[i] == 0) q.push(i);
    }

    int cnt = 0;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        ans[cnt++] = cur;

        for(int i : grid[cur]) {
            indgree[i]--;
            if(indgree[i] == 0) q.push(i);
        }
    }

    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}