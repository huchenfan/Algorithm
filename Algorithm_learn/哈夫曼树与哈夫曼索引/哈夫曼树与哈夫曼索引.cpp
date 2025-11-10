#include <iostream>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;


class HuffmanTree {
public:
    HuffmanTree()
        : root_(nullptr)
        , minHeap([](Node* n1, Node* n2) -> bool{return n1->weight_ > n2->weight_;})
    {}

    ~HuffmanTree()
    {
        deleteNode(root_);
    }

    string encode(string &str)
    {
        createHuffmanTree(str);
        getHuffmanCode();
        string ans;
        for(char ch : str) {
            ans.append(codeMap[ch]);
        }
        return ans;
    }

    string decode(string &str)
    {
        Node* cur = root_;
        string ans;
        for(char ch : str) {
            if(ch == '0') {
                cur = cur->left_;
            }
            else {
                cur = cur->right_;
            }
            if(cur->left_ == nullptr && cur->right_ == nullptr) {
                ans.push_back(cur->data_);
                cur = root_;
            }
        }
        return ans;
    }

    void clear()
    {
        deleteNode(root_);
        root_ = nullptr;
        codeMap.clear();
    }
private:
    struct Node {
        explicit Node(char ch, int weight)
            : data_(ch)
            , weight_(weight)
            , left_(nullptr)
            , right_(nullptr)
        {}
        char data_;
        int weight_;
        Node* left_;
        Node* right_;
    };

private:
    void createHuffmanTree(string &str)
    {
        unordered_map<char, int> strMap;
        for(char ch : str) {
            strMap[ch]++;
        }
        for(auto it : strMap) {
            Node* node = new Node(it.first, it.second);
            minHeap.push(node);
        }

        while(minHeap.size() > 1) {
            Node* node1 = minHeap.top();
            minHeap.pop();
            Node* node2 = minHeap.top();
            minHeap.pop();
            Node* father = new Node('\0', node1->weight_+node2->weight_);
            father->left_ = node1;
            father->right_ = node2;
            minHeap.push(father);
        }
        root_ = minHeap.top();
        minHeap.pop();
    }

    void getHuffmanCode()
    {
        getHuffmanCode(root_, "");
    }

    void getHuffmanCode(Node* node, string code)
    {
        if(node->left_ == nullptr && node->right_ == nullptr) {
            codeMap.emplace(node->data_, code);
            return;
        }

        getHuffmanCode(node->left_, code + '0');
        getHuffmanCode(node->right_, code + '1');

    }

    void deleteNode(Node* node)
    {
        if(node == nullptr) {
            return;
        }
        deleteNode(node->left_);
        deleteNode(node->right_);

        delete node;
    }
private:
    Node* root_;
    unordered_map<char, string> codeMap;
    using MinHeap = priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>>;
    MinHeap minHeap;
};

int main() {
    HuffmanTree huffmanTree;
    string str = "huffmanTree";
    string encode = huffmanTree.encode(str);
    cout << encode << endl;
    string decode = huffmanTree.decode(encode);
    cout << decode << endl;
    huffmanTree.clear();
    cout << "+++++++++++++++++++++++++" << endl;
    string s = "I love you! I very very very love you!!!";
    encode = huffmanTree.encode(s);
    cout << encode << endl;
    decode = huffmanTree.decode(encode);
    cout << decode << endl;
}