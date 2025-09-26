#include <bits/stdc++.h>

using namespace std;

const int N = 11;
int s[N] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, b[N] = {0};

int n;
int MIN = 1e9;

void dfs(int cur, int count) {
    if(MIN == 0) {
        return;
    }
    if(cur > n) {
        if(count == 0) return;
        int sTotal = 1, bTotal = 0;
        for(int i = 1; i <= n; i++) {
            sTotal *= s[i];
            bTotal += b[i];
        }
        if(MIN > abs(sTotal - bTotal)) {
            MIN = abs(sTotal - bTotal);
        }
        return;
    }
    for(int i = 0; i < 2; i++) {
        if(!i) {
            int sTmp = s[cur], bTmp = b[cur];
            s[cur] = 1;
            b[cur] = 0;
            dfs(cur+1, count);
            s[cur] = sTmp;
            b[cur] = bTmp;
        }else{
            dfs(cur+1, count+1);
        }
    }
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> s[i] >> b[i];
    }
    dfs(1, 0);
    cout << MIN << endl;
    return 0;
}

// 可能出现的问题， 题目要求必须至少由一种， 不可以全部不选（如果可以全不选，最小值都是 1）