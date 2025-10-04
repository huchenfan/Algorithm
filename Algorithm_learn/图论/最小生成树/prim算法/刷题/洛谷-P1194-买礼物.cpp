#include<bits/stdc++.h>

using namespace std;

const int N = 505;
bool visited[N];
int minDist[N];
int grid[N][N];

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(visited, false, sizeof(visited));
    fill(minDist, minDist + N, 1e9);
    cin >> n >> m;
    int val;
    for(int i = 0; i < m; i++) {
        for(int  j = 0; j < m; j++) {
           cin >> val;
           if(val == 0) {
               grid[i][j] = n;
               continue;
           }
           if(val > n) {
               grid[i][j] = n;
               continue;
           }
           grid[i][j] = val;
        }
    }

    minDist[0] = 0;

    for (int round = 0; round < m; round++) {
        int cur = 0;
        int min_ = 1e9;
        for (int i = 0; i < m; i++) {
            if (!visited[i] && min_ > minDist[i]) {
                min_ = minDist[i];
                cur = i;
            }
        }

        visited[cur] = true;

        for (int i = 0; i < m; i++) {
            if (!visited[i] && minDist[i] > grid[cur][i]) {
                minDist[i] = grid[cur][i];
            }
        }
    }

    long long sum = n;

    for(int i = 0; i < m; i++) {
        sum += minDist[i];
    };

    cout << sum << endl;
    return 0;
}