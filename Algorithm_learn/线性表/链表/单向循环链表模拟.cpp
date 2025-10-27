#include<iostream>

using namespace std;

struct Node {
    int data;
    Node *next;

    explicit Node(int val = 0) : data(val), next(nullptr) {};
};

class Clink {
public:
    explicit Clink() {
        head = new Node();
        tail = head;
        head->next = head;
    }

    ~Clink() {
        Node *tmp = head->next;
        while (tmp != head) {
            head->next = tmp->next;
            delete tmp;
            tmp = head->next;
        }
        delete head;
    }

    // 尾插法
    void insertTail(int val) {
        Node *tmp = new Node(val);
        tail->next = tmp;
        tmp->next = head;
        tail = tmp;
    }

    // 头插法
    void insertHead(int val) {
        Node *tmp = new Node(val);
        tmp->next = head->next;
        head->next = tmp;
        if (head == tail) tail = head->next;
    }

    // 删除元素
    void remove(int val, int cnt = 1) {
        Node *tmp = head;
        while (cnt > 0 && tmp->next != head) {
            if (tmp->next->data == val) {
                cnt--;
                Node *goat = tmp->next;
                tmp->next = tmp->next->next;
                delete goat;
                if (tmp->next == head) tail = tmp;
                continue;
            }
            tmp = tmp->next;
        }
    }

    // 查找元素
    bool find(int val) {
        Node *tmp = head->next;
        while (tmp != head) {
            if (tmp->data == val) return true;
            tmp = tmp->next;
        }
        return false;
    }

    // 打印链表
    void show() {
        Node *tmp = head->next;
        while (tmp != head) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

private:
    Node *head;
    Node *tail;
};


int main() {
    Clink clink;
    for (int i = 1; i <= 9; i++) {
        clink.insertTail(i);
        clink.insertHead(i);
    }
    clink.show();
    clink.remove(1, 3);
    clink.show();
    if(clink.find(1)) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}

