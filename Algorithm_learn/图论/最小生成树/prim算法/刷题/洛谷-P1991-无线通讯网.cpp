#include<bits/stdc++.h>

using namespace std;

const int N = 505;
int x[N];
int y[N];
bool visited[N];
double minDist[N];

int n, m;

double sqr(int num) { return (double) num * (double) num; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(minDist, minDist + N, 1e18);
    memset(visited, false, sizeof(visited));
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    };

    priority_queue<double> pq;

    minDist[0] = 0;
    for (int round = 0; round < n; round++) {
        int cur = 0;
        double min_ = 1e18;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && minDist[i] < min_) {
                min_ = minDist[i];
                cur = i;
            }
        }

        pq.emplace(minDist[cur]);
        visited[cur] = true;

        for (int j = 0; j < n; j++) {
            if (visited[j]) continue;
            int distance_x = x[cur] - x[j];
            int distance_y = y[cur] - y[j];
            double distance = sqrt(sqr(distance_x) + sqr(distance_y));
            if (minDist[j] > distance) minDist[j] = distance;
        }
    }

    while(--m >= 1) {
        pq.pop();
    }
    double max_ = pq.top();

    cout << fixed << setprecision(2) << max_;
    return 0;
}

/*

    这题是个稠密图， 用 prim算法的朴素版更好，更快

 */