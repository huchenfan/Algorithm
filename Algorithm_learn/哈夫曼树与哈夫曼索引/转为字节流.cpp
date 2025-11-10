#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <functional>
#include <vector>
#include <cstdint>

using namespace std;

class HuffmanTree {
public:
    HuffmanTree() : root_(nullptr), minHeap(compareNodes) {}

    ~HuffmanTree() {
        deleteNode(root_);
    }

    // 返回字节流 vector<uint8_t>
    vector<uint8_t> encode(string &str) {
        clear();
        createHuffmanTree(str);
        getHuffmanCode();

        string binaryStr;
        for(char ch : str) {
            auto it = codeMap.find(ch);
            if(it != codeMap.end()) {
                binaryStr.append(it->second);
            }
        }



        vector<uint8_t> byteStream;

        // 第一个字节存储补位数量（0-7）
        uint8_t padding = (8 - binaryStr.length() % 8) % 8;
        byteStream.push_back(padding);

        // 补足8的倍数
        for(int i = 0; i < padding; ++i) {
            binaryStr.push_back('0');
        }

        // 每8位转成一个字节
        for(size_t i = 0; i < binaryStr.length(); i += 8) {
            uint8_t byte = 0;
            for(int j = 0; j < 8; ++j) {
                byte = (byte << 1) | (binaryStr[i + j] - '0');
            }
            byteStream.push_back(byte);
        }

        return byteStream;
    }

    // 接收字节流 vector<uint8_t>
    string decode(vector<uint8_t> &byteStream) {
        if(byteStream.empty() || root_ == nullptr) return "";

        uint8_t padding = byteStream[0];
        string binaryStr;

        // 将字节流转回二进制字符串
        for(size_t i = 1; i < byteStream.size(); ++i) {
            uint8_t byte = byteStream[i];
            for(int j = 7; j >= 0; --j) {
                binaryStr.push_back(((byte >> j) & 1) + '0');
            }
        }

        // 去掉补的0
        if(padding > 0 && binaryStr.length() >= padding) {
            binaryStr = binaryStr.substr(0, binaryStr.length() - padding);
        }

        // 用霍夫曼树解码
        Node* cur = root_;
        string ans;
        for(char ch : binaryStr) {
            if(ch == '0') {
                cur = cur->left_;
            } else {
                cur = cur->right_;
            }
            if(cur->left_ == nullptr && cur->right_ == nullptr) {
                ans.push_back(cur->data_);
                cur = root_;
            }
        }
        return ans;
    }

    void clear() {
        deleteNode(root_);
        root_ = nullptr;
        codeMap.clear();
        while(!minHeap.empty()) {
            minHeap.pop();
        }
    }

private:
    struct Node {
        explicit Node(char data, int weight)
                : data_(data), weight_(weight), left_(nullptr), right_(nullptr) {}
        char data_;
        int weight_;
        Node* left_;
        Node* right_;
    };

    static bool compareNodes(Node* node1, Node* node2) {
        return node1->weight_ > node2->weight_;
    }

    void createHuffmanTree(string &str) {
        unordered_map<char, int> strMap;
        for(char ch : str) {
            strMap[ch]++;
        }

        for(auto &p : strMap) {
            Node* node = new Node(p.first, p.second);
            minHeap.push(node);
        }

        while(minHeap.size() > 1) {
            Node* node1 = minHeap.top(); minHeap.pop();
            Node* node2 = minHeap.top(); minHeap.pop();
            Node* father = new Node('\0', node1->weight_ + node2->weight_);
            father->left_ = node1;
            father->right_ = node2;
            minHeap.push(father);
        }

        if(!minHeap.empty()) {
            root_ = minHeap.top();
            minHeap.pop();
        }
    }

    void getHuffmanCode() {
        if(root_) getHuffmanCode(root_, "");
    }

    void getHuffmanCode(Node* node, string code) {
        if(!node) return;
        if(node->left_ == nullptr && node->right_ == nullptr) {
            codeMap[node->data_] = code;
            return;
        }
        getHuffmanCode(node->left_, code + '0');
        getHuffmanCode(node->right_, code + '1');
    }

    void deleteNode(Node* node) {
        if(!node) return;
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

// 辅助函数：打印字节流
void printByteStream(const vector<uint8_t>& byteStream) {
    cout << "字节流大小: " << byteStream.size() << " bytes" << endl;
    cout << "字节内容: ";
    for(size_t i = 0; i < byteStream.size() && i < 20; ++i) {
        cout << hex << (int)byteStream[i] << " ";
    }
    if(byteStream.size() > 20) cout << "...";
    cout << dec << endl;
}

int main() {
    HuffmanTree huffmanTree;

    cout << "=== 测试1: huffmanTree ===" << endl;
    string str = "huffmanTree";
    vector<uint8_t> encode = huffmanTree.encode(str);
    printByteStream(encode);
    string decode = huffmanTree.decode(encode);
    cout << "解码结果: " << decode << endl;
    cout << (decode == str ? "成功" : "失败") << endl;

    huffmanTree.clear();

    cout << "\n=== 测试2: 英文文本 ===" << endl;
    string s = "Because we plant in spring, we harvest in autumn.";
    encode = huffmanTree.encode(s);
    printByteStream(encode);
    decode = huffmanTree.decode(encode);
    cout << "解码结果长度: " << decode.length() << endl;
    cout << (decode == s ? "成功" : "失败") << endl;

    return 0;
}