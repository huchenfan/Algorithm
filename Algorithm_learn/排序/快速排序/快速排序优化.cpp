#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

void insertSort(int arr[], int l, int r) {
    for(int i = l + 1; i < r; i++) {
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
    if((r-l) <= 16) {
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


int main() {
    const int COUNT = 1000000;
    int* arr = new int[COUNT];
    srand(time(nullptr));
    for(int i = 0; i < COUNT; i++) {
        arr[i] =   rand() % COUNT;
    }

    clock_t begin, end;
    begin = clock();
    quickSort(arr, COUNT);
    end = clock();
    cout << "quickSort speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;
    delete []arr;
    return 0;
}
