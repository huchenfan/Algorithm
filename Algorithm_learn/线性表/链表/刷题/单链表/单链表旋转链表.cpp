#include<iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    explicit Node(int val = 0): data(val), next(nullptr) {};
};

Node* circle(Node* head, int cnt) {
    Node* p = head;
    int count = 1;
    if(p == nullptr) return nullptr;
    while(p->next != nullptr) {
        count++;
        p = p->next;
    }
    p->next = head;
    int num = ((count - cnt) % count + count) % count;
    if(num == 0) {
        p->next = nullptr;
        return head;
    }
    p = head;
    while(--num > 0) {
        p = p->next;
    }
    head = p->next;
    p->next = nullptr;
    return head;
}

int main() {
    Node head(0);
    Node n1(1), n2(2), n3(3), n4(4);
    head.next = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    Node* tmp = circle(&head, 3);
    while(tmp!=nullptr) {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << endl;
    return 0;
}
