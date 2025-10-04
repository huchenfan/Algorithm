#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int partSort(int arr[], int l, int r) {
    int val = arr[l];
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
    int pos = partSort(arr, l, r);
    quickSort(arr, l, pos-1);
    quickSort(arr, pos+1, r);
}

void quickSort(int arr[], int size) {
    quickSort(arr, 0, size - 1);
}

int main() {
    srand(time(nullptr));
    int arr[10];
    for (int &i: arr) {
        i = rand() % 100 + 1;
        cout << i << " ";
    }
    cout << endl;
    quickSort(arr, 10);
    for (int i: arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
