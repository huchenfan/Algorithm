#include<bits/stdc++.h>

using namespace std;

const int N = 55;
bool visited[N];
long long minDist[N];
int x[N];
int y[N];

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(visited, false, sizeof(visited));
    fill(minDist, minDist + N, 1e18);
    cin >> n;
    int s, t;
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        x[i] = s;
        y[i] = t;
    }

    minDist[0] = 0;

    long long max_ = 0;
    for (int round = 0; round < n; round++) {
        int cur = 0;
        long long min_ = 1e18;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && min_ > minDist[i]) {
                min_ = minDist[i];
                cur = i;
            }
        }

        visited[cur] = true;
        if (minDist[cur] > max_) max_ = minDist[cur];

        for (int i = 0; i < n; i++) {
            long long distance = abs(x[cur] - x[i]) + abs(y[cur] - y[i]);
            if (!visited[i] && minDist[i] > distance) {
                minDist[i] = distance;
            }
        }
    }

    long long time = (max_ + 1) / 2;

    cout << time << endl;
    return 0;
}
