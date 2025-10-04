#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;
    explicit Node(int val = 0): data(val), next(nullptr) {};
};

bool isClinkCircle(Node* head, Node* &node) {
    Node* fast = head; Node* slow = head;
    Node* a; Node* b;
    bool flag = false;
    while( fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next; slow = slow->next;
        if(slow == fast && !flag) {
            a = head; b = slow;
            flag = true;
        }
        if(flag) {
            a = a->next; b = b->next;
            if(a == b) {
                node = a;
                break;
            }
        }
    }
    return flag;
}

int main() {
    Node head;
    Node n1(25), n2(67), n3(32), n4(18);
    head.next = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n1;
    Node* tmp;
    if(isClinkCircle(&head, tmp)) {
        cout << tmp->data << endl;
    }else {
        cout << "false" << endl;
    }
    return 0;
}

