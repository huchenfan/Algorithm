#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

// 基于 插入排序 优化， 从全局出发 -> 让数据趋于有序
void shellSort(int arr[], int size) {
    for(int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int val = arr[i];
            int j = i - gap;
            for (; j >= 0; j -= gap) {
                if (val >= arr[j]) {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
        }
    }
}


int main() {
    srand(time(nullptr));
    int arr[20];
    for (int &i: arr) {
        i = rand() % 100 + 1;
        cout << i << " ";
    }
    cout << endl;
    shellSort(arr, 20);
    for (int i: arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
