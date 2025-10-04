#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

void siftDown(int arr[], int i, int size) {
    int val = arr[i];
    while(2 * i + 1 < size) {   // 之前写的是 i < (size-1) / 2, 容易出问题， 能用乘尽量少用除
        int child = 2 * i + 1;
        if(child +1 < size && arr[child+1] > arr[child]) child++;
        if(val < arr[child]) {
            arr[i] = arr[child];
            i = child;
        }
        else break;
    }
    arr[i] = val;
}


void heapSort(int arr[], int size) {
    int n = size - 1;
    for(int i = (n-1)/2; i >= 0; i--) {
        siftDown(arr, i, n);
    }

    for(int i = n; i > 0; i--) {
        int tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        siftDown(arr, 0, i);
    }
}


int main() {
    srand(time(nullptr));
    int arr[10];
    for(int i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;
        cout << arr[i] << " ";
    }
    cout << endl;

    heapSort(arr, 10);

    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}