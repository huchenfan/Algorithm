#include<iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
    explicit Node(int val = 0) : data(val), next(nullptr) {};
};

bool isClinkMerge(Node* head1, Node* head2, Node* &node) {
    int cnt1 = 0, cnt2 = 0;
    Node* p = head1->next;
    Node* q = head2->next;
    while(p!= nullptr) {
        cnt1++;
        p = p->next;
    }
    while(q != nullptr) {
        cnt2++;
        q = q->next;
    }
    p = head1;
    q = head2;
    if(cnt1 > cnt2) {
        int d = cnt1 - cnt2;
        while(d-- > 0) {
            p = p->next;
        }
    } else {
        int d = cnt2 - cnt1;
        while(d-- > 0) {
            q = q->next;
        }
    }
    while(p != nullptr && q != nullptr) {
        p = p->next;
        q = q->next;
        if(p == q) {
            node = p;
            return true;
        }
    }
    return false;
}


int main() {
    Node head1, head2;
    Node n1(25), n2(67), n3(32), n4(18);
    head1.next = &n1;
    head2.next = &n3;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    Node* tmp;
    if(isClinkMerge(&head1, &head2, tmp)) {
        cout << tmp->data << endl;
    } else cout << "false" << endl;
    return 0;
}










