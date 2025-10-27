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

bool same(Node* father, Node* child) {
    if(father == nullptr && child == nullptr) {
        return true;
    }
    if(father == nullptr) {
        return false;
    }
    if(child == nullptr) {
        return true;
    }

    if(father->data != child->data) {
        return false;
    }

    return same(father->left_, child->left_) && same(father->right_, child->right_);
}

bool isChildTree(Node* fatherRoot, Node* childRoot) {
    if(childRoot == nullptr) {
        return true;
    }

    Node* cur = fatherRoot;
    while(cur != nullptr) {
        if(cur->data == childRoot->data) {
            break;
        }
        else if(cur->data > childRoot->data) {
            cur = cur->left_;
        }
        else {
            cur = cur->right_;
        }
    }

    if(cur == nullptr) {
        return false;
    }

    return same(cur, childRoot);
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

    Node node6(100);
    cout << isChildTree(&node1, &node6)<< endl;

    return 0;
}