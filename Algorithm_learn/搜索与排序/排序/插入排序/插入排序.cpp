#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

// 如果数据趋于有序，则插入排序是所有排序中 效率最高的
void insertSort(int arr[], int size) {
    for(int i = 1; i < size; i++) {
        int val = arr[i];
        int j = i - 1;
        for(; j >= 0; j--) {
            if(val >= arr[j]) {
                break;
            }
            arr[j+1] = arr[j];
        }
        arr[j+1] = val;
    }
}


int main() {
    srand(time(nullptr));
    int arr[10];
    for (int &i: arr) {
        i = rand() % 100 + 1;
        cout << i << " ";
    }
    cout << endl;
    insertSort(arr, 10);
    for (int i: arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
