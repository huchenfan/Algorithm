#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;


void bubbleSort(int arr[], int size) {
    for(int j = 1; j < size; j++) {
        bool flag = false;
        for (int i = 0; i < size - j; i++) {
            if (arr[i] > arr[i + 1]) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                flag = true;
            }
        }
        if(!flag) return;  // 说明这一趟冒泡中并没有进行交换， 即已经排好序了
    }
}


int main() {
    srand(time(nullptr));
    int arr[10];
    for (int & i : arr) {
        i = rand() % 100 + 1;
        cout << i << " ";
    }
    cout << endl;
    bubbleSort(arr, 10);
    for(int i : arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

