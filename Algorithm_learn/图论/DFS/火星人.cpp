 #include<bits/stdc++.h>

using namespace std;

// ================================================康托压缩==============================================================
// 为什么不行， 因为阶乘太大了， 没有必要怎么算， 读懂题意可知， 只要从初始状态开始加即可， 没有必要把阶乘真的算出来（但想到康托压缩是好的）
//long long getInt(int n) {
//    long long total = 1;
//    for(int i = 2; i <= n; i++) {
//        total *= i;
//    }
//    return total;
//}
//
//long long cantor(const vector<int> &s, int n) {
//    long long code = 0;
//    for(int i = 0; i < n; i++) {
//        int cnt = 0;
//        for(int j = i+1; j < n; j++) {
//            if(s[i] > s[j]) ++cnt;
//        }
//        code += cnt * getInt(n - i - 1);
//    }
//    return code;
//}
//
//vector<int> inv_cantor(long long code, int n) {
//    vector<int> s(n);
//    vector<char> used(n, 0);
//    for (int i = 0; i < n; ++i) {
//        long long rk = code / getInt(n - i - 1);
//        code %= getInt(n - i - 1);
//        int pos = 0;
//        for (int j = 0; j < n; ++j) {
//            if (!used[j]) {
//                if (pos == rk) {
//                    s[i] = j + 1;
//                    used[j] = 1;
//                    break;
//                }
//                pos++;
//            }
//        }
//    }
//    return s;
//}
//
//
//int main() {
//    int n, m;
//    cin >> n >> m;
//    vector<int> val(n);
//    for(int i = 0; i < n; i++) {
//        cin >> val[i];
//    }
//    long long  ans_ = cantor(val, n) + m;
//    vector<int> ans = inv_cantor( ans_, n);
//    for(int i : ans) {
//        cout << i << " ";
//    }
//    cout << endl;
//    return 0;
//};


int n, m;
int val[10002];
int mars[10002];
int state[10002] = {0};
int res = 0;
bool flag = false;

void dfs(int cur) {
    if(flag) exit(0);
    if(cur > n) {
        res++;
        if(res == m + 1) {
            for(int i = 1; i <= n; i++) {
                cout << val[i] << " ";
            }
            cout << endl;
            flag = true;
        }
        return;
    }

    for(int i = 1; i <= n; i++) {
        if(!res) {
            i = mars[cur];
        }
        if(state[i] == 0) {
            val[cur] = i;
            state[i] = 1;
            dfs(cur + 1);
            state[i] = 0;
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n ; i++) {
        cin >> mars[i];
    }
    dfs(1);
    return 0;
}

