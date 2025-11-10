#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<queue>

using namespace std;

class Trie {
public:
    Trie()
    {
        root_ = new TrieNode();
    }
    ~Trie()
    {
        queue<TrieNode*> nodes;
        nodes.emplace(root_);
        while(!nodes.empty()) {
            TrieNode* front = nodes.front();
            nodes.pop();
            for(auto &ele : front->children) {
                nodes.emplace(ele.second);
            }

            delete front;
        }
    }
    // 添加接口
    void add(const string &str)
    {
        TrieNode* cur = root_;
        for(char i : str) {
            auto child = cur->children.find(i);
            if(child == cur->children.end()) {
                auto* node = new TrieNode(i);
                cur->children.emplace(i, node);
                cur = node;
            }
            else {
                cur = child->second;
            }
        }
        cur->freq_++;
    }
    // 删除接口
    void remove(const string &str)
    {
        TrieNode* cur = root_;
        TrieNode* del = root_;
        char delChar;
        for(char i : str) {
            auto child = cur->children.find(i);
            if(child == cur->children.end()) {
                return;
            }
            else {
                if(cur->freq_ > 0 || cur->children.size() > 1) {
                    del = cur;
                    delChar = i;
                }
                cur = child->second;
            }
        }

        if(cur->children.empty()) {
            TrieNode* start = del->children[delChar];
            queue<TrieNode*> nodes;
            nodes.emplace(start);
            while(!nodes.empty()) {
                TrieNode* front = nodes.front();
                nodes.pop();
                for(auto &ele : front->children) {
                    nodes.emplace(ele.second);
                }
                delete front;
            }

            del->children.erase(delChar);
        }
        else {
            cur->freq_ = 0;
        }
    }
    // 查询接口
    int query(const string &str)
    {
        TrieNode* cur = root_;
        for(char i : str) {
           auto child = cur->children.find(i);
           if(child == cur->children.end()) {
               return 0;
           }
           else {
               cur = child->second;
           }
        }
        return cur->freq_;
    }
    // 顺序打印
    void preOrder()
    {
        string word;
        vector<string> wordList;
        preOrder(root_, word, wordList);
        for(const auto& str : wordList) {
            cout << str << endl;
        }

    }
    // 前缀搜索
    vector<string> queryPrefix(string fix)
    {
        vector<string> ans;
        TrieNode* cur = root_;
        for(char i : fix) {
            auto it = cur->children.find(i);
            if(it == cur->children.end()) {
                return ans;
            }
            cur = it->second;
        }
        fix.pop_back();
        queryPrefix(cur, fix, ans);
        return ans;
    }
private:
    struct TrieNode {
        explicit TrieNode (char ch = '\0', int freq = 0)
            : ch_(ch)
            , freq_(freq)
        {}
        char ch_;
        int freq_;
        map<char, TrieNode*> children;
    };
private:
    void preOrder(TrieNode* node,  string word, vector<string> &wordList)
    {
        if(node != root_ ) {
            word.push_back(node->ch_);
            if(node->freq_ > 0) {
                wordList.push_back(word);
            }
        }

        for(auto child : node->children) {
            preOrder(child.second, word, wordList);
        }
    }
    void queryPrefix(TrieNode* node, string word, vector<string> &wordList)
    {
        word.push_back(node->ch_);
        if(node->freq_ > 0) {
            wordList.push_back(word);
        }

        for(auto child : node->children) {
            queryPrefix(child.second, word, wordList);
        }
    }
private:
    TrieNode* root_;
};


int main() {
    Trie trie;
    trie.add("Mask");
    trie.add("Maya");
    trie.add("Memory");
    trie.add("Mary");
    trie.add("Make");
    trie.add("Mark");

//    trie.preOrder();

    vector<string> vec = trie.queryPrefix("Ma");
    for(const auto& i : vec) {
        cout << i << endl;
    }
    return 0;
}

