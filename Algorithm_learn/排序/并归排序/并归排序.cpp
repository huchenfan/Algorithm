#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

void merge(int arr[], int l, int mid, int r) {
    int i = l;
    int j = mid +1;
    int k = 0;
    int* tmp = new int[r-l+1];  // 防止大数据时报错
    while(i <= mid && j <= r) {
        tmp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    }
    while(i <= mid) {
        tmp[k++] = arr[i++];
    }
    while(j <= r) {
        tmp[k++] = arr[j++];
    }

    for(int t = l, s = 0; t <= r; t++, s++) {
        arr[t] = tmp[s];
    }
    delete tmp;
    tmp = nullptr;
}

void mergeSort(int arr[], int l, int r) {
    if(l >= r) return;
    int mid = (l + r ) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid+1, r);
    merge(arr, l, mid, r);
}

void mergeSort(int arr[], int size) {
    mergeSort(arr, 0, size - 1);
}


int main() {
    srand(time(nullptr));
    int arr[10];
    for (int &i: arr) {
        i = rand() % 100 + 1;
        cout << i << " ";
    }
    cout << endl;
    mergeSort(arr, 10);
    for (int i: arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}


