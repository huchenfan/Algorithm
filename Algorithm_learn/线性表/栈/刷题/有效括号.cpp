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



bool isGood(const string& str)
{
    if(str.size() & 1) return false;
    int ascii[256];
    ascii['('] = 1; ascii[')'] = -1;
    ascii['['] = 2; ascii[']'] = -2;
    ascii['{'] = 3; ascii['}'] = -3;
    ClinkStack stack;
    for(char ch : str) {
        int ele = ascii[ch];
        if(stack.empty()) {
            stack.push(ele);
            continue;
        }
        if(ele > 0) stack.push(ele);
        else {
            if(ele == -stack.top()) stack.pop();
            else stack.push(ele);
        }
    }
    return stack.empty();
}

int main() {
    string str = "([}}])";
    if(isGood(str)) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}
