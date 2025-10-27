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


int isBalance(Node* node, bool& ok) {
    if (!node) return 0;

    int lh = isBalance(node->left_, ok);
    if (!ok) return 0;

    int rh = isBalance(node->right_, ok);
    if (!ok) return 0;

    if (abs(lh - rh) > 1) ok = false;

    return max(lh, rh) + 1;
}

bool isBalance(Node* root) {
    bool ok = true;
    isBalance(root, ok);
    return ok;
}