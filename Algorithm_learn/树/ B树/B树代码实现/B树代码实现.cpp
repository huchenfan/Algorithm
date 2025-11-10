#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

template<int T>
class BTree {
    static_assert(T >= 2, "B-Tree minimum degree must be at least 2");

private:
    struct Node {
        int keys[2*T - 1];
        Node* children[2*T];
        int n;          // 当前key数量
        bool leaf;      // 是否为叶子

        Node(bool _leaf = false) : n(0), leaf(_leaf) {
            memset(keys, 0, sizeof(keys));
            memset(children, 0, sizeof(children));
        }
    };

    Node* root;

    // 分裂子节点：在"进入"子节点前调用，确保父节点有空间
    void splitChild(Node* parent, int idx) {
        Node* full = parent->children[idx];
        Node* newNode = new Node(full->leaf);

        // 1. 把右半部分搬到新节点
        newNode->n = T - 1;
        for (int j = 0; j < T-1; j++)
            newNode->keys[j] = full->keys[j + T];

        // 2. 子节点指针搬迁（如果是内部节点）
        if (!full->leaf) {
            for (int j = 0; j < T; j++)
                newNode->children[j] = full->children[j + T];
        }

        // 3. 在父节点腾位置
        for (int j = parent->n; j > idx; j--)
            parent->children[j+1] = parent->children[j];
        parent->children[idx+1] = newNode;

        // 4. key上浮
        for (int j = parent->n - 1; j >= idx; j--)
            parent->keys[j+1] = parent->keys[j];
        parent->keys[idx] = full->keys[T-1];
        parent->n++;

        // 5. 原节点瘦身
        full->n = T - 1;
        // 清理被移动的key（可选，但有助于调试）
        full->keys[T-1] = 0;
    }

    // 插入到非满节点
    void insertNonFull(Node* node, int key) {
        int i = node->n - 1;

        if (node->leaf) {
            // 叶子：直接插入
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i+1] = node->keys[i];
                i--;
            }
            node->keys[i+1] = key;
            node->n++;
        } else {
            // 内部节点：找子节点
            while (i >= 0 && key < node->keys[i]) i--;
            i++;

            // 预判：子节点满了？立即分裂！
            if (node->children[i]->n == 2*T - 1) {
                splitChild(node, i);
                if (key > node->keys[i]) i++;  // 分裂后重新定位
            }

            insertNonFull(node->children[i], key);
        }
    }

    // 获取前驱（用于内部节点删除）
    int getPredecessor(Node* node) {
        while (!node->leaf)
            node = node->children[node->n];
        return node->keys[node->n - 1];
    }

    // 获取后继
    int getSuccessor(Node* node) {
        while (!node->leaf)
            node = node->children[0];
        return node->keys[0];
    }

    // 合并子节点：父节点的keys[idx]下沉，与children[idx]和children[idx+1]合并
    void mergeChildren(Node* parent, int idx) {
        Node* left = parent->children[idx];
        Node* right = parent->children[idx+1];

        // 1. 先搬运右子节点的keys
        for (int j = 0; j < T-1; j++)
            left->keys[T + j] = right->keys[j];

        // 2. 父节点的key下沉（放到中间位置）
        left->keys[T-1] = parent->keys[idx];

        // 3. 子指针搬迁（如果是内部节点）
        if (!left->leaf) {
            for (int j = 0; j < T; j++)
                left->children[T + j] = right->children[j];
        }

        // 4. 左子节点key数变为2T-1
        left->n = 2*T - 1;

        // 5. 父节点删除idx位置的key和右子指针
        for (int j = idx+1; j < parent->n; j++)
            parent->children[j] = parent->children[j+1];
        for (int j = idx; j < parent->n-1; j++)
            parent->keys[j] = parent->keys[j+1];
        parent->n--;

        delete right;
    }

    // 从左兄弟借：左旋操作
    void borrowFromLeft(Node* parent, int idx) {
        Node* child = parent->children[idx];
        Node* leftSibling = parent->children[idx-1];

        // 1. 父节点的分隔key下移
        for (int j = child->n - 1; j >= 0; j--)
            child->keys[j+1] = child->keys[j];
        child->keys[0] = parent->keys[idx-1];

        // 2. 左兄弟的最大key上移到父节点
        parent->keys[idx-1] = leftSibling->keys[leftSibling->n - 1];

        // 3. 子指针搬迁（如果是内部节点）
        if (!child->leaf) {
            // 修复：循环范围应该是 n
            for (int j = child->n; j >= 0; j--)
                child->children[j+1] = child->children[j];
            child->children[0] = leftSibling->children[leftSibling->n];
        }

        child->n++;
        leftSibling->n--;
    }

    // 从右兄弟借：右旋操作
    void borrowFromRight(Node* parent, int idx) {
        Node* child = parent->children[idx];
        Node* rightSibling = parent->children[idx+1];

        // 1. 父节点的分隔key下移
        child->keys[child->n] = parent->keys[idx];

        // 2. 右兄弟的最小key上移到父节点
        parent->keys[idx] = rightSibling->keys[0];

        // 3. 右兄弟的keys左移
        for (int j = 1; j < rightSibling->n; j++)
            rightSibling->keys[j-1] = rightSibling->keys[j];

        // 4. 子指针搬迁（如果是内部节点）
        if (!child->leaf) {
            // 修复：应该用 child->n，不是 child->n + 1
            child->children[child->n] = rightSibling->children[0];
            for (int j = 1; j <= rightSibling->n; j++)
                rightSibling->children[j-1] = rightSibling->children[j];
        }

        child->n++;
        rightSibling->n--;
    }

    // 自顶向下删除
    void removeFromNode(Node* node, int key) {
        int i = 0;
        while (i < node->n && key > node->keys[i]) i++;

        // 情况1 & 2：key在当前节点
        if (i < node->n && key == node->keys[i]) {
            if (node->leaf) {
                // 叶子：直接删
                for (int j = i; j < node->n-1; j++)
                    node->keys[j] = node->keys[j+1];
                node->n--;
            } else {
                // 内部节点：用前驱或后继替换
                if (node->children[i]->n >= T) {
                    int pred = getPredecessor(node->children[i]);
                    node->keys[i] = pred;
                    removeFromNode(node->children[i], pred);
                } else if (node->children[i+1]->n >= T) {
                    int succ = getSuccessor(node->children[i+1]);
                    node->keys[i] = succ;
                    removeFromNode(node->children[i+1], succ);
                } else {
                    // 合并后递归删
                    mergeChildren(node, i);
                    removeFromNode(node->children[i], key);
                }
            }
        } else {
            // 情况3：key在子树
            if (node->leaf) return; // 不存在

            // 确保子节点有冗余（T个key）
            if (node->children[i]->n == T - 1) {
                if (i > 0 && node->children[i-1]->n >= T) {
                    borrowFromLeft(node, i);
                } else if (i < node->n && node->children[i+1]->n >= T) {
                    borrowFromRight(node, i);
                } else {
                    // 合并操作
                    if (i > 0) mergeChildren(node, i-1);
                    else mergeChildren(node, i);

                    // 修复：如果与左兄弟合并，索引需要减1
                    if (i > 0) i--;  // ? 正确：直接判断
                }
            }

            removeFromNode(node->children[i], key);
        }
    }

    // 中序遍历打印
    void traverse(Node* node) {
        if (!node) return;
        for (int i = 0; i < node->n; i++) {
            if (!node->leaf) traverse(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->leaf) traverse(node->children[node->n]);
    }

    // 层次遍历打印（更直观）
    void printLevelOrder() {
        if (!root) {
            cout << "空树\n";
            return;
        }
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        int curLevel = 0;
        while (!q.empty()) {
            auto [node, level] = q.front(); q.pop();
            if (level > curLevel) {
                cout << "\n";
                curLevel = level;
            }
            cout << "[";
            for (int i = 0; i < node->n; i++) {
                cout << node->keys[i];
                if (i < node->n - 1) cout << ",";
            }
            cout << "] ";
            if (!node->leaf) {
                for (int i = 0; i <= node->n; i++)
                    q.push({node->children[i], level + 1});
            }
        }
        cout << "\n";
    }

    // 查找（返回节点及索引）
    pair<Node*, int> searchNode(Node* node, int key) {
        int i = 0;
        while (i < node->n && key > node->keys[i]) i++;
        if (i < node->n && key == node->keys[i]) return {node, i};
        if (node->leaf) return {nullptr, -1};
        return searchNode(node->children[i], key);
    }

    // 析构（后序删除）
    void destroy(Node* node) {
        if (!node) return;
        if (!node->leaf) {
            for (int i = 0; i <= node->n; i++)
                destroy(node->children[i]);
        }
        delete node;
    }

public:
    BTree() : root(nullptr) {}

    ~BTree() {
        destroy(root);
    }

    void insert(int key) {
        // 检查重复（可选，取决于业务需求）
        if (search(key)) {
            // cout << "重复key: " << key << "，忽略插入\n";
            return;
        }

        if (!root) {
            root = new Node(true);
            root->keys[0] = key;
            root->n = 1;
            return;
        }

        // 根满了？树长高
        if (root->n == 2*T - 1) {
            Node* newRoot = new Node(false);
            newRoot->children[0] = root;
            splitChild(newRoot, 0);
            root = newRoot;
        }

        insertNonFull(root, key);
    }

    void remove(int key) {
        if (!root) return;

        removeFromNode(root, key);

        // 根变空？树降低
        if (root->n == 0 && !root->leaf) {
            Node* oldRoot = root;
            root = root->children[0];
            delete oldRoot;
        }
    }

    bool search(int key) {
        if (!root) return false;
        auto [node, idx] = searchNode(root, key);
        return node != nullptr;
    }

    // 打印函数（可选择中序或层次遍历）
    void print() {
        // 使用层次遍历更直观展示树结构
        printLevelOrder();
    }
};

// ---------- 测试 ----------
int main() {
    BTree<2> tree;  // t=2，即2-3-4树

    cout << "=== 插入测试 ===\n";
    vector<int> insertKeys = {10, 20, 5, 6, 12, 30, 7, 17, 3, 40, 50, 60, 70, 80, 90, 100};
    for (int k : insertKeys) {
        cout << "插入 " << k << ":\n";
        tree.insert(k);
        tree.print();
    }

    cout << "\n=== 删除测试 ===\n";
    vector<int> deleteKeys = {10, 20, 5, 50, 30, 40, 100};
    for (int k : deleteKeys) {
        cout << "删除 " << k << ":\n";
        tree.remove(k);
        tree.print();
    }

    cout << "\n=== 查找测试 ===\n";
    cout << "查找 70: " << (tree.search(70) ? "存在" : "不存在") << "\n";
    cout << "查找 20: " << (tree.search(20) ? "存在" : "不存在") << "\n";

    return 0;
}