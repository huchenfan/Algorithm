#include<iostream>

using namespace std;

struct Node{
    explicit Node(int val = 0)
        : data(val)
        , next(nullptr)
        , pre(nullptr)
    {}
    int data;
    Node* next;
    Node* pre;
};

class CircleClink {
public:
    CircleClink() {
        head = new Node();
        head->next = head;
        head->pre = head;
    }

    ~CircleClink() {
        Node* p = head->next;
        while(p!= head) {
            head->next = p->next;
            delete p;
            p = head->next;
        }
        delete head;
    }

    // 尾插法
    void insertTail(int val) {
        Node* p = head;
        while(p->next != head) {
            p = p->next;
        }
        Node* tmp = new Node(val);
        p->next = tmp;
        tmp->pre = p;
        tmp->next = head;
        head->pre = tmp;
    }

    // 头差法
    void insertHead(int val) {
        Node* p = new Node(val);
        Node* tmp = head->next;
        p->next = tmp;
        tmp->pre = p;
        head->next = p;
        p->pre = head;
    }

    // 删除元素
    void remove(int val, int k) {
        Node* p = head;
        while(k && p->next != head) {
            if(p->next->data == val) {
                k--;
                Node* tmp = p->next;
                p->next = tmp->next;
                tmp->pre = p;
                delete tmp;
                continue;
            }
            p = p->next;
        }
    }

    // 查找元素
    bool find(int val) {
        Node* p = head->next;
        while(p != head) {
            if(p->data == val) return true;
            p = p->next;
        }
        return false;
    }

    // 打印链表
    void show() {
        Node* p = head->next;
        while(p != head) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
private:
    Node* head;
};

int main() {
    CircleClink circleClink;
    for(int i = 1; i <= 9; i++) {
        circleClink.insertTail(i);
        circleClink.insertHead(i);
    }
    circleClink.show();
    circleClink.remove(1, 2);
    circleClink.show();
    if(circleClink.find(1)) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}