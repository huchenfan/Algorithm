#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> result;

vector<int> path;

void dfs(vector<vector<int>> &grid, int cur, int end){
    if(cur == end) {
        result.push_back(path);
        return ;
    }
    for(int i = 1; i <= end; i++) {
        if(grid[cur][i] == 1) {
            path.push_back(i);
            dfs(grid, i, end);
            path.pop_back();
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n+1, vector<int>(n+1, 1e9));
    while(m--){
        int s, t;
        cin >> s >> t;
        grid[s][t] = 1;
    }
    int start, end;
    cin  >> start >> end;
    path.push_back(start);
    dfs(grid, start, end);
    for(auto & i : result) {
        for(int j = 0; j < i.size() ; j++) {
            cout << i[j] << " ";
        }
        cout << endl;
    }
    return 0;
}

















