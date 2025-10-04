#include<bits/stdc++.h>

using namespace std;

const int N = 1005;

vector<vector<int>> grid(N);
int indgree[N] = {0};
int fi[N];
bool visited[N][N];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(visited, false, sizeof(visited));
    cin >> n >> m;
    int count;
    while(m--) {
        vector<bool> flag(n+1, false);
        cin >> count;
        int nums[count];
        for(int i = 0; i < count; i++) {
            cin >> nums[i];
            flag[nums[i]] = true;
        }
        for(int cur : nums) {
            for(int i = nums[0]; i <= nums[count-1]; i++) {
                if(visited[cur][i]) continue;
                if(!flag[i]) {
                    grid[cur].push_back(i);
                    visited[cur][i] = true;
                    indgree[i]++;
                    continue;
                }
            }
        }
    }


    queue<int> q;

    for(int i = 1; i <= n; i++) {
        fi[i] = 1;
        if(indgree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for(int i : grid[cur]) {
            indgree[i]--;
            fi[i] = max(fi[i], fi[cur]+1);
            if(indgree[i] == 0) q.push(i);
        }
    }

    cout << *max_element(fi + 1, fi + n + 1) << '\n';

    return 0;
}

/*
    题解：
        考察 约束图建模 + 拓扑排序 + 最长路
            1. 约束图建模
                因为题目没直接给你图，只给了你“谁必须比谁大”的规则:【只要这趟车停靠了站 s，那么区间里所有未停靠站 t 的级别都必须严格小于 s】
                约束图建模 = 把 【不等式】 翻译成【有向边】
            2. 拓扑排序
                了解题意， 有图有等级 --> 想到拓扑排序
            3. 最长的路
                一、先回答“什么是最长路”
                    在一张 有向无环图（DAG） 里：
                    每条边都有一个“长度”（本题里长度 = 1）
                    从起点到终点，沿着有向边走，把经过的边长加起来
                    最长路就是所有可能路径里，这个“总长度”最大的那条
                二、怎么在拓扑序上操作？
                    加上递推：
                        fi[v] = max(fi[v], fi[u] + 1)
*/
