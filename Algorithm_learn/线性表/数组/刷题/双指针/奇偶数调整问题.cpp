#include<bits/stdc++.h>

using namespace std;

// 模运算
//void change(int arr[], int size) {
//    int* h = arr;
//    int* t = h + size - 1;
//    while(h < t) {
//        if(*h % 2 == 0) {
//            h++;
//        }else{
//            if(*t %2 == 0) {
//                int tmp;
//                tmp = *h;
//                *h = *t;
//                *t = tmp;
//                h++; t--;
//            }else{
//                t--;
//            }
//        }
//    }
//}

// 位运算 + 交换优化
bool even(int x) { return (x & 1) == 0; }

void change(int arr[], int size) {
    int* h = arr;
    int* t = h + size - 1;
    while(h < t) {
        if(even(*h)) h++;
        else{
            if(even(*t)) iter_swap(h++, t--);
            else t--;
        }
    }
}

int main() {
    int arr[] = {99, 63, 76, 6, 74, 8, 1, 90, 51, 38};
    int size = 10;
    change(arr,size);
    for(auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}


/*
 * 题目描述：
 *      输入一个int 数组， 以及数组的大小；
 *      输出一个数组， 使得输入的数组中的偶数在数组左边， 奇数在数组右边
 * 题解：
 *      利用 双指针
 *
 *      复杂度分析：
 *          时间：
 *              O(n)
 *          空间：
 *              O(1) 额外的内存
 * */