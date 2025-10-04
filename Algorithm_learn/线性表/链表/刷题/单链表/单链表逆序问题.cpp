#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;
    explicit Node(int val = 0): data(val), next(nullptr) {};
};


class Clink {
public:
    Clink() {
        head = new Node();
    }
    ~Clink() {
        Node* p = head;
        while(p != nullptr) {
            head = head->next;
            delete p;
            p = head;
        }
    }

    void insertTail(int val) {
        Node* p = head;
        while(p->next != nullptr) {
            p = p->next;
        }
        p->next = new Node(val);
    }

    void insertHead(int val) {
        Node* p = new Node(val);
        p->next = head->next;
        head->next = p;
    }

    bool find(int val) {
        Node* p = head->next;
        while(p != nullptr) {
            if(p->data == val) return true;
            p = p->next;
        }
        return false;
    }

    void remove(int val, int num = 1) {
        Node* p = head;
        while(num && p->next != nullptr) {
            if(p->next->data == val) {
                Node* tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            } else{
                p = p->next;
            }
        }
    }

    void reverse() {
        Node* p = head->next;
        head->next = nullptr; //让链表最后一个节点的 next 指向 nullptr;
        while(p != nullptr) {
            Node* q = p->next;
            p->next = head->next;
            head->next = p;
            p = q;
        }
    }

    void show() {
        Node* p = head->next;
        while(p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
private:
    Node* head;
};



int main() {
    Clink clink;
    for(int i = 1; i <= 9; i++) {
        clink.insertTail(i);
        clink.insertHead(i);
    }
    clink.show();
    clink.remove(5, 10);
    cout << clink.find(5) << endl;
    clink.reverse();
    clink.show();

    return 0;
}































