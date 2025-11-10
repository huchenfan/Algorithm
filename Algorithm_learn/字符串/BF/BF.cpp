#include<iostream>
#include<string>

using namespace std;

int BF(string s, string t) {
    int i = 0;  // 主串起始下标
    int j = 0;  // 子串起始下标
    while(i < s.size() && j < t.size()) {
        if(s[i] == t[j]) {
            i++; j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }

    if(j == t.size()) {
        return i - j;
    }
    else {
        return -1;
    }
}

int main() {
    string s = "ABDCCCDABEFDSG";
    string t = "CCD";
    int pos = BF(s, t);
    cout << pos << endl;
    return 0;
}