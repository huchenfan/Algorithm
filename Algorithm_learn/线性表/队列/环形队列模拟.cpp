#include<iostream>

using namespace std;

class Queue {
public:
    Queue(int size = 10)
        : begin(0)
        , end(0)
        , mCap(0)
        , mCup(size)
    {
        mp = new int[size];
    }

    ~Queue()
    {
        delete []mp;
        mp = nullptr;
    }

    int front() const
    {
        if(begin == end) throw "";
        return  mp[begin];
    }

    int back() const
    {
        if(begin == end) throw "";
        return mp[(end-1 + mCup) % mCup];
    }

    void push(int val)
    {
        if(begin == (end + 1) % mCup) expand();
        mp[end] = val;
        end = (end+1) % mCup;
        mCap++;
    }

    void pop()
    {
        if(begin == end) throw "";
        begin = (begin+1) % mCup;
        mCap--;
    }

    int size() const
    {
        return mCap;
    }

    bool empty()
    {
        return mCap == 0;
    }
private:
    void expand()
    {
        int* p = new int[mCup*2];
        int i = 0;
        int j = begin;
        for(; j != end; i++, j=(j+1)%mCup) {
            p[i] = mp[j];
        }
        delete []mp;
        mp = p;
        begin = 0;
        end = i;
        mCup *= 2;
    }
private:
    int* mp;
    int begin;
    int end;
    int mCup;
    int mCap;
};

int main() {
    Queue queue;
    for(int i = 0; i <= 10; i++) {
        queue.push(i);
    }
    cout << queue.front() << " ";
    cout << queue.back() << " ";
    cout << queue.size() << endl;
    if(queue.empty()) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}

