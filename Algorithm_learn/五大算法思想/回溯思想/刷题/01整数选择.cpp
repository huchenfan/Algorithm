#include<iostream>
#include<cmath>

using namespace std;

int const N = 500;
int arr[N];
int n;

int min_ = 0xFFFFFFF;
int x[N];
int ans[N];
int sum = 0;
int r = 0;

void solve(int index) {
    if(index == n-1) {
        int result = abs(sum -r);
        if(min_ > result) {
            min_ = result;
            for (int i = 0; i < n; i++) {
                ans[i] = x[i];
            }
        }
    }
    else {
        x[index] = 1;
        sum += arr[index];
        solve(index+1);
        // 恢复现场
        sum -= arr[index];

        x[index] = 0;
        r += arr[index];
        solve(index+1);
        // 恢复现场
        r -= arr[index];

    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    solve(0);
    for(int i = 0; i < n; i++) {
        if(ans[i] == 1) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
    cout << min_ << endl;
    return 0;
}