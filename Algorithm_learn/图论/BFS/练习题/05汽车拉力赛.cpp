#include<bits/stdc++.h>
#include <cstring>

using namespace std;

typedef pair<int, int> QUE;
int dix[4] = {0, 1, 0, -1};
int diy[4] = {1, 0, -1, 0};
int high[510][510];
int flag[510][510];


bool check(int d, int x, int y, int n, int m, int flagTotal) {
    bool visited[n][m];
    memset(visited, false, sizeof(visited));   // 放在两层循环之前
    QUE pq[n * m];
    int hh = 0;
    int tt = -1;
    pq[++tt] = {x, y};
    visited[x][y] = true;
    int count = 0;
    while(tt- hh >=0) {
        pair<int, int> cur = pq[hh]; hh++;
        int next_x, next_y;
        for(int i = 0; i < 4; i++) {
            next_x = cur.first + dix[i];
            next_y = cur.second + diy[i];
            if(next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) continue;
            if(abs(high[cur.first][cur.second] - high[next_x][next_y]) > d) continue;
            if(visited[next_x][next_y]) continue;
            if(flag[next_x][next_y] == 1){
                count++;
                if(count == flagTotal - 1) {
                    return true;
                }
            }
            visited[next_x][next_y] = true;
            pq[++tt] = {next_x, next_y};
        }
    }
    return false;
}


int main() {
    // 输入矩阵大小
    int n, m;
    cin >> n >> m;

    // 输入海拔高度
    int max = -1, min = 1e9;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int val;
            cin >> val;
            high[i][j]= val;
            if(max <= val) max = val;
            if(min >= val) min = val;
        }
    }
    int max_min = max - min;

    // 输入路标
    int flagTotal = 0;
    pair<int, int> start;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int val;
            cin >> val;
            flag[i][j] = val;
            if(val == 1) {
                flagTotal++;
                start = {i, j};
            }
        }
    }

    int l = 1, r = max_min;

    while(l < r) {
        int mid = l + (r - l) / 2;
        if(check(mid, start.first, start.second, n, m, flagTotal)) {
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    cout << l << endl;
    return 0;
}





