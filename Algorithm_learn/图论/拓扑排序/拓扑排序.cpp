//---------------------------------------------- 朴素版， 循环 -----------------------------------------------------------
//#include<bits/stdc++.h>
//
//using namespace std;
//
//const int N = 505;
//vector<vector<int>> grid(N);
//int indgree[N] = {0};
//int ans[N];
//
//int n, m;
//
//int main() {
//    cin >> n >> m;
//    int s, t;
//    while(m--) {
//        cin >> s >> t;
//        grid[s].push_back(t);
//        indgree[t]++;
//    }
//    int cnt = 0;
//    for(int i = 0; i < n; i++) {
//        for(int j = 0; j < n; j++) {
//            if(indgree[j] == 0) {
//                ans[cnt++] = j;
//                indgree[j]--;
//                for(int r : grid[j]) {
//                    indgree[r]--;
//                }
//            }
//        }
//    }
//
//    if(cnt != n) {
//        cout << "FALSE" << endl;
//        return 0;
//    }
//
//    for(int i = 0; i < n; i++) {
//        cout << ans[i] << " ";
//    }
//    cout << endl;
//    return 0;
//}

//----------------------------------------------Kahn算法 类似 BFS 队列版 -------------------------------------------------

#include<bits/stdc++.h>

using namespace std;

const int N = 505;
int indgree[N] = {0};
int ans[N];
vector<vector<int>> grid(N);

int n, m;

int main() {
    cin >> n >> m;
    int s, t;
    while(m--) {
        cin >> s >> t;
        grid[s].push_back(t);
        indgree[t]++;
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indgree[i] == 0) q.push(i);
    }

    int cnt = 0;

    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        ans[cnt++] = cur;
        for(int r : grid[cur]) {
            indgree[r]--;
            if(indgree[r] == 0) {
                q.push(r);
            }
        }
    }

    if(cnt != n) {
        cout << "FALSE" << endl;
        return 0;
    }

    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}
