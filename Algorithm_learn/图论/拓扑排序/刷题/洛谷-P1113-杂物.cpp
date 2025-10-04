#include<bits/stdc++.h>

using namespace std;

const int N = 1005;
vector<vector<int>> grid(N);
int indgree[N];
int expense[N];
int fi[N] = {0};

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 1; i <= n; i++ ) {
        cin >> i;
        cin >> expense[i];
        int dot;
        cin >> dot;
        while(dot != 0) {
            grid[dot].push_back(i);
            indgree[i]++;
            cin >> dot;
        }
    }

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(indgree[i] == 0) {
            q.push(i);
            fi[i] = expense[i];
        }
    }
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for(int i : grid[cur]) {
            indgree[i]--;
            fi[i] = max(fi[i], fi[cur] + expense[i]);  // 这里相当于 在所有已完成的【前驱】中选取 最长的；
            if(indgree[i] == 0) {
                q.push(i);
            }
        }
    }
    int max_ = 0;
    for(int i = 1; i <= n; i++ ) {
        max_ = max(max_, fi[i]);
    }
    cout << max_ << endl;
    return 0;
}

/*

 主要思路：
    拓扑排序 + 最长路-->
        理解题目意思 -->  每个任务 只能在前驱任务全部结束后开始
                        因此它的 开始时间 = 所有前驱任务的完成时间的最大值
                        完成时间 = 开始时间 + 自身耗时
                        最后输出所有任务中最大耗时 --> 不一定是最后一个任务

*/