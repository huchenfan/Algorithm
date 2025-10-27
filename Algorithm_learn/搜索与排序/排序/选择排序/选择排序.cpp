#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;


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


int main() {
    srand(time(nullptr));
    int arr[10];
    for (int &i: arr) {
        i = rand() % 100 + 1;
        cout << i << " ";
    }
    cout << endl;
    choiceSort(arr, 10);
    for (int i: arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}