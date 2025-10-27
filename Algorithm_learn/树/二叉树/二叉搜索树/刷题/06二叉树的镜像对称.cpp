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

bool isMirror(Node* node1, Node* node2) {
    if(node1 == nullptr && node2 == nullptr) {
        return true;
    }
    if(node1 == nullptr || node2 == nullptr) {
        return false;
    }
    if(node1->data != node2->data) {
        return false;
    }

    return isMirror(node1->left_, node2->right_) && isMirror(node1->right_, node2->left_);
}

bool isMirror(Node* root) {
    if(root == nullptr) {
        return true;
    }

    return isMirror(root->left_, root->right_);
}


int main() {
    Node node1(10);
    Node node2(20);
    Node node3(20);
    Node node4(15);
    Node node5(30);
    Node node6(15);
    Node node7(30);
    node1.left_ = &node2;
    node1.right_ = &node3;
    node3.left_ = &node4;
    node3.right_ = &node5;
    node2.left_ = &node7;
    node2.right_ = &node6;
    cout << isMirror(&node1) << endl;

    return 0;
}