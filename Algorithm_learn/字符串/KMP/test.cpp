#include <bits/stdc++.h>
using namespace std;


vector<int> getNext(string str) {
    vector<int> next(str.size());
    next[0] = 0;
    int j = 0;
    for(int i = 1; i < str.size(); i++) {
        while(j > 0 && str[j] != str[i]) {
            j = next[j-1];
        }
        if(str[j] == str[i]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}


int search(string string1, string string2) {
    if(string2.empty()) return -1;
    vector<int> next = getNext(string2);
    int j = 0;
    for(int i = 0; i < string1.size(); i++) {
        while(j > 0 && string1[i] != string2[j]) {
            j = next[j-1];
        }
        if(string1[i] == string2[j]){
            j++;
        }
        if(j == string2.size()){
            return i - j + 1;
        }
    }
    return -1;
}



int main() {
    string str1 = "aafaabaaacdeeec";
    string str2 = "cdee";
    cout << search(str1, str2)  << endl;
    return 0;
}