#include<bits/stdc++.h>

using namespace std;

void r(string& str, int size) {
    int h = 0;
    int t = h + size - 1;
    while(h < t) {
        char tmp = str[h];
        str[h] = str[t];
        str[t] = tmp;
        h++; t--;
    }
}

int main() {
    string str = "hello world";
    r(str, str.size());
    cout << str << endl;
    return 0;
}