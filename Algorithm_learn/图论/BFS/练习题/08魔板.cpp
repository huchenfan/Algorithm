//# include<bits/stdc++.h>
//
//using namespace std;
//
//string moveA(string str) {
//    reverse(str.begin(), str.end());
//    return str;
//}
//
//string moveB(string str) {
//    str = " " + str + " ";
//    swap(str[0], str[4]);
//    swap(str[9], str[5]);
//    string ans;
//    for (int i = 0; i < 10; i++) {
//        if (str[i] != ' ') {
//            ans += str[i];
//        }
//    }
//    return ans;
//}
//
//string moveB_(string str) {
//    str = " " + str + " ";
//    swap(str[0], str[4]);
//    swap(str[9], str[5]);
//    swap(str[0], str[2]);
//    swap(str[1], str[3]);
//    swap(str[9], str[5]);
//    swap(str[8], str[4]);
//    string ans;
//    for (int i = 0; i < 10; i++) {
//        if (str[i] != ' ') {
//            ans += str[i];
//        }
//    }
//    return ans;
//}
//
//string moveC(string str) {
//    swap(str[1], str[2]);
//    swap(str[5], str[6]);
//    swap(str[1], str[5]);
//    return str;
//}
//
//string moveC_(string str) {
//    swap(str[1], str[2]);
//    swap(str[5], str[6]);
//    swap(str[2], str[6]);
//    return str;
//}
//
//
//int main() {
//    string end;
//    cin >> end;
//    string start = "12345678";
//    if (start == end) {
//        cout << 0 << endl;
//        cout << endl;
//        return 0;
//    }
//    unordered_map<string, int> dist;
//    unordered_map<string, int> vis;
//    unordered_map<string, string> step;
//    dist[end] = 0;
//    dist[start] = 0;
//    vis[end] = 2;
//    vis[start] = 1;
//    step[end] = "";
//    step[start] = "";
//    queue<string> pq;
//    pq.push(start);
//    pq.push(end);
//    while (!pq.empty()) {
//        string cur = pq.front();
//        pq.pop();
//        string move[3];
//        if (vis[cur] == 1) {
//            move[0] = moveA(cur);
//            move[1] = moveB(cur);
//            move[2] = moveC(cur);
//            char s[3] = {'A', 'B', 'C'};
//            for (int i = 0; i < 3; i++) {
//                if (!dist.count(move[i])) {
//                    dist[move[i]] = dist[cur] + 1;
//                    vis[move[i]] = vis[cur];
//                    step[move[i]] = step[cur] + s[i];
//                    pq.push(move[i]);
//                } else {
//                    if (vis[cur] != vis[move[i]]) {
//                        cout << dist[cur] + dist[move[i]] + 1 << endl;
//                        cout << step[cur] + s[i] + step[move[i]] << endl;
//                        return 0;
//                    }
//                }
//
//            }
//        } else {
//            move[0] = moveA(cur);
//            move[1] = moveB_(cur);
//            move[2] = moveC_(cur);
//            char s[3] = {'A', 'B', 'C'};
//            for (int i = 0; i < 3; i++) {
//                if (!dist.count(move[i])) {
//                    dist[move[i]] = dist[cur] + 1;
//                    vis[move[i]] = vis[cur];
//                    step[move[i]] = s[i] + step[cur];
//                    pq.push(move[i]);
//                } else {
//                    if (vis[cur] != vis[move[i]]) {
//                        cout << dist[cur] + dist[move[i]] + 1 << endl;
//                        cout << step[move[i]] + s[i] + step[cur] << endl;
//                        return 0;
//                    }
//                }
//            }
//        }
//    }
//    cout << -1 << endl;
//    return 0;
//}


/*=================================================康托压缩优化版=======================================================*/


# include<bits/stdc++.h>

using namespace std;


const int F8[8] = {1, 1, 2, 6, 24, 120, 720, 5040};

int cantor(const string &s) {
    int code = 0;
    for(int i = 0; i < 8; i++) {
        int cnt = 0;
        for(int j = i+1; j < 8; j++) {
            if(s[i] > s[j]) ++cnt;
        }
        code += cnt * F8[8 - i - 1];
    }
    return code;
}

string inv_cantor(int code) {
    string s(8, ' ');
    vector<char> used(8, 0);
    for(int i = 0; i < 8; i++) {
        int rk = code/ F8[7 - i];
        code %= F8[7-i];
        int pos = 0;
        for(int j = 0; j < 8; j++) {
            if(!used[j]) {
                if(pos==rk) {
                    s[i] = '1' + j;
                    used[j] = 1;
                    break;
                }
                pos++;
            }
        }
    }
    return s;
}


string moveA(string str) {
    reverse(str.begin(), str.end());
    return str;
}

string moveB(string str) {
    str = " " + str + " ";
    swap(str[0], str[4]);
    swap(str[9], str[5]);
    string ans;
    for (int i = 0; i < 10; i++) {
        if (str[i] != ' ') {
            ans += str[i];
        }
    }
    return ans;
}

string moveB_(string str) {
    str = " " + str + " ";
    swap(str[0], str[4]);
    swap(str[9], str[5]);
    swap(str[0], str[2]);
    swap(str[1], str[3]);
    swap(str[9], str[5]);
    swap(str[8], str[4]);
    string ans;
    for (int i = 0; i < 10; i++) {
        if (str[i] != ' ') {
            ans += str[i];
        }
    }
    return ans;
}

string moveC(string str) {
    swap(str[1], str[2]);
    swap(str[5], str[6]);
    swap(str[1], str[5]);
    return str;
}

string moveC_(string str) {
    swap(str[1], str[2]);
    swap(str[5], str[6]);
    swap(str[2], str[6]);
    return str;
}


int main() {
    string end;
    cin >> end;
    string start = "12345678";
    if (start == end) {
        cout << 0 << endl;
        cout << endl;
        return 0;
    }


    int dist[40320];
    memset(dist, -1, sizeof(dist));
    int vis[40320];
    memset(vis, 0, sizeof(vis));
    string step[40320];
    int code_start = cantor(start);
    int code_end = cantor(end);
    dist[code_start] = 0; dist[code_end] = 0;
    vis[code_start] = 1; vis[code_end] = 2;
    step[code_start] = ""; step[code_end] = "";
    queue<int> pq;
    pq.push(code_start);
    pq.push(code_end);
    while (!pq.empty()) {
        string cur = inv_cantor(pq.front());
        pq.pop();
        string move[3];
        int code_cur = cantor(cur);
        if (vis[code_cur] == 1) {
            move[0] = moveA(cur);
            move[1] = moveB(cur);
            move[2] = moveC(cur);
            char s[3] = {'A', 'B', 'C'};
            for (int i = 0; i < 3; i++) {
                int code_move = cantor(move[i]);
                if (dist[code_move] == -1) {
                    dist[code_move] = dist[code_cur] + 1;
                    vis[code_move] = 1;
                    step[code_move] = step[code_cur] + s[i];
                    pq.push(code_move);
                } else {
                    if (vis[code_cur] + vis[code_move] == 3) {
                        cout << dist[code_cur] + dist[code_move] + 1 << endl;
                        cout << step[code_cur] + s[i] + step[code_move] << endl;
                        return 0;
                    }
                }

            }
        } else if (vis[code_cur] == 2) {
            move[0] = moveA(cur);
            move[1] = moveB_(cur);
            move[2] = moveC_(cur);
            char s[3] = {'A', 'B', 'C'};
            for (int i = 0; i < 3; i++) {
                int code_move = cantor(move[i]);
                if (dist[code_move] == -1) {
                    dist[code_move] = dist[code_cur] + 1;
                    vis[code_move] = 2;
                    step[code_move] = s[i] + step[code_cur];
                    pq.push(code_move);
                } else {
                    if (vis[code_cur] + vis[code_move] == 3) {
                        cout << dist[code_cur] + dist[code_move] + 1 << endl;
                        cout << step[code_move] + s[i] + step[code_cur] << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << -1 << endl;
    return 0;
}