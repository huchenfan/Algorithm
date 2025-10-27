#include<iostream>

using namespace std;


enum State {
    STATE_UNUSED,
    STATE_USING,
    STATE_DEL
};

struct Bucket {
    explicit Bucket (int val = 0)
        : data(val)
        , state(STATE_UNUSED)
    {};
    int data;
    State state;
};


class HashTable {
public:
    explicit HashTable(int size = primList[0], float factor = 0.7)
        : mSize(0)
        , loadFactor(factor)
        , primIndex(0)
    {
        if(size != primList[0]) {
            while(primIndex < primSize - 1) {
                if(size <= primList[primIndex]) break;
                primIndex++;
            }
        }
        size = primList[primIndex];
        mCup = size;
        mp = new Bucket[mCup];
    }

    ~HashTable() {
        delete []mp;
        mp = nullptr;
    }

    // 插入元素
    void insert(int val) {
        if (mSize * 1.0 / mCup > loadFactor) expand();

        int index = (val % mCup + mCup) % mCup;
        while (true) {
            if (mp[index].state != STATE_USING) {
                mp[index].data = val;
                mp[index].state = STATE_USING;
                break;
            }
            index = (index + 1) % mCup;
        }
        mSize++;
    }

    // 删除元素
    void erase(int val) {
        int index = (val % mCup + mCup) % mCup;
        while (true) {
            if (mp[index].state == STATE_USING && mp[index].data == val) {
                mp[index].state = STATE_DEL;
                mSize--;
            }
            if (mp[index].state == STATE_UNUSED) return;
            index = (index + 1) % mCup;
        }
    }

    // 查找元素
    bool find(int val) {
        int index = (val % mCup + mCup) % mCup;
        while (true) {
            if (mp[index].state == STATE_USING && mp[index].data == val) return true;
            if (mp[index].state == STATE_UNUSED) return false;
            index = (index + 1) % mCup;
        }
    }

private:
    void expand() {
        if (primIndex + 1 == primSize) throw "";
        Bucket *p = new Bucket[primList[++primIndex]];
        mCup = primList[primIndex];
        for (int i = 0; i < mSize; i++) {
            if (mp[i].state != STATE_USING) continue;
            int index = (mp[i].data % mCup + mCup) % mCup;
            while (true) {
                if (p[index].state == STATE_UNUSED) {
                    p[index].data = mp[i].data;
                    p[index].state = STATE_USING;
                    break;
                }
                index = (index + 1) % mCup;
            }
        }
        delete[]mp;
        mp = p;
    }

private:
    Bucket *mp;
    int mSize;
    int mCup;
    float loadFactor;
    int primIndex;

    static const int primSize = 10;
    static int primList[primSize];
};

int HashTable::primList[primSize] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};


int main() {
    HashTable hash;
    for(int i = 0; i < 10; i++) {
        hash.insert(i);
    }
    hash.insert(5);
    hash.erase(5);
    cout << hash.find(4) << endl;
}

