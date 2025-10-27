#include<iostream>
#include<vector>

using namespace std;

void solve01(vector<int>& arr)
{
    // 根据位图算法的定义来说， 是要事先知道数据的范围的，即 最大值，最小值
    int max_ = arr[0];
    int min_ = arr[0];
    for(int i = 1; i < arr.size(); i++) {
        if(max_ < arr[i]) max_ = arr[i];
        if(min_ > arr[i]) min_ = arr[i];
    }
    int* map = new int[(max_-min_+1)/32+1]();

    for(auto val: arr) {
        int index = (val-min_) / 32;
        int offset = (val-min_) % 32;
        if(map[index] & (1 << offset)) {      //  与运算，判断是否存在
            cout << "the first repeated num:: " << val << endl;
            return;
        }
        else {
            map[index] |= (1 << offset);  // 或运算， 标记位存在
        }
    }
    delete []map;
}

void solve02(vector<int>& arr) {
    // 根据位图算法的定义来说， 是要事先知道数据的范围的，即 最大值，最小值
    int max_ = arr[0];
    int min_ = arr[0];
    for(int i = 1; i < arr.size(); i++) {
        if(max_ < arr[i]) max_ = arr[i];
        if(min_ > arr[i]) min_ = arr[i];
    }
    int* map = new int[(max_-min_+1)/32+1]();

    for(auto val: arr) {
        int index = (val-min_) / 32;
        int offset = (val-min_) % 32;
        if(map[index] & (1 << offset)) {      //  与运算，判断是否存在
            cout << "the first repeated num:: " << val << endl;
        }
        else {
            map[index] |= (1 << offset);  // 或运算， 标记位存在
        }
    }
    delete []map;
}


int main() {
    vector<int> arr{1, 23, 41, 52, 120, 114, 4, 1 ,23};

    // 找到第一个重复的元素
    solve01(arr);
    cout << "================================" << endl;
    // 找到所有重复的元素
    solve02(arr);
    return 0;
}

