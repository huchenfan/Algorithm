#include<iostream>
#include <shared_mutex>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

enum Color {
    RED,
    BLACK
};

struct Node {
    explicit Node(int val = 0, Color color = BLACK, Node* parent = nullptr)
            : data(val)
            , color_(color)
            , left_(nullptr)
            , right_(nullptr)
            , parent_(parent)
    {}

    int data;
    Color color_;
    Node* left_;
    Node* right_;
    Node* parent_;
};

class RBTree {
    shared_mutex rw_mtx_;
public:
    RBTree()
        : root_(nullptr)
    {}

    ~RBTree()
    {
        deleteNode(root_);
    }
    // 红黑树插入操作
    void insert(int val)
    {
        unique_lock<shared_mutex> lock(rw_mtx_);  // 写操作独占
        if(root_ == nullptr) {
            root_ = new Node(val);
            return;
        }

        Node* cur = root_;
        Node* parent = nullptr;

        while(cur != nullptr) {
            if(cur->data == val) {
                return;
            }
            else if(cur->data > val) {
                parent = cur;
                cur = getLeft(cur);
            }
            else {
                parent = cur;
                cur = getRight(cur);
            }
        }

        cur = new Node(val, RED, parent);
        if(parent->data > val) {
            parent->left_ = cur;
        }
        else {
            parent->right_ = cur;
        }

        if(getColor(parent) == RED) {
            fixAfterInsert(cur);
        }
    }
    // 红黑树删除操作
    void remove(int val)
    {
        unique_lock<shared_mutex> lock(rw_mtx_);  // 写操作独占
        if(root_ == nullptr) {
            return;
        }

        Node* cur = root_;
        while(cur != nullptr) {
            if(cur->data == val) {
                break;
            }
            else if(cur->data > val) {
                cur = cur->left_;
            }
            else {
                cur = cur->right_;
            }
        }

        if(cur == nullptr) {
            return;
        }

        if(cur->left_ != nullptr && cur->right_ != nullptr) {
            Node* pre = cur->left_;
            while(pre->right_ != nullptr) {
                pre = pre->right_;
            }
            cur->data = pre->data;
            cur = pre;
        }

        Node* child = cur->left_;
        if(child == nullptr) {
            child = cur->right_;
        }

        if(child != nullptr) {
            child->parent_ = getParent(cur);
            if(getParent(cur) == nullptr) {
                root_ = child;
            }
            else {
                if(getLeft(getParent(cur)) == cur) {
                    getParent(cur)->left_ = child;
                }
                else {
                    getParent(cur)->right_ = child;
                }
            }

            Color color = getColor(cur);
            delete cur;
            if(color == BLACK) {
                fixAfterRemove(child);
            }
        }
        else {
            if(getParent(cur) == nullptr) {
                root_ = nullptr;
            }
            else {
                if(getColor(cur) == BLACK) {
                    fixAfterRemove(cur);
                }
                if (getLeft(getParent(cur)) == cur) {
                    getParent(cur)->left_ = nullptr;
                }
                else {
                    getParent(cur)->right_ = nullptr;
                }
            }
            delete cur;
        }
    }

    // 红黑树查询操作
    bool find(int val) {
        unique_lock<shared_mutex> lock(rw_mtx_);  // 写操作独占
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data == val) return true;
            cur = (val < cur->data) ? cur->left_ : cur->right_;
        }
        return false;
    }
private:
    // 析构递归函数
    void deleteNode(Node* node) {
        if(node == nullptr) {
            return;
        }
        deleteNode(node->left_);
        deleteNode(node->right_);

        delete node;
    }
    // 获得节点颜色
    Color getColor(Node* node)
    {
        return node == nullptr ? BLACK : node->color_;
    }
    // 设置节点颜色
    void setColor(Node* node, Color color)
    {
        if(node != nullptr) {
            node->color_ = color;
        }
    }
    // 获得父节点
    Node* getParent(Node* node)
    {
        return node == nullptr ?  nullptr : node->parent_;
    }
    // 获得左子节点
    Node* getLeft(Node* node)
    {
        return node == nullptr ? nullptr : node->left_;
    }
    // 获得右子节点
    Node* getRight(Node* node)
    {
        return node == nullptr ? nullptr : node->right_;
    }
    // 左旋
    void leftRotate(Node* node) {
        Node* child = getRight(node);
        child->parent_ = getParent(node);
        if(getParent(node) == nullptr) {
            root_ = child;
        }
        else {
            if(getParent(node)->left_ == node) {
                getParent(node)->left_ = child;
            }
            else {
                getParent(node)->right_ = child;
            }
        }
        node->right_ = getLeft(child);
        if(getLeft(child) != nullptr) {
            getLeft(child)->parent_ = node;
        }
        child->left_ = node;
        node->parent_ = child;
    }
    // 右旋
    void rightRotate(Node* node) {
        Node* child = getLeft(node);
        child->parent_ = getParent(node);
        if(getParent(node) == nullptr) {
            root_ = child;
        }
        else {
            if(getParent(node)->left_ == node) {
                getParent(node)->left_ = child;
            }
            else {
                getParent(node)->right_ = child;
            }
        }
        node->left_ = getRight(child);
        if(getRight(child) != nullptr) {
            getRight(child)->parent_ = node;
        }
        child->right_ = node;
        node->parent_ = child;
    }
    // 红黑树插入调整
    void fixAfterInsert(Node* node)
    {
        while(getColor(getParent(node)) == RED) {
            if(getLeft(getParent(getParent(node))) == getParent(node)) {
                Node* uncle = getRight(getParent(getParent(node)));
                if(getColor(uncle) == RED) {
                    setColor(getParent(node), BLACK);
                    setColor(uncle, BLACK);
                    setColor(getParent(getParent(node)), RED);
                    node = getParent(getParent(node));
                }
                else {
                    if(getRight(getParent(node)) == node) {
                        node = getParent(node);
                        leftRotate(node);
                    }
                    setColor(getParent(node), BLACK);
                    setColor(getParent(getParent(node)), RED);
                    rightRotate(getParent(getParent(node)));
                    break;
                }
            }
            else {
                Node* uncle = getLeft(getParent(getParent(node)));
                if(getColor(uncle) == RED) {
                    setColor(getParent(node), BLACK);
                    setColor(uncle, BLACK);
                    setColor(getParent(getParent(node)), RED);
                    node = getParent(getParent(node));
                }
                else {
                    if(getLeft(getParent(node)) == node) {
                        node = getParent(node);
                        rightRotate(node);
                    }

                    setColor(getParent(node), BLACK);
                    setColor(getParent(getParent(node)), RED);
                    leftRotate(getParent(getParent(node)));
                    break;

                }
            }
        }

        setColor(root_, BLACK);
    }
    // 红黑树删除调整
    void fixAfterRemove(Node* node)
    {
        while(node != root_ && getColor(node) == BLACK) {
            if(getLeft(getParent(node)) == node) {
                Node* brother = getRight(getParent(node));
                if(getColor(brother) == RED) {
                    setColor(brother, BLACK);
                    setColor(getParent(node), RED);
                    leftRotate(getParent(node));
                    brother = getRight(getParent(node));
                }

                if(getColor(getLeft(brother)) == BLACK && getColor(getRight(brother)) == BLACK) {
                    setColor(brother, RED);
                    node = getParent(node);
                }
                else {
                    if(getColor(getRight(brother)) != RED) {
                        setColor(brother, RED);
                        setColor(getLeft(brother), BLACK);
                        rightRotate(brother);
                        brother = getRight(getParent(node));
                    }

                    setColor(brother, getColor(getParent(node)));
                    setColor(getParent(node), BLACK);
                    setColor(getRight(brother), RED);
                    break;
                }
            }
            else {
                Node* brother = getLeft(getParent(node));
                if(getColor(brother) == RED) {
                    setColor(brother, BLACK);
                    setColor(getParent(node), RED);
                    rightRotate(getParent(node));
                    brother = getLeft(getParent(node));
                }

                if(getColor(getLeft(brother)) == BLACK && getColor(getRight(brother)) == BLACK) {
                    setColor(brother, RED);
                    node = getParent(node);
                }
                else {
                    if(getColor(getLeft(brother)) != RED) {
                        setColor(brother, RED);
                        setColor(getRight(brother), BLACK);
                        leftRotate(brother);
                        brother = getLeft(getParent(node));
                    }

                    setColor(brother, getColor(getParent(node)));
                    setColor(getParent(node), BLACK);
                    setColor(getLeft(brother), RED);
                    break;
                }
            }
        }
        setColor(node, BLACK);
    }
private:
    Node* root_;
};


// 1. 禁用优化（防止编译器耍赖）
volatile int dummy = 0;  // 强制编译器不能优化

// 2. 计时必须包含join()等待时间
int main() {
    RBTree tree;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> workers;
    for (int i = 0; i < 10; ++i) {
        workers.emplace_back([&tree, i]() {
            for (int j = 0; j < 100000; ++j) {
                tree.insert(i * 100000 + j);
                dummy += j;  // 强制副作用
            }
        });
    }
    for (auto& t : workers) t.join();  // 必须join

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "10线程耗时: " << (end - start).count() / 1e6 << "ms\n";

    // 单线程对比
    RBTree singleTree;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        singleTree.insert(i);
        dummy += i;
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "单线程耗时: " << (end - start).count() / 1e6 << "ms\n";

    return 0;
}
