#include <bits/stdc++.h>

using namespace std;

struct Node{
    int value;
    Node *left;
    Node *right;
};

void search(Node* header, vector<int> &ans){
    queue<Node*> que;
    ans.push_back(header->value);
    que.push(header);
    while(!que.empty()) {
        Node* cur = que.front(); que.pop();
        if(cur->left){
            ans.push_back(cur->left->value);
            que.push(cur->left);
        }
        if(cur->right){
            ans.push_back(cur->right->value);
            que.push(cur->right);
        }
    }
}

int main(){

}