#include<iostream>
#include<vector>
using namespace std;

struct Node {
    explicit Node(int val = 0)
            : data(val)
            , left_(nullptr)
            , right_(nullptr)
    {}
    int data;
    Node* left_;
    Node* right_;
};

int search(vector<int>& vec, int val) {
    int l = 0, r = vec.size()-1;
    while(true) {
        int mid = (l+r)/2;
        if(val == vec[mid]) return mid;
        if(val > vec[mid]) l = mid + 1;
        if(val < vec[mid]) r = mid - 1;
    }
}

// 这样写就不需要反复创建vector, 且注意，创建的node必须要在堆区创建，否则函数结束就全部清空！！！
Node* build(vector<int>& pre, int pl, int pr, vector<int>& mid, int ml, int mr){
    if(pl > pr) return nullptr;
    int rootVal = pre[pl];
    int k = search(mid, rootVal);        // 在中序里找根
    int leftCnt = k - ml;                // 左子树节点个数
    Node* root = new Node(rootVal);
    root->left_  = build(pre, pl+1, pl+leftCnt, mid, ml, k-1);
    root->right_ = build(pre, pl+leftCnt+1, pr, mid, k+1, mr);
    return root;
}

Node* buildTree(vector<int> pre, vector<int> mid){
    return build(pre, 0, pre.size()-1, mid, 0, mid.size()-1);
}


