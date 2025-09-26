//#include<bits/stdc++.h>
//using namespace std;
//
//int n, m;
//int val[10] = {0};
//int state[10] = {0};
//
//void dfs(int cur) {
//    if(cur > m) {
//        for(int i = 1; i <= m; i++){
//            cout << val[i] << " ";
//        }
//        cout << endl;
//        return;
//    }
//    for(int i = 1 + val[cur - 1]; i <= n; i++) {
//        if(state[i] == 0) {
//            val[cur] = i;
//            state[i] = 1;
//            dfs(cur+1);
//            state[i] = 0;  // 复原
//        }
//    }
//}
//
//int main() {
//    cin >> n >> m;
//    val[m+1] = 10;
//    dfs(1);
//    return 0;
//}


#include <bits/stdc++.h>

using namespace std;

int n, m;
int val[10] = {0};
int state[10] = {0};

void dfs(int cur, int min) {
    if(cur > m) {
        for(int i = 1; i <= m; i++){
            cout << val[i] << " ";
        }
        cout << endl;
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
    dfs(1, 1);
    return 0;
}