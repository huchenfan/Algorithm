#include<bits/stdc++.h>

using namespace std;

const int N = 105;
int minDist[N];
bool visited[N];
int grid[N][N];
int n, m;

int main() {
    fill(minDist, minDist+N, 1e9);
    memset(visited, false, sizeof(visited));
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n ;
    int val;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> val;
            grid[i][j] = val;
        }
    }
    minDist[1] = 0;
    for(int i = 1; i <= n; i++) {
        int cur = -1;
        int min_ = 1e9;
        for(int t = 1; t <= n; t++) {
            if (!visited[t] && minDist[t] < min_) {
                min_ = minDist[t];
                cur = t;
            }
        }
        if(cur==-1) break;
        visited[cur] = true;

        for(int j = 1; j <= n; j++) {
            if(!visited[j] && minDist[j] > grid[cur][j]) {
                minDist[j] = grid[cur][j];
            }
        }
    }
    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += minDist[i];
    }
    cout << sum << endl;
    return 0;
}

/*

    一样的【稠密图】， 用朴素版即可

*/