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


Node* LCA(Node* node, int val1, int val2) {
    if(node == nullptr) {
        return nullptr;
    }

    if(node->data > val1 && node->data > val2) {
        return LCA(node->left_, val1, val2);
    }
    else if(node->data < val1 && node->data < val2) {
        return LCA(node->right_, val1, val2);
    }
    else {
        return node;
    }
}

int getLCA(Node* root_, int val1, int val2) {

    Node* cur = LCA(root_, val1, val2);
    if(cur == nullptr) {
        throw "no LCA!";
    }
    else {
        return cur->data;
    }
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
    cout << getLCA(&node1, 2, 30) << endl;

    return 0;
}