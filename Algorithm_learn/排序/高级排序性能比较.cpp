#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void insertSort(int arr[], int l, int r) {
    for(int i = l + 1; i < r; i++) {
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

int partSort(int arr[], int l, int r) {
    int mid = (l+r) / 2;
    int val;
    if((arr[l] >= arr[mid] && arr[l] <= arr[r]) || (arr[l] <= arr[mid] && arr[l] >= arr[r])){
        val = arr[l];
    }else if((arr[mid] >= arr[l] && arr[mid] <= arr[r]) || (arr[mid] <= arr[l] && arr[mid] >= arr[r])) {
        val = arr[mid];
        arr[mid] = arr[l];
        arr[l] = val;
    }else {
        val = arr[r];
        arr[r] = arr[l];
        arr[l] = val;
    }
    while(l < r) {
        while(l < r && arr[r] > val) {
            r--;
        }
        if(l<r) {
            arr[l] = arr[r];
            l++;
        }

        while(l < r && arr[l] < val) {
            l++;
        }
        if(l<r) {
            arr[r] = arr[l];
            r--;
        }
    }
    arr[l] = val;
    return l;
}

void quickSort(int arr[], int l, int r) {
    if(l >= r) return;
    if((r-l) <= 15) {
        insertSort(arr, l, r);
        return;
    }
    int pos = partSort(arr, l, r);
    quickSort(arr, l, pos-1);
    quickSort(arr, pos+1, r);
}

void quickSort(int arr[], int size) {
    quickSort(arr, 0, size - 1);
}


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


void merge(int arr[], int l, int mid, int r) {
    int i = l;
    int j = mid +1;
    int k = 0;
    int* tmp = new int[r-l+1];
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
    delete []tmp;
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
    const int COUNT = 1000000;
    int* arr = new int[COUNT];
    int* brr = new int[COUNT];
    int* crr = new int[COUNT];
    srand(time(nullptr));
    for(int i = 0; i < COUNT; i++) {
        int val = rand() % COUNT;
        arr[i] = val;
        brr[i] = val;
        crr[i] = val;
    }
    clock_t begin, end;
    begin = clock();
    quickSort(arr, COUNT);
    end = clock();
    cout << "quickSort speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;

    begin = clock();
    heapSort(brr, COUNT);
    end = clock();
    cout << "heapSort  speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;

    begin = clock();
    mergeSort(crr, COUNT);
    end = clock();
    cout << "mergeSort speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;

    delete []arr;
    delete []brr;
    delete []crr;
    return 0;
}















