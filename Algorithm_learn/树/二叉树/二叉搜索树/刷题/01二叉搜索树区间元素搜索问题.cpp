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


void findValues_(Node* node, int l, int r) {
    if(node == nullptr) {
        return;
    }

    if(node->data > l) {   // 合理剪枝
        findValues_(node->left_, l, r);
    }

    if(node->data >= l && node->data <= r) {   // 过滤正确答案
        cout << node->data << " ";
    }

    if(node->data < r) {   // 合理剪枝
        findValues_(node->right_, l ,r);
    }
}

void findValues(Node* root, int l, int r) {
    cout << "L ~ R: ";
    findValues_(root, l ,r);
    cout << endl;
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
    findValues(&node1, 2, 14);

    return 0;
}

