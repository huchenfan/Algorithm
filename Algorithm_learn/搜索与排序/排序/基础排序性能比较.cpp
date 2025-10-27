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
        if(!flag) return;
    }
}

void choiceSort(int arr[], int size) {
    for (int j = 0; j < size - 1; j++) {
        int min_ = arr[j];
        int k = j;
        for (int i = j + 1; i < size; i++) {
            if (min_ > arr[i]) {
                min_ = arr[i];
                k = i;
            }
        }
        if (k != j) {
            int tmp = arr[k];
            arr[k] = arr[j];
            arr[j] = tmp;
        }
    }
}

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

void shellSort(int arr[], int size) {
    for(int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int val = arr[i];
            int j = i - gap;
            for (; j >= 0; j -= gap) {
                if (val >= arr[j]) {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
        }
    }
}

int main() {
    const int COUNT = 100000;
    int* arr = new int[COUNT];
    int* brr = new int[COUNT];
    int* crr = new int[COUNT];
    int* drr = new int[COUNT];
    srand(time(nullptr));
    for(int i = 0; i < COUNT; i++) {
        int val = rand() % COUNT;
        arr[i] = val;
        brr[i] = val;
        crr[i] = val;
        drr[i] = val;
    }
     clock_t begin, end;
    begin = clock();
    bubbleSort(arr, COUNT);
    end = clock();
    cout << "bubbleSort speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;

    begin = clock();
    choiceSort(brr, COUNT);
    end = clock();
    cout << "choiceSort speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;

    begin = clock();
    insertSort(crr, COUNT);
    end = clock();
    cout << "insertSort speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;

    begin = clock();
    shellSort(drr, COUNT);
    end = clock();
    cout << "shellSort  speed: " << (end - begin) * 1.0 / CLOCKS_PER_SEC << " s" << endl;
    delete []arr;
    delete []brr;
    delete []crr;
    delete []drr;
    return 0;
}
