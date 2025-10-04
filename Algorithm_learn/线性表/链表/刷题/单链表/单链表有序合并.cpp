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

    void findK(int k = 1) {
        Node* h = head;
        Node* t = head;
        while(h != nullptr) {
            if(k){
                k--;
                h = h->next;
                continue;
            }
            h = h->next;
            t = t->next;
        }

        if(t != head && t != nullptr) cout << t->data << endl;
        else cout << "undefined" << endl;
    }
private:
    Node* head;
    friend void merge(Clink &clink1, Clink &clink2);
};


//void merge(Clink &clink1, Clink &clink2) {
//    Node* p = clink1.head->next;
//    Node* q = clink2.head->next;
//    Node* last = clink1.head;
//    while(p != nullptr && q != nullptr) {
//        if(p->data < q->data) {
//            last->next = p;
//            p = p->next;
//            last = last->next;
//        } else{
//            last->next = q;
//            q = q->next;
//            last = last->next;
//        }
//    }
//    if(p == nullptr) last->next = q;
//    if(q == nullptr) last->next = p;
//    clink2.head->next = nullptr;
//}

void merge(Clink &clink1, Clink &clink2) {
    Node* h1 = clink1.head;
    Node* h2 = clink2.head;
    while(h1->next!= nullptr && h2->next != nullptr) {
        if(h1->next->data < h2->next->data) {
            Node* tmp = h1->next->next;
            h1->next->next = h2->next;
            h2->next = tmp;
        } else{
            Node* tmp = h2->next->next;
            h2->next->next = h1->next;
            h1->next = h2->next;
            h2->next = tmp;
        }
        h1 = h1->next;
    }
    if(clink1.head->next == nullptr) clink1.head->next = clink2.head->next;
    clink2.head->next = nullptr;
}


int main() {
    Clink clink1, clink2;
    for(int i = 1; i <= 6; i+=2) {
        clink1.insertTail(i);
        clink2.insertTail(i+1);
    }
    clink1.show();
    clink2.show();
    merge(clink1, clink2);
    clink1.show();

    return 0;
}
