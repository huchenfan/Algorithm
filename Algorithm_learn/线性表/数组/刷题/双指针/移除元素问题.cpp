#include<bits/stdc++.h>

using namespace std;

int solve(int arr[], int n, int val) {
    int* h = arr;
    int* t  = arr + n - 1;
    while(h <= t) {
        if(*h != val) h++;
        else{
            if(*t != val) iter_swap(h++, t--);
            else t--;
        }
    }
    return h - arr;
}

int main() {
    int arr[] = {0, 1, 2, 2, 3, 0, 4, 2};
    int len = solve(arr,8, 2);
    for(int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}


/*
 * 题目描述：
 *      输入一个数组， 同时输入一个val,
 *          输出不含val的数组， 只要元素正确即可， 不考虑元素顺序
 * 题解：
 *      一样是 双指针， 将val换到数组右边， 只打印左边不含val的即可
 * */