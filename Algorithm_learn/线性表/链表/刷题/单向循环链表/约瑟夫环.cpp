#include<iostream>

using namespace std;

struct Node {
    int data;
    Node *next;

    explicit Node(int val = 0)
            : data(val), next(nullptr) {};
};

void Joseph(Node *&head, int k, int m) {
    if (head) return;
    Node *h = head;
    Node *t = head;
    while (k-- > 1) {
        t = h;
        h = h->next;
    }
    while (true) {
        for (int i = 1; i < m; i++) {
            t = h;
            h = h->next;
        }
        cout << h->data << " ";
        if (h == t) {
            delete h;
            head = nullptr;
            break;
        }
        t->next = h->next;
        delete h;
        h = t->next;
    }
}

int main() {
    Node *head = new Node(1);
    Node *n1 = new Node(2);
    Node *n2 = new Node(3);
    Node *n3 = new Node(4);
    Node *n4 = new Node(5);
    Node *n5 = new Node(6);
    Node *n6 = new Node(7);
    Node *n7 = new Node(8);
    head->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;
    n7->next = head;
    Joseph(head, 1, 3);
    return 0;
}
