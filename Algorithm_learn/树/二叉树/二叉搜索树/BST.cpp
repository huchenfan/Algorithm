#include<iostream>
#include<stack>
#include<queue>

using namespace std;

struct Node {
    explicit Node(int val = 0)
        : data(val)
        , left_(nullptr)
        , right_(nullptr)
    {};

    int data;
    Node* left_;
    Node* right_;
};


class BSTree {
public:
    explicit BSTree()
        : root_(nullptr)
    {}

    ~BSTree()
    {
        if(root_ == nullptr) {
            return;
        }

        queue<Node*> nodes;
        nodes.push(root_);
        while(!nodes.empty()) {
            Node* front = nodes.front();
            nodes.pop();

            if(front->left_ != nullptr) {
                nodes.push(front->left_);
            }
            if(front->right_ != nullptr) {
                nodes.push(front->right_);
            }

            delete front;
        }

        root_ =nullptr;
    }
    // 递归插入
    void insert(int val)
    {
        root_ = insert(root_, val);
    }

    // 递归删除
    void remove(int val)
    {
        root_ = remove(root_, val);
    }

    // 递归查询
    bool find(int val)
    {
        return nullptr != find(root_, val);
    }

    // 递归前序遍历
    void preOrder()
    {
        cout << "preOrder:  ";
        preOrder(root_);
        cout << endl;
    }

    // 递归中序遍历
    void midOrder()
    {
        cout << "midOrder:  ";
        midOrder(root_);
        cout << endl;
    }

    // 递归后序遍历
    void postOrder()
    {
        cout << "postOrder:  ";
        postOrder(root_);
        cout << endl;
    }

    // 递归层序遍历
    void levelOrder()
    {
        cout << "levelOrder:  ";
        if(root_ == nullptr) {
            return;
        }

        int h = high(root_);
        for(int i = 0; i < h; i++) {
            levelOrder(root_, i);
        }
        cout << endl;
    }

    // 非递归插入
    void n_insert(int val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }

        Node *cur = root_;
        Node *parent = nullptr;
        while (cur != nullptr) {
            if (cur->data == val) {
                return;
            } else if (cur->data > val) {
                parent = cur;
                cur = cur->left_;
            } else {
                parent = cur;
                cur = cur->right_;
            }
        }
        if(parent->data > val) {
            parent->left_ = new Node(val);
        }
        else {
            parent->right_ = new Node(val);
        }

    }

    // 非递归删除
    void n_remove(int val)
    {
        if(root_ == nullptr) {
            return;
        }

        Node* cur = root_;
        Node* parent = nullptr;
        while(cur != nullptr) {
            if(cur->data > val) {
                parent = cur;
                cur = cur->left_;
            }
            else if(cur->data < val) {
                parent = cur;
                cur = cur->right_;
            }
            else {
                break;
            }
        }

        if(cur == nullptr) {
            return;
        }

        if(cur->left_ != nullptr && cur->right_ != nullptr) {
            Node* preParent = cur;
            Node* pre = cur->left_;
            while(pre->right_ != nullptr) {
                preParent = pre;
                pre = pre->right_;
            }
            cur->data = pre->data;
            parent = preParent;
            cur = pre;
        }

        Node* child = cur->left_;
        if(child == nullptr) {
            child = cur->right_;
        }

        if(parent == nullptr) {
            root_ = child;
            delete cur;
            return;
        }

        if(parent->left_ == cur) {
            parent->left_ = child;
        }
        if(parent->right_ == cur) {
            parent->right_ = child;
        }
        delete cur;
    }

    // 非递归查询
    bool n_find(int val)
    {
        if (root_ == nullptr) {
            return false;
        }

        Node *cur = root_;
        while (cur != nullptr) {
            if (cur->data == val) {
                return true;
            }
            else if (cur->data > val) {
                cur = cur->left_;
            }
            else {
                cur = cur->right_;
            }
        }
        return false;
    }

    // 非递归前序遍历
    void n_preOrder()
    {
        cout << "n_preOrder:  ";
        if(root_ == nullptr) {
            return;
        }

        stack<Node*> nodes;
        nodes.push(root_);
        while(!nodes.empty()) {
            Node* top = nodes.top();
            nodes.pop();
            cout << top->data << " ";

            if(top->right_ != nullptr) {
                nodes.push(top->right_);
            }

            if(top->left_ != nullptr) {
                nodes.push(top->left_);
            }
        }
        cout << endl;
    }

    // 非递归中序遍历
    void n_midOrder()
    {
        cout << "n_midOrder:  ";
        if(root_ == nullptr) {
            return;
        }

        stack<Node*> nodes;
        Node* cur = root_;

        while(!nodes.empty() || cur != nullptr) {
            if(cur != nullptr) {
                nodes.push(cur);
                cur = cur->left_;
            }
            else {
                Node* top = nodes.top();
                nodes.pop();
                cout << top->data << " ";

                cur = top->right_;
            }
        }
        cout << endl;
    }

    // 非递归后序遍历
    void n_postOrder()
    {
        cout << "n_postOrder:  ";
        if(root_ == nullptr) {
            return;
        }

        stack<Node*> nodes, ans;
        nodes.push(root_);
        while(!nodes.empty()){
            Node* top = nodes.top();
            nodes.pop();

            ans.push(top);
            if(top->left_ != nullptr) {
                nodes.push(top->left_);
            }
            if(top->right_ != nullptr) {
                nodes.push(top->right_);
            }
        }

        while(!ans.empty()) {
            cout << ans.top()->data << " ";
            ans.pop();
        }

        cout << endl;
    }

    // 非递归层序遍历
    void n_levelOrder()
    {
        cout << "n_levelOrder:  ";
        if(root_ == nullptr) {
            return;
        }

        queue<Node*> q;
        q.push(root_);
        while (!q.empty()) {
            Node *cur = q.front();
            q.pop();
            cout << cur->data << " ";
            if (cur->left_ != nullptr) {
                q.push(cur->left_);
            }
            if (cur->right_ != nullptr) {
                q.push(cur->right_);
            }
        }
        cout << endl;
    }
private:
    // 递归插入
    Node* insert(Node* node, int val)
    {
        // 没找到
        if(node == nullptr) {
            return new Node(val);
        }

        // 正在找
        if(node->data == val) {
            return node;
        }
        else if(node->data < val) {
            node->right_ = insert(node->right_, val);
        }
        else{
            node->left_ = insert(node->left_, val);
        }
        return node;
    }

    // 递归删除 返回删除目标节点后的 【root_】节点
    Node* remove(Node* node, int val)
    {
        // 没找到
        if(node == nullptr) {
            return node;
        }

        // 正在找
        if(node->data == val) {
            if (node->left_ != nullptr && node->right_ != nullptr) {
                Node *pre = node->left_;
                while (pre->right_ != nullptr) {
                    pre = pre->right_;
                }
                node->data = pre->data;
                node->left_ = remove(node->left_, pre->data);
            }
            else {
                if (node->left_ != nullptr) {
                    Node *tmp = node->left_;
                    delete node;
                    return tmp;
                }
                else if (node->right_ != nullptr) {
                    Node *tmp = node->right_;
                    delete node;
                    return tmp;
                }
                else {
                    delete node;
                    return nullptr;
                 }
            }
        }
        else if(node->data < val) {
            node->right_ = remove(node->right_, val);
        }
        else {
            node->left_ = remove(node->left_, val);
        }
        return node;
    }

    // 递归查询
    Node* find(Node* node, int val)
    {
        if(node == nullptr) {
            return nullptr;
        }

        if(node->data == val) {
            return node;
        }
        else if(node->data > val) {
            return  find(node->left_, val);
        }
        else {
            return find(node->right_, val);
        }
    }

    // 递归前序遍历
    void preOrder(Node* node)
    {
        if(node == nullptr) {
            return;
        }

        cout << node->data; " ";
        preOrder(node->left_);
        preOrder(node->right_);
    }

    // 递归中序遍历
    void midOrder(Node* node) {
        if(node == nullptr) {
            return;
        }

        midOrder(node->left_);
        cout << node->data << " ";
        midOrder(node->right_);
    }

    // 递归后序遍历
    void postOrder(Node* node)
    {
        if(node == nullptr) {
            return;
        }

        postOrder(node->left_);
        postOrder(node->right_);
        cout << node->data << " ";
    }

    int high(Node* node)
    {
        if(node == nullptr) {
            return 0;
        }
        int left = high(node->left_);
        int right = high(node->right_);
        return left > right ? left + 1 : right + 1;
    }

    int number(Node* node)
    {
        if(node == nullptr) {
            return 0;
        }
        int left = number(node->left_);
        int right = number(node->right_);
        return left + right + 1;
    }

    // 递归层序遍历
    void levelOrder(Node* node, int i)
    {
        if(node == nullptr) {
            return;
        }
        if(i == 0) {
            cout << node->data << " ";
            return;
        }
        levelOrder(node->left_, i-1);
        levelOrder(node->right_, i-1);
    }
private:
    Node* root_;
};


int main() {
    BSTree bsTree;
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    for(int i : arr) {
        bsTree.insert(i);
    }


    bsTree.n_postOrder();
    bsTree.postOrder();

    for(int i : arr) {
        bsTree.remove(i);
    }
    return 0;
}