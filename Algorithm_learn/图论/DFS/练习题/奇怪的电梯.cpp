//================================================DFS会超时============================================================//
//#include <bits/stdc++.h>
//
//using namespace std;
//
//const int N = 201;
//int arr[N] = {0};
//int visited[N] = {0};
//int n, A, B;
//int res = 1e9;
//
//
//void dfs(int cur, int count) {
//    if(count >= 200) return;
//    if (cur > n || cur <= 0) return;
//    if (cur == B) {
//        if (count < res) {
//            res = count;
//        }
//        return;
//    }
//
//    if (!visited[cur + arr[cur]]) {
//        visited[cur + arr[cur]] = 1;
//        dfs(cur + arr[cur], count + 1);
//        visited[cur + arr[cur]] = 0;
//    }
//    if (!visited[cur - arr[cur]]) {
//        visited[cur - arr[cur]] = 1;
//        dfs(cur - arr[cur], count + 1);
//        visited[cur - arr[cur]] = 0;
//    }
//}
//
//
//int main() {
//    cin >> n >> A >> B;
//    for(int i = 1; i <= n; i++) {
//        cin >> arr[i];
//    }
//    visited[A] = 1;
//    dfs(A, 0);
//    if(res == 1e9) res = -1;
//
//    cout << res << endl;
//    return 0;
//}

//=========================================BFS========================================================================//

#include <bits/stdc++.h>

using namespace std;

int n, A, B;
const int N = 201;
int arr[N];
int dist[N] = {0};
int visited[N] = {0};

int main() {
    cin >> n >> A >> B;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    queue<int> pq;
    pq.push(A);
    visited[A] = 1;
    dist[A] = 0;
    while(!pq.empty()) {
        int cur = pq.front(); pq.pop();
        if(cur == B) {
            cout << dist[B] << endl;
            return 0;
        }
        if(cur+arr[cur] < N && !visited[cur+arr[cur]]) {
            pq.push(cur+arr[cur]);
            visited[cur+arr[cur]] = 1;
            dist[cur+arr[cur]] = dist[cur] + 1;
        }
        if(cur-arr[cur] > 0 && !visited[cur-arr[cur]]) {
            pq.push(cur-arr[cur]);
            visited[cur-arr[cur]] = 1;
            dist[cur-arr[cur]] = dist[cur] + 1;
        }

    }
    cout << -1 << endl;
    return 0;
}

