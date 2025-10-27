#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

void merge(int arr[], int l, int mid, int r, int* p) {
    int i = l;
    int j = mid +1;
    int k = 0;
    while(i <= mid && j <= r) {
        p[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    }
    while(i <= mid) {
        p[k++] = arr[i++];
    }
    while(j <= r) {
        p[k++] = arr[j++];
    }

    for(int t = l, s = 0; t <= r; t++, s++) {
        arr[t] = p[s];
    }
}

void mergeSort(int arr[], int l, int r, int* p) {
    if(l >= r) return;
    int mid = (l + r ) / 2;
    mergeSort(arr, l, mid, p);
    mergeSort(arr, mid+1, r, p);
    merge(arr, l, mid, r, p);
}

void mergeSort(int arr[], int size) {
    int* p = new int[size];
    mergeSort(arr, 0, size - 1, p);
    delete []p;
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


