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

void _midOrder(Node *node, int k, int &cnt, bool &found) {
    if (node == nullptr || found) {
        return;
    }

    _midOrder(node->right_, k, cnt, found);
    if (found) {
        return;
    }
    if (++cnt == k) {
        cout << node->data << endl;
        found = true;
        return;
    }

    _midOrder(node->left_, k, cnt, found);
}

void _midOrder(Node* root, int k) {
    if(root == nullptr) {
        return;
    }
    int cnt = 0;
    bool found = false;
    _midOrder(root, k, cnt, found);
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
    _midOrder(&node1, 1);

    return 0;
}