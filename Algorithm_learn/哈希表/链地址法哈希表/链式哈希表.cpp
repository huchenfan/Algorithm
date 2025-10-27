#include<iostream>
#include<algorithm>
#include <stdexcept>
#include<list>
#include <vector>
using namespace std;

class HashTable {
public:
    explicit HashTable(int size = primList[0], float factor = 0.7)
        : bucketSize(0)
        , mSize(0)
        , primIndex(0)
        , loadFactor(factor)
    {
        if(size != primList[0]) {
            while(primIndex < size -1) {
                if(size <= primList[primIndex]) break;
                primIndex++;
            }
        }
        mCup = primList[primIndex];
        mTable.resize(mCup);
    }

    void insert (int val)
    {
        if(bucketSize*1.0/mCup > loadFactor) expand();

        int index = (val%mCup+mCup)%mCup;
        if(mTable[index].empty()) {
            bucketSize++;
        }
        auto it = ::find(mTable[index].begin(), mTable[index].end(), val);
        if(it != mTable[index].end()) return;
        mTable[index].emplace_back(val);
        mSize++;
    }

    void erase(int val)
    {
        int index = (val%mCup+mCup)%mCup;
        if(!mTable[index].empty()) {
            auto it = ::find(mTable[index].begin(), mTable[index].end(), val);
            if(it != mTable[index].end()) {
                mSize--;
                mTable[index].erase(it);
                if(mTable[index].empty()) bucketSize--;
            }
        }
    }

    bool find(int val) const
    {
        int index = (val%mCup+mCup)%mCup;
        if(!mTable[index].empty()) {
            auto it = ::find(mTable[index].begin(), mTable[index].end(), val);
            if(it != mTable[index].end()) return true;
        }
        return false;
    }

    int size() const
    {
        return mSize;
    }

    bool empty() const
    {
        return mSize == 0;
    }

private:
    void expand()
    {
        if(primIndex+1 == primSize) throw std::runtime_error("HashTable cannot expand further (max prime reached)");
        primIndex++;
        mCup = primList[primIndex];
        vector<list<int>> tmp;
        mTable.swap(tmp);
        mTable.resize(mCup);
        bucketSize = 0;
        for(auto& list : tmp) {
            for(auto val : list) {
                int index = (val%mCup+mCup)%mCup;
                if(mTable[index].empty()) bucketSize++;
                mTable[index].emplace_back(val);
            }
        }
    }
private:
    vector<list<int>> mTable;
    int bucketSize;
    int mSize;
    int mCup;
    int primIndex;
    float loadFactor;

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
    cout << hash.find(8) << endl;
}