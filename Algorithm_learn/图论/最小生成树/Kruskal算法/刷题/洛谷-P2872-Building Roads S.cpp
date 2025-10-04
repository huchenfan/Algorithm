#include<bits/stdc++.h>

using namespace std;

const int N = 1005;

int father[N];
int rk[N];

void init() {
    for(int i = 0; i < N; i++) {
        father[i] = i;
        rk[i] = 0;
    }
}

int find(int cur) {
    if(cur == father[cur]) return cur;
    return father[cur] = find(father[cur]);
}

void join(int a, int b) {
    a = find(a);
    b = find(b);
    if(rk[a] <= rk[b]) father[a] = b;
    else father[b] = a;

    if(rk[a] == rk[b] && a != b) rk[b]++;
}

bool same(int a, int b) {
    return find(a) == find(b);
}



int main() {
    return 0;
}

// 这是稠密图， 适合prim算法的朴素版