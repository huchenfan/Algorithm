#include<iostream>

using namespace std;

struct Node {
    explicit Node(int val = 0)
            : data(val), pre(nullptr), next(nullptr) {}

    int data;
    Node *pre;
    Node *next;
};

class Clink {
public:
    Clink() {
        head = new Node();
    }

    ~Clink() {
        Node *p = head;
        while (p != nullptr) {
            head = head->next;
            delete p;
            p = head;
        }
    }

    // 尾插法：
    void insertTail(int val) {
        Node *p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        Node *q = new Node(val);
        p->next = q;
        q->pre = p;
    }

    // 头插法
    void insertHead(int val) {
        Node *p = new Node(val);
        p->next = head->next;
        head->next = p;
        p->pre = head;
        if (p->next != nullptr) p->next->pre = p;
    }

    // 删除元素
    void remove(int val, int k = 1) {
        Node *p = head;
        while (k && p->next != nullptr) {
            if (p->next->data == val) {
                k--;
                Node *tmp = p->next;
                p->next = tmp->next;
                tmp->next->pre = p;
                delete tmp;
                continue;
            }
            p = p->next;
        }
    }

    // 查找元素
    bool find(int val) {
        Node *p = head->next;
        while (p != nullptr) {
            if (p->data == val) return true;
            p = p->next;
        }
        return false;
    }

    // 打印链表
    void show() {
        Node *p = head->next;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

private:
    Node *head;
};

int main() {
    Clink clink;
    for (int i = 1; i < 10; i++) {
        clink.insertTail(i);
        clink.insertHead(i);
    }
    clink.show();
    clink.remove(1, 2);
    clink.show();
    if(clink.find(1)) cout << "true";
    else cout << "false" << endl;
    return 0;
}


