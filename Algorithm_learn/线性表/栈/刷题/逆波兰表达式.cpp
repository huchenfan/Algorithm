#include<iostream>
#include<vector>

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

int cal(int a, int b, char ch) {
    switch (ch) {
        case '+':
            return a +b;
        case '-':
            return a - b;
        case '*':
            return a*b;
        case '/':
            return a/b;
    }
    throw "";
}

int evalRPN(vector<string>& tokens) {
    ClinkStack stack;
    for(string str : tokens) {
        if(str.size() == 1 && (str[0] == '+' || str[0] == '-' ||str[0] == '*' ||str[0] == '/')) {
            int r = stack.top(); stack.pop();
            int l = stack.top(); stack.pop();
            stack.push(cal(l, r, str[0]));
        } else {
            stack.push(stoi(str));
        }
    }
    return stack.top();
}

int main() {
    vector<string> str = {"2", "6", "4", "2", "-", "/", "4", "6", "+", "2", "/", "+", "+"};
    cout << evalRPN(str) << endl;
    return 0;
}
