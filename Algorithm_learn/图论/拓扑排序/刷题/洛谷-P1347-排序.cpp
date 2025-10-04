#include<bits/stdc++.h>

using namespace std;

const int N = 30;

int inDegree[N];
vector<int> grid[N];
int dotVisited[N] = {0};
bool visited[N][N];
int ans[N] = {0};
int n, m;

int tp(int in[N]) {
    fill(ans, ans+N, 0);
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(in[i] == 0) {
            q.push(i);
        }
    }
    int count = 0;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        ans[++count] = cur;
        for(int i : grid[cur]) {
            in[i]--;
            if(in[i] == 0) {
                q.push(i);
            }
        }
    }
    return count;
}

int exchange(char ch) {
    return int(ch - 'A' + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(visited, false, sizeof(visited));
    fill(inDegree, inDegree+N, -1);
    cin >> n >> m;
    int round = 0;
    fill(ans, ans+N, 0);
    for(int edge = 1; edge <= m; edge++) {
        int num = 0; // 统计已经放入的节点个数
        round++;
        char H, T, R;
        cin >> H >> R >> T;
        int h = exchange(H); int t = exchange(T);
        if(visited[t][h]) continue;
        dotVisited[h] = 1; dotVisited[t] = 1;
        visited[t][h] = true;
        grid[t].push_back(h);
        if(inDegree[h] == -1) inDegree[h] = 0;
        if(inDegree[t] == -1) inDegree[t] = 0;
        inDegree[h]++;
        int in[N];
        for(int i = 1; i <= n; i++) {
            in[i] = inDegree[i]; num += dotVisited[i];
        }
        int flag = tp(in);
        if(flag != num) {
            cout << "Inconsistency found after " << round << " relations." << endl;
            return 0;
        } // 存在环， 即存在矛盾
        if(flag == n) {
            string result, result_;
            int x = n;
            for (int i = 1; i <= n; i++) {
                char ch = char('A' + ans[x--] - 1);
                result += ch;
                result_ += char('A' + i - 1);
            }
            if (result == result_ || round == m) {
                cout << "Sorted sequence determined after " << round << " relations: " << result << "." << endl;
                return 0;
            }
        }
    }
    cout << "Sorted sequence cannot be determined." << endl;
    return 0;
}

/*
 * 题解：
 *      拓扑排序 + 有向图环的判定
 *      基本原理：
 *          拓扑排序本身就具有判断一个图是否为有向无环图的能力
 *      细究题目：
 *          判断成功的条件：
 *              1. 成功排成 字典序 （eg. ABCDEF）
 *              2. 经过所有的大小条件仍不存在矛盾的 非字典序 (eg. ACEGIKMOQSUWYZBDFHJLNPRTVX)
 *          判断失败的条件：
 *              给出的大小条件存在矛盾 --> 构成的图有环
 *          判断不清楚的条件：
 *              在没有成功也没有失败的前提下 --> 构成 不清楚
 *      本题本来就不难， 问题是 题目未将条件讲清楚
*/


