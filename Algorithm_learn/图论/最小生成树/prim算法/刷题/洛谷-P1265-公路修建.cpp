#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5005;
struct Pt { ll x, y; } p[N];
double minDist[N];
bool vis[N];
int n;

double sqr(ll x) { return (double)x * (double)x; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;

    fill(minDist, minDist + n, 1e18);
    minDist[0] = 0;
    for (int round = 0; round < n; ++round) {
        int u = -1;
        double best = 1e18;
        for (int i = 0; i < n; ++i)
            if (!vis[i] && minDist[i] < best) { best = minDist[i]; u = i; }
        vis[u] = true;
        for (int v = 0; v < n; ++v) {
            if (vis[v]) continue;
            ll dx = p[u].x - p[v].x, dy = p[u].y - p[v].y;
            double w = sqrt(sqr(dx) + sqr(dy));
            if (w < minDist[v]) minDist[v] = w;
        }
    }
    double ans = accumulate(minDist, minDist + n, 0.0);
    cout << fixed << setprecision(2) << ans;
    return 0;
}

/*
 为什么用朴素版？
    因为这是一个【稠密图】， 用优先队列优化版反而变得更慢了， 其时间复杂度是O(n^2*log(n))
    而朴素版时间复杂度 才O(n^2)。
*/
