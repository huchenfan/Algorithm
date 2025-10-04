#include<iostream>

using namespace std;

class Array{
public:
    Array(int size = 10, int num = 0): mCur(0), mCup(size) {
        mpArr = new int[size]();
        if(size != 10) {
            mCur = size;
            for(int i = 0; i < mCur; i++) {
                mpArr[i] = num;
            }
        }
    }

    ~Array() {
        delete []mpArr;
        mpArr = nullptr;
    }

    // 末尾加入元素：
    void push_back(int val) {
        if(mCup == mCur) expand();
        mpArr[mCur++] = val;
    }

    // 末尾删除元素
    void pop_back() {
        mCur--;
    }
     // 按索引插入元素
     void insert(int pos, int val) {
        if(pos < 0 || pos > mCur) {
            cout << "pos is out of the array" << endl;
            return;
        }
        if(mCup == mCur) expand();
        for(int i = mCur - 1; i >= pos; i--) {
            mpArr[i+1] = mpArr[i];
        }
        mpArr[pos] = val;
        mCur++;
    }

    // 按索引删除元素
    void erase(int pos) {
        if(pos <0 || pos > mCur) {
            cout << "pos is out of the array" << endl;
            return;
        }
        for(int i = pos; i <= mCur-1; i++) {
            mpArr[i] = mpArr[i+1];
        }
        mCur--;
    }

    // 查找元素
    int find(int val) {
        for(int i = 0; i < mCur; i++) {
            if(mpArr[i] == val) return i;
        }
        return -1;
    }

    // operator重载
    int& operator[](int idx){
        if(idx < 0 || idx > mCur) {
            throw std::out_of_range("Array::operator[] index out of range");
        }
        return mpArr[idx];
    }

    // 打印
    void show() const {
        for(int i = 0; i < mCur; i++) {
            cout << mpArr[i] << " ";
        }
        cout << endl;
    }
private:
    void expand() {
        int* p = new int[2*mCup]();
        memcpy(p, mpArr, sizeof(int) * mCup);
        delete []mpArr;
        mpArr = p;
        mCup *= 2;
        p = nullptr;
    }
private:
    int* mpArr;
    int mCur;
    int mCup;
};

int main() {
    Array array(11);
    for(int i = 0; i <10; i++) {
        array[i] = i;
    }
    array.show();
    array[2] = 100;
    array.show();
    array.pop_back();
    array.insert(0, 100);
    array.show();
}

