#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;

// 给一个数字数组，找到第一个重复的数字
void solve01(vector<int>& arr) {
    unordered_set<int> set;
    for(auto i : arr) {
        auto it = set.find(i);  // 返回相应的迭代器
        if(it != set.end()) {
            cout << "The first ::: " << i << endl;
            return;
        }
        else{
            set.insert(i);
        }
    }
}

// 找到所有重复的数字
void solve02(vector<int>& arr) {
    unordered_set<int> set;
    for(auto i : arr) {
        auto it = set.find(i);
        if(it != set.end()) {
            cout << "The repeated num ::: " << i << endl;
        }
        else{
            set.insert(i);
        }
    }
}

// 统计数字出现的次数
void solve03(vector<int>& arr) {
    unordered_map<int, int> map;
    for(auto i : arr) {
        auto it = map.find(i);
        if(it != map.end()) {
            it->second++;
        }
        else{
            map.insert({i, 1});
        }
    }

    for(auto pair : map) {
        if(pair.second > 1) {
            cout << " key :: " << pair.first << " cnt :: " << pair.second << endl;
        }
    }
}

// 给一个字符串，找到第一个不重复的字符
void solve04(string& str) {
    unordered_map<char, int> map;
    for(auto ch : str) {
        map[ch]++;
    }
    for(auto ch : str) {
        if(map[ch] == 1) {
            cout << "The first char which is the only one::: " << ch << endl;
            return;
        }
    }
    cout << "All of chars are repeated" << endl;
}