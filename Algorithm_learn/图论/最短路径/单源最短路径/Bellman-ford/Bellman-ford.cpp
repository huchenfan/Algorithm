#include<bits/stdc++.h>

using namespace std;

const int N = 505;
int minDist[N];

int n, m;
struct Edge {
    int u, v, val;
};

int main() {
    memset(minDist, 0x3f, sizeof(minDist));
    cin >> n >> m;
    Edge edges[m];
    int s, t, val;
    for(int i = 0; i < m; i++) {
        cin >> s >> t >> val;
        edges[i] = {s, t, val};
    }

    int start = 1;
    minDist[start] = 0;

    bool flag = false;

    for(int i = 1; i <= n; i++) {
        if(i < n){
            for(Edge edge : edges) {
                if(minDist[edge.v] > minDist[edge.u] + edge.val) {
                    minDist[edge.v] = minDist[edge.u] + edge.val;
                }
            }
        }else{
            for(Edge edge : edges) {
                if(minDist[edge.v] > minDist[edge.u] + edge.val) {
                   flag = true;
                }
            }
        }
    }

    if(flag) {
        cout << "FALSE" << endl;
        return 0;
    }

    for(int i = 1; i <= n; i++) {
        cout << minDist[i] << " ";
    }
    cout << endl;
    return 0;
}