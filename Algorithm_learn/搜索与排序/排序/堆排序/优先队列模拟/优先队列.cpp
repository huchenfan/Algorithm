#include<iostream>
#include<functional>
#include<ctime>
#include<cstdlib>
#include <utility>

using namespace std;

class PriorityQueue {
public:
    using Comp = function<bool(int, int)>;
    explicit PriorityQueue(int size = 20, Comp comp_ = greater<int>())
        : mSize(0)
        , mCup(size)
        , comp(std::move(comp_))
    {
        mp = new int[mCup];
    }

    explicit PriorityQueue(Comp comp_)
        : mSize(0)
        , mCup(20)
        , comp(comp_)
    {
        mp = new int[mCup];

    }

    ~PriorityQueue()
    {
        delete []mp;
        mp = nullptr;
    }

    void push(int val)
    {
        if(mSize == mCup) expand();
        if(mSize == 0) {
            mp[mSize++] = val;
            return;
        }
        siftUp(mSize, val);
        mSize++;
    }

    void pop() {
        if(mSize == 0) throw " ";
        mSize--;
        if(mSize > 0) {
            siftDown(mp[mSize]);
        }

    }

    bool empty() const
    {
        return mSize == 0;
    }

    int top() const
    {
        if(mSize == 0) throw " ";
        return mp[0];
    }

    int size() const
    {
        return mSize;
    }

private:
    void expand()
    {
        int* p = new int[mCup*2];
        memcpy(p, mp, sizeof(int)*mCup);
        mCup *= 2;
        delete []mp;
        mp = p;
    }

    void siftUp(int i, int val)
    {
        while(i > 0) {
            int father = (i-1) / 2;
            if(comp(val, mp[father])) {
                mp[i] = mp[father];
                i = father;
            }
            else {
                break;
            }
        }
        mp[i] = val;
    }

    void siftDown(int val)
    {
        int i = 0;
        while(2 * i + 1 < mSize) {
            int child = i * 2 + 1;
            if (child + 1 < mSize && comp(mp[child+1], mp[child])) child++;
            if(comp(mp[child], val)) {
                mp[i] = mp[child];
                i = child;
            }
            else {
                break;
            }
        }
        mp[i] = val;
    }
private:
    int* mp;
    int mSize;
    int mCup;
    Comp comp;
};

int main() {
    srand(time(nullptr));
    PriorityQueue pq([](int a, int b){return a < b;});
    for(int i = 0; i < 10; i++ ) {
        int val = rand() % 100 + 1;
        pq.push(val);
        cout <<  val << " ";
    }
    cout << endl;
    while(!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    return 0;
}