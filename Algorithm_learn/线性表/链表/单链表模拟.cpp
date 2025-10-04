#include<iostream>

using namespace std;

struct Node {
    explicit Node(int val = 0): data(val), next(nullptr) {};
    int data;
    Node* next;
};

class Clink {
public:
    Clink() {
        head = new Node();
    }

    ~Clink(){
        Node* p = head;
        while(p != nullptr) {
            head = head->next;
            delete p;
            p = head;
        }
    }

    // 尾插
    void insertTail(int val) {
        Node* p = head;
        while(p->next!=nullptr) p = p -> next;
        p->next = new Node(val);
    }

    // 头插
    void insertHead(int val) {
        Node* p = new Node(val);
        p->next = head->next;
        head->next = p;
    }

    // 删除元素
    void remove(int val, int num = 1) {
        Node* p = head;
        while(num && p->next!=nullptr) {
            if(p->next->data == val) {
                num--;
                Node* tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            }else{
                p = p->next;
            }
        }
    }

    // 查找元素
    bool find(int val){
        Node* p = head->next;
        while(p!=nullptr){
            if(p->data == val) return true;
            p = p->next;
        }
        return false;
    }

    // 链表逆序
    void reverse() {
        Node*p = head->next;
        head->next = nullptr;
        while(p != nullptr) {
            Node*q = p->next;
            p->next = head->next;
            head->next = p;
            p = q;
        }
    }

    // 打印链表
    void show() {
        Node* p = head->next;
        while(p != nullptr) {
            cout << p->data << " ";
            p = p -> next;
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