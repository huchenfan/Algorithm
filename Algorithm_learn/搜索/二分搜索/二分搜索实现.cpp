#include<iostream>

using namespace std;

int bs(int arr[], int size, int val) {
    int l = 0;
    int r = size - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(arr[mid] == val) return mid;
        if (arr[mid] < val) l = mid + 1;
        if (arr[mid] > val) r = mid - 1;
    }
    return  -1;
}

int bs(int arr[], int l, int r, int val) {
    if(l > r)  return -1;
    int mid = l + (r-l)/2;
    if(arr[mid] == val) return mid;
    else if(arr[mid] < val) return bs(arr, mid+1, r, val);
    else return bs(arr, l, mid-1, val);
}

int main() {
    int arr[] = {12,34, 39, 45, 57, 63, 78, 82, 96, 100};
    cout << bs(arr, 10, 100) << endl;
    cout << bs(arr, 0, 9, 34) << endl;
    return 0;
}