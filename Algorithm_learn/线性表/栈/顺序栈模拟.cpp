#include<iostream>

using namespace std;

class SeqStack {
public:
    explicit SeqStack(int size = 10)
        : mTop(0)
        , mCup(size)
    {
        mpStack = new int[mCup];
    }

    ~SeqStack() {
        delete []mpStack;
        mpStack = nullptr;
    }

     int top() const {
        if(mTop == 0) throw "The stack is empty";
        return mpStack[mTop-1];
    }

    int size() const {
        return  mTop;
    }

    bool empty() const {
        return mTop == 0;
    }

    void push(int val) {
        if(mTop == mCup) expand();
        mpStack[mTop++] = val;
    }

    void pop() {
        if(mTop == 0) throw "The stack is empty";
        mTop--;
    }
private:
    void expand() {
        int* p = new int[mCup*2];
        memcpy(p, mpStack, sizeof(int)* mCup);
        mCup *= 2;
        delete []mpStack;
        mpStack = p;
    }
private:
    int mTop;
    int mCup;
    int* mpStack;
};

int main() {
    SeqStack stack;
    for(int i = 0; i < 10; i++) {
        stack.push(i);
    }
    while(!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
    return 0;
}
