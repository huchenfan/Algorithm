#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n;
    int result[n];
    for(int round = 0; round < n; round++) {
        cin >> m;
        int arr[m];
        string s;
        cin >> s;
        for(int i = 0; i < s.size(); i++) {
            if(s[i]== 'a') arr[i] = 1;
            else arr[i] = -1;
        }
        int sum = 0;
        for(int i = 0; i < m; i++) {
            sum += arr[i];
        }
        if(sum == 0) {
            result[round] = 0;
        }
        else{
            int start = abs(sum);
            bool ans = false;
            for(int i = start; i < s.size() - 1; i++) {
                int hh = 0, tt = i - 1;
                bool flag = false;
                while(tt <= s.size() - 1) {
                    int count = 0;
                    for (int j = hh; j <= tt; j++) {
                        count += arr[j];
                    }
                    if(count == sum) {
                        result[round] = i;
                        flag = true;
                        ans = true;
                        break;
                    }
                    hh++;
                    tt++;
                }
                if(flag) break;
            }
            if(!ans) result[round] = -1;
        }
    };
    for(int i = 0; i < n; i++ ) {
        cout << result[i] << endl;
    };
    return 0;
}

