#include<bits/stdc++.h>

using namespace std;
const int N = 20;
int n;
string words[N];
int grid[N][N] = {0};
int vis[N] = {0};
int res = 0;

void dfs(string sum, int cur) {
    if(res < sum.size()) res = sum.size();

    vis[cur]++;
    if(vis[cur] > 2) return;

    for(int i = 0; i < n; i++) {
        int tmp = grid[cur][i];
        if(tmp && vis[i] < 2) {
            dfs(sum + words[i].substr(tmp), i);
        }
    }
    vis[cur]--; // 恢复现场
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> words[i];
    }

    char start;
    cin >> start;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            string a = words[i], b = words[j];
            for(int k = 1; k < min(a.size(), b.size()); k++) {
                if(a.substr(a.size()-k, k) == b.substr(0, k)) {
                    grid[i][j] = k;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(words[i][0] == start) {
            dfs(words[i], i);
        }
    }
    cout << res << endl;
    return 0;
}



















