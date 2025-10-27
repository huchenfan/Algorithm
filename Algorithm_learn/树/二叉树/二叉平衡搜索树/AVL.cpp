#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;

    explicit Node(int val)
            : data(val)
            , height(1)
            , left(nullptr)
            , right(nullptr)
    {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    int getBalanceFactor(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // 查找最小节点（用于后继查找）
    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    // 查找最大节点 （用于前驱查找）
    Node* findMax(Node* node) const {
        while(node && node->right) node = node->right;
        return node;
    }

    // 处理左左情况
    Node* rightRotate(Node* node)
    {
        Node* child = node->left;
        node->left = child->right;
        child->right = node;

        updateHeight(node);
        updateHeight(child);
    }

    // 处理右右情况
    Node* leftRotate(Node* node)
    {
        Node* child = node->right;
        node->right = node->left;
        child->left = node;

        updateHeight(node);
        updateHeight(child);
    }

    // 处理右左情况
    Node* rightLeftRotate(Node* node)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 处理左右情况
    Node* leftRightRotate(Node* node)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 统一平衡操作：检查并执行旋转，同时更新高度
    Node* balance(Node* node)
    {
        if (node == nullptr) return nullptr;

        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        // 左子树过高
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) >= 0) {
                return rightRotate(node); // LL型
            }
            else {
                return leftRightRotate(node); // LR型
            }
        }

        // 右子树过高
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) <= 0) {
                return leftRotate(node); // RR型
            }
            else {
                return rightLeftRotate(node); // RL型
            }
        }

        return node;
    }

    // 递归插入
    Node* insert(Node* node, int val)
    {
        if (!node) return new Node(val);
        if (val == node->data) return node; // 重复值不插入

        if (val < node->data) {
            node->left = insert(node->left, val);
        } else {
            node->right = insert(node->right, val);
        }

        return balance(node);
    }

    // 递归删除
    Node* remove(Node* node, int val)
    {
        if (!node) return nullptr;

        if (val == node->data) {
            // 情况1：叶子节点或只有一个孩子
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            // 情况2：有两个孩子，左子树高用前驱节点，右子树高用后继节点
            Node* succ;
            if(getHeight(node->left) > getHeight(node->right)){
                succ = findMax(node->left);
                node->data = succ->data;
                node->left = remove(node->left, succ->data);
            }
            else{
                succ = findMin(node->right);
                node->data = succ->data;
                node->right = remove(node->right, succ->data);
            }
        }
        else if (val < node->data) {
            node->left = remove(node->left, val);
        }
        else {
            node->right = remove(node->right, val);
        }

        return balance(node);
    }

    // 递归释放内存
    void destroy(Node* node)
    {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree()
    {
        destroy(root);
    }

    // 公开接口
    void insert(int val)
    {
        root = insert(root, val);
    }

    void remove(int val)
    {
        root = remove(root, val);
    }

    // 非递归中序遍历
    void inOrder() const
    {
        stack<Node*> s;
        Node* cur = root;
        cout << "中序遍历: ";
        while (cur || !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top(); s.pop();
            cout << cur->data << " ";
            cur = cur->right;
        }
        cout << "\n";
    }

    // 层序遍历（调试用）
    void levelOrder() const
    {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        cout << "层序遍历: ";
        while (!q.empty()) {
            Node* node = q.front(); q.pop();
            cout << "(" << node->data << "," << node->height << ") ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << "\n";
    }
};

