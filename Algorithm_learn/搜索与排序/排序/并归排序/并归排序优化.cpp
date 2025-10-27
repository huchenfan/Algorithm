#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

void insertSort(int arr[], int l, int r) {
    for(int i = l + 1; i <= r; i++) {
        int val = arr[i];
        int j = i - 1;
        for(; j >= l; j--) {
            if(val >= arr[j]) {
                break;
            }
            arr[j+1] = arr[j];
        }
        arr[j+1] = val;
    }
}


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
    if(r - l + 1 <= 64) {
        insertSort(arr, l, r);
        return;
    }
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
    const int COUNT = 100000000;
    int* crr = new int[COUNT];
    srand(time(nullptr));
    for(int i = 0; i < COUNT; i++) {
        int val = rand() % COUNT;
        crr[i] = val;
    }
    clock_t begin, end;

    begin = clock();
    mergeSort(crr, COUNT);
    end = clock();
    cout << "mergeSort speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;

    delete []crr;
    return 0;
}
