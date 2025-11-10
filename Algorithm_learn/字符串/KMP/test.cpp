#include<iostream>
#include<string>

using namespace std;

int *getNext(string& str) {
    int* next = new int[str.size()];
    int j = 0;
    int k = -1;
    next[j] = k;
    int size = str.size();
    while(j < size-1) {
        if(k == -1 || str[j] == str[k]) {
            j++; k++;

            if(str[j] == str[k]) {    // 算法优化
                next[j] = next[k];
            }
            else {
                next[j] = k;
            }
        }
        else {
            k = next[k];
        }
    }

    return next;
}

int KMP(const string& s, string& t) {
    int i = 0;
    int j = 0;
    int* next = getNext(t);

    int size1 = s.size(); int size2 = t.size();     // 为什么要这样写？ 如果不用这个直接用 j 与 t.size() 比较，会有隐藏Bug, t.size() 是无符号类型，而 j 可能是 -1， 会进行隐式转换成无符号比较
    while(i < size1 && j < size2) {
        if(j == -1 || s[i] == t[j]) {
            i++; j++;
        }
        else {
            j = next[j];
        }
    }

    delete []next;

    if(j == size2) {
        return i - j;
    }
    return -1;
}

int main() {
    string s = "ABDCCCDABEFDSG";
    string t = "CCD";
    int pos = KMP(s, t);
    cout << pos << endl;
    return 0;
}






