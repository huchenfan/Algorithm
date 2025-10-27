//#include <iostream>
//#include <queue>
//#include <stack>
//#include <algorithm>
//
//using namespace std;
//
//struct Node {
//    int data;
//    int height;
//    Node* left;
//    Node* right;
//
//    explicit Node(int val)
//        : data(val)
//        , height(1)
//        , left(nullptr)
//        , right(nullptr)
//    {}
//};
//
//
//class AVLTree {
//public:
//    explicit AVLTree()
//            : root(nullptr)
//    {}
//
//    ~AVLTree()
//    {
//        if(root == nullptr) {
//            return;
//        }
//
//        queue<Node*> nodes;
//        nodes.push(root);
//        while(!nodes.empty()) {
//            Node* front = nodes.front();
//            nodes.pop();
//
//            if(front->left != nullptr) {
//                nodes.push(front->left);
//            }
//            if(front->right != nullptr) {
//                nodes.push(front->right);
//            }
//            delete front;
//        }
//
//    }
//
//    // 递归插入
//    void insert(int val)
//    {
//        root = insert(root, val);
//    }
//
//    // 递归删除
//    void remove(int val)
//    {
//        root = remove(root, val);
//    }
//private:
//    int getHeight(Node* node)
//    {
//        return node == nullptr ? 0 : node->height;
//    }
//
//    void updateHeight(Node* node)
//    {
//        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
//    }
//
//    int getBalanceFactor(Node* node)
//    {
//        return getHeight(node->left) - getHeight(node->right);
//    }
//
//private:
//    // 旋转操作
//
//    // 处理LL情况
//    Node* rightRotate(Node* node)
//    {
//        Node* child = node->left;
//        node->left = child->right;
//        child->right = node;
//
//        updateHeight(node);
//        updateHeight(child);
//        return child;
//    }
//
//    // 处理RR情况
//    Node* leftRotate(Node* node)
//    {
//        Node* child = node->right;
//        node->right = child->left;
//        child->left = node;
//
//        updateHeight(node);
//        updateHeight(child);
//        return child;
//    }
//
//    // 处理LR情况
//    Node* leftRightRotate(Node* node)
//    {
//        node->left = leftRotate(node->left);
//        return rightRotate(node);
//    }
//
//    //处理RL情况
//    Node* rightLeftRotate(Node* node)
//    {
//        node->right = rightRotate(node->right);
//        return leftRotate(node);
//    }
//
//private:
//    Node* balance(Node* node)
//    {
//        int factor = getBalanceFactor(node);
//
//        if(factor > 1) {
//            if(getHeight(node->left) > getHeight(node->right)) {
//                return rightRotate(node);
//            }
//            else {
//                return leftRightRotate(node);
//            }
//        }
//        else if (factor < -1) {
//            if(getHeight(node->right) > getHeight(node->left)) {
//                return leftRotate(node);
//            }
//            else {
//                return rightLeftRotate(node);
//            }
//        }
//        else {
//            return node;
//        }
//    }
//
//private:
//    Node* insert(Node* node, int val)
//    {
//        if(node == nullptr) {
//            return new Node(val);
//        }
//
//        if(node->data == val) {
//            return node;
//        }
//        else if(node->data > val) {
//            node->left = insert(node->left, val);
//        }
//        else {
//            node->right = insert(node->right, val);
//        }
//
//        return balance(node);
//    }
//
//    Node* remove(Node* node, int val)
//    {
//        if(node == nullptr) {
//            return nullptr;
//        }
//
//        if(node->data == val) {
//            if(node->left != nullptr && node->right != nullptr) {
//                if(getHeight(node->left) > getHeight(node->right)) {
//                    Node* pre = node->left;
//                    while(pre->right != nullptr) {
//                        pre = pre->right;
//                    }
//                    node->data = pre->data;
//                    node->left = remove(node->left, pre->data);
//                }
//            }
//
//            if(node->left != nullptr) {
//                Node* tmp = node->left;
//                delete node;
//                return tmp;
//            }
//            else if(node->right != nullptr) {
//                Node* tmp = node->right;
//                delete node;
//                return tmp;
//            }
//            else {
//                delete node;
//                return nullptr;
//            }
//        }
//        else if(node->data > val) {
//            node->left = remove(node->left, val);
//        }
//        else {
//            node->right = remove(node->right, val);
//        }
//
//        return balance(node);
//    }
//private:
//    Node* root;
//};


