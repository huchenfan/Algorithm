
/* ========================================== 未优化字符交换 ============================================================*/

//# include <bits/stdc++.h>
//
//using namespace std;
//
//int dix[] = {0, 1, 0, -1};
//int diy[] = {1, 0, -1, 0};
//
//int main() {
//    string start;
//    string end = "123804765";
//    cin >> start;
//    unordered_map<string, int> grid;
//    grid[start] = 0;
//    queue<string> pq;
//    pq.push(start);
//    int step = -1;
//    while (!pq.empty()) {
//        step++;
//        int sz = pq.size();
//        for (int s = 0; s < sz; s++) {
//            string cur = pq.front();pq.pop();
//            if(cur== end) {
//                cout << step << endl;
//                return  0;
//            }
//            char curGrid[3][3];
//            int x0, y0;
//            for (int i = 0; i < cur.size(); i++) {
//                int n = i / 3;
//                int m = i % 3;
//                curGrid[n][m] = cur[i];
//                if (cur[i] == '0') {
//                    x0 = n;
//                    y0 = m;
//                }
//            }
//            int next_x, next_y;
//            for (int i = 0; i < 4; i++) {
//                string next;
//                next_x = x0 + dix[i];
//                next_y = y0 + diy[i];
//                if (next_x < 0 || next_x >= 3 || next_y < 0 || next_y >= 3) continue;
//                char tmp = curGrid[next_x][next_y];
//                curGrid[x0][y0] = tmp;
//                curGrid[next_x][next_y] = '0';
//                for (auto & j : curGrid) {
//                    for (char t : j) {
//                        next += t;
//                    }
//                }
//                if (grid.count(next)) {
//                    curGrid[x0][y0] = '0';
//                    curGrid[next_x][next_y] = tmp;
//                    continue;
//                }
//                grid[next] = step;
//                pq.push(next);
//
//                curGrid[x0][y0] = '0';
//                curGrid[next_x][next_y] = tmp;
//            }
//        }
//    }
//    cout << -1 << endl;
//    return 0;
//}

/*================================================利用swap交换优化======================================================*/

//# include <bits/stdc++.h>
//
//using namespace std;
//
//int dix[] = {0, 1, 0, -1};
//int diy[] = {1, 0, -1, 0};
//
//int main() {
//    string start;
//    string end = "123804765";
//    cin >> start;
//    unordered_map<string, int> grid;
//    grid[start] = 0;
//    queue<string> pq;
//    pq.push(start);
//    while (!pq.empty()) {
//            string cur = pq.front();pq.pop();
//            if(cur == end) {
//                cout << grid[cur] << endl;
//                return  0;
//            }
//            int index_0 = cur.find('0');  // 找到 "0" 的坐标
//            int x0 = index_0 / 3;
//            int y0 = index_0 % 3;
//            int next_x, next_y;
//            int step = grid[cur];
//            for (int i = 0; i < 4; i++) {
//                next_x = x0 + dix[i];
//                next_y = y0 + diy[i];
//                if (next_x < 0 || next_x >= 3 || next_y < 0 || next_y >= 3) continue;
//                int tmp = next_x * 3 + next_y;
//                swap(cur[index_0], cur[tmp]);  // 交换
//                if (!grid.count(cur)) {
//                    grid[cur] = step + 1;
//                    pq.push(cur);
//                }
//                swap(cur[index_0], cur[tmp]);  // 恢复之前的状态， 进行下一次交换
//            }
//    }
//    cout << -1 << endl;
//    return 0;
//}

/*====================================================================================================================*/


# include <bits/stdc++.h>

using namespace std;

int dix[] = {0, 1, 0, -1};
int diy[] = {1, 0, -1, 0};

int main() {
    string start;
    string end = "123804765";
    cin >> start;
    if(start == end) {
        cout << 0 << endl;
        return 0;
    }
    unordered_map<string, int> grid;
    unordered_map<string, int> vis;
    grid[start] = 0;
    grid[end] = 0;
    queue<string> pq;
    pq.push(start);
    vis[start] = 1;
    pq.push(end);
    vis[end] = 2;
    while (!pq.empty()) {
            string cur = pq.front();pq.pop();
            int index_0 = cur.find('0');  // 找到 "0" 的坐标
            int x0 = index_0 / 3;
            int y0 = index_0 % 3;
            int next_x, next_y;
            int step = grid[cur];
            int flag = vis[cur];
            for (int i = 0; i < 4; i++) {
                next_x = x0 + dix[i];
                next_y = y0 + diy[i];
                if (next_x < 0 || next_x >= 3 || next_y < 0 || next_y >= 3) continue;
                int tmp = next_x * 3 + next_y;
                swap(cur[index_0], cur[tmp]);  // 交换
                if (!grid.count(cur)) {
                    grid[cur] = step + 1;
                    pq.push(cur);
                    if(flag == 1) vis[cur] = 1;
                    if(flag == 2) vis[cur] = 2;
                }else{
                    if(vis[cur] != flag) {
                        cout << step + grid[cur] + 1 << endl;
                        return 0;
                    }
                }
                swap(cur[index_0], cur[tmp]);  // 恢复之前的状态， 进行下一次交换
            }
    }
    cout << -1 << endl;
    return 0;
}
















