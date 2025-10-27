#include<iostream>

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

void solve(Node* node) {
    if(node == nullptr) {
        return;
    }

    Node* tmp = node->left_;
    node->left_ = node->right_;
    node->right_ = tmp;

    solve(node->left_);
    solve(node->right_);
}

void mirror(Node* root) {
    solve(root);
}