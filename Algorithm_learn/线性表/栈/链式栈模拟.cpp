#include<iostream>

using namespace std;

struct Node {
    explicit Node(int val = 0)
        : data(val)
        , next(nullptr)
    {}
    int data;
    Node *next;
};

class ClinkStack {
public:
    explicit ClinkStack()
        : size_(0)
    {
        head = new Node();
    }

    ~ClinkStack() {
        Node *p = head;
        while (p != nullptr) {
            head = head->next;
            delete p;
            p = head;
        }
    }

    int top() const {
        if (head->next == nullptr) throw "The stack is empty";
        return head->next->data;
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void push(int val) {
        Node *p = new Node(val);
        p->next = head->next;
        head->next = p;
        size_++;
    }

    void pop() {
        if (head->next == nullptr) throw "The stack is empty";
        Node *p = head->next;
        head->next = p->next;
        delete p;
        size_--;
    }

private:
    Node *head;
    int size_;
};

int main() {
    ClinkStack stack;
    for (int i = 0; i < 10; i++) {
        stack.push(i);
    }
    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
    return 0;
}
