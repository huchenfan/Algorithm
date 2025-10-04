#include<iostream>

using namespace std;

struct Node
{
    explicit Node(int val = 0)
        : data(val)
        , next(nullptr)
    {}
    int data;
    Node* next;
};

class Queue
{
public:
    Queue()
    {
        head = new Node();
        tail = head;
        mSize = 0;
    }

    ~Queue()
    {
        Node* p = head;
        while(p != nullptr) {
            head = head->next;
            delete p;
            p = head;
        }
    }

    void push(int val)
    {
        Node* p = new Node(val);
        tail->next = p;
        tail = p;
        mSize++;
    }

    void pop()
    {
        if(head == tail) return;
        Node* p = head->next;
        head->next = p->next;
        if(tail == p) tail = head;
        delete p;
        mSize--;
    }

    int front() const
    {
        if(head == tail) throw " ";
        return head->next->data;
    }

    int back() const
    {
        if(head == tail) throw " ";
        return tail->data;
    }

    bool empty() const
    {
        return head == tail;
    }

    int size() const
    {
        return mSize;
    }

private:
    Node* head;
    Node* tail;
    int mSize;
};

int main() {
    Queue queue;
    for(int i = 0; i<10; i++) {
        queue.push(i);
    }
    queue.pop();
    cout << queue.front() << " ";
    cout << queue.back() << " ";
    cout << queue.size() << endl;
    if(queue.empty()) cout << "The queue is empty" << endl;
    else cout << "The queue is not empty" << endl;
    return 0;
}