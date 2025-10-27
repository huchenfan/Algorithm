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

// 如果只在意 左 < 父 < 右，那也只是【局部符合】， 带上中序遍历的思想，保证 【前 < 后】

bool isBSTree(Node* node, Node*& pre) {
    if(node == nullptr) {
        return true;
    }


    if(!isBSTree(node->left_, pre)) {
        return false;
    }

    if(pre != nullptr && node->data < pre->data) {
        return false;
    }
    pre = node;

    return isBSTree(node->right_, pre);
}

bool isBSTree(Node* node) {
    Node* pre = nullptr;
    return isBSTree(node, pre);
}


int main() {
    Node node1(10);
    Node node2(2);
    Node node3(20);
    Node node4(15);
    Node node5(30);
    node1.left_ = &node2;
    node1.right_ = &node3;
    node3.left_ = &node4;
    node3.right_ = &node5;
    cout << isBSTree(&node1) << endl;

    return 0;
}