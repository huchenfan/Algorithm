#include<iostream>

using namespace std;

class SkipList {
public:
    SkipList ()
    {
        head_ = new HeadNode(1);
    }

    ~SkipList()
    {
        deleteNode(head_);
    }
    // 插入接口
    void insert(int data)
    {
        if(find(data)) {
            return;
        }

        int level = getLevel();
        if(level > head_->level_) {
            level = head_->level_ + 1;
            auto* topHeadNode = new HeadNode(level);
            topHeadNode->down_ = head_;
            head_ = topHeadNode;
        }

        Node** nodeList = new Node*[level];
        for(int i = level -1; i >= 0; i--) {
            nodeList[i] = new Node(data);
            if(i < level -1) {
                nodeList[i]->down_ = nodeList[i+1];
            }
        }

        Node* head = head_;
        for(int i = head_->level_; i > level; i--) {
            head = head->down_;
        }
        Node* pre = head;
        Node* cur = pre->next_;
        for(int i = 0; i < level; i++) {
            while (cur != nullptr) {
                if (cur->data_ < data) {
                    pre = cur;
                    cur = cur->next_;
                }
                else {
                    break;
                }
            }
            nodeList[i]->next_ = cur;
            pre->next_ = nodeList[i];
            // 为下一层插入
            pre = pre->down_;
            cur = pre == nullptr ? nullptr : pre->next_;
        }
        delete []nodeList;
    }
    // 删除接口
    void remove(int data)
    {
        Node* pre = head_;
        Node* cur = pre->next_;
        while(true) {
            if(cur != nullptr) {
                if (cur->data_ < data) {
                    pre = cur;
                    cur = cur->next_;
                    continue;
                } else if (cur->data_ == data) {
                    pre->next_ = cur->next_;
                    delete cur;
                }
            }

            if(pre->down_ == nullptr) {
                return;
            }
            if(head_->next_ == nullptr) {   // 若只有一个元素的链表的唯一元素被删去，则这层链表也没有存在的必要了
                auto* tmp = static_cast<HeadNode*>(head_->down_);
                delete head_;
                head_ = tmp;
            }
            pre = pre->down_;
            cur = pre->next_;
        }

    }
    // 查询接口
    bool find(int data)
    {
        Node* pre = head_;
        Node* cur = head_->next_;
        while(true) {
            if(cur != nullptr) {
                if(cur->data_ < data) {
                    pre = cur;
                    cur = cur->next_;
                    continue;
                }
                else if(cur->data_ == data) {
                    return true;
                }
            }

            if(pre->down_ == nullptr) {
                // 最后一层也没找到，说明元素不存在
                return false;
            }
            pre = pre->down_;
            cur = pre->next_;
        }
    }
    // 打印测试
    void show()
    {
        HeadNode* head = head_;
        while(head != nullptr) {
            Node* cur = head->next_;
            while(cur != nullptr) {
                cout << cur->data_ << " ";
                cur = cur->next_;
            }
            cout << endl;
            head = static_cast<HeadNode*>(head->down_);
        }
    }
private:
    struct Node {
        explicit Node(int data = 0)
            : data_(data)
            , next_(nullptr)
            , down_(nullptr)
        {}
        int data_;
        Node* next_;
        Node* down_;
    };

    struct HeadNode : public Node {
        explicit HeadNode(int level)
            : level_(level)
        {}
        int level_;
    };
private:
    void deleteNode (Node* node)
    {
        if(node == nullptr) {
            return;
        }
        deleteNode(node->down_);

        Node* cur = node->next_;
        while(cur != nullptr) {
            Node* tmp = cur->next_;
            delete cur;
            cur = tmp;
        }
        delete node;
    }

    static int getLevel()
    {
        int level = 1;
        while(rand() % 2 == 1) {
            level++;
        }
        return level;
    }
private:
    HeadNode* head_;
};

int main() {
    SkipList skipList;
    for(int i  = 1; i <= 49; i++) {
        skipList.insert(i);
    }
    skipList.show();
    cout << skipList.find(9) << endl;
    skipList.remove(11);
    cout << skipList.find(11) << endl;

    return 0;
}