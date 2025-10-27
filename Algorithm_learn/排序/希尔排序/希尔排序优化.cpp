#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <random>

using namespace std;

void shellSort(int arr[], int size) {
    static const int sedgewick[] = {1,5,19,41,109,209,505,929,2161,3905,8929,16001,36289,64769,146305,260609,587521,1045505,2354689,4188161,9427969,16764929,37730305,67004001,150958081,268386305,603906049,1073643521};
    int k = 0;
    while (sedgewick[k] < size / 3) ++k;
    for(; k >= 0; --k) {
        int gap = sedgewick[k];
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
    const int COUNT = 100000000;
    int* arr = new int[COUNT];

    // ② 高速随机数
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, COUNT - 1);
    for (int i = 0; i < COUNT; ++i) arr[i] = dist(rng);
    clock_t begin = clock();
    shellSort(arr, COUNT);
    clock_t end = clock();

    std::cout << "shellSort speed: " << double(end - begin) / CLOCKS_PER_SEC << " s\n";

    delete[] arr;
    return 0;
}
