#include <bits/stdc++.h>

using namespace std;


int target, res = 0;
vector<int> path;
vector<vector<int>> result;

void dfs(int cur, int sum) {
    if(cur > 10 && sum == target) {
        result.push_back(path);
        res++;
    }
    for(int i = 1; i <=3; i++) {
        if(sum + i + (10 - cur) * 3 < target) continue;   // 为什么是continue?  因为可能加 1 不行， 加2 3 行      【剪枝】
        if(sum + i + (10 - cur) * 1 > target) break;      // 为什么是break? 当前都不行了， 越往后越大              【剪枝】
        path.push_back(i);
        dfs(cur+1, sum + i);  // 没有必要为了一个sum 单独可一个全局变量， 这样即不好理解， 也不好管理（不清楚递归过程中是否会相互影响）
        path.pop_back();  // 恢复现场
    }
}

int main() {
    cin >> target;
    dfs(1, 0);
    cout << res << endl;
    for(const vector<int>& vec : result) {
        for(int i : vec) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}










