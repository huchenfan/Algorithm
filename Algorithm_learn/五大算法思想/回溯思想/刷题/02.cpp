#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

int const N = 20;
int arr[N];
int n, m;

int min_ = 0xFFFFFFF;
vector<int> x, ans;
int sum = 0;
int r = 0;
int cnt = 0;

void solve(int index, int k) {
    if(k == m){
        cnt++;
        int result = abs(sum -r);
        if(min_ > result) {
            min_ = result;
            ans = x;
        }
        return;
    }

    if(m-k > n- index) return;
    if(sum - r > min_) return;
    int remaining = r;
    if (abs(sum - r) - remaining >= min_) return;

    x.push_back(arr[index]);
    sum += arr[index];
    r -= arr[index];
    solve(index+1, k+1);

    sum -= arr[index];
    r += arr[index];
    x.pop_back();
    solve(index+1, k);
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        arr[i] = tmp;
        r += tmp;
    }

    solve(0, 0);
    for(auto i : ans) {
        cout << i << " ";
    }
    cout << endl;

    cout << min_ << endl;

    cout << cnt << endl;
    return 0;
}