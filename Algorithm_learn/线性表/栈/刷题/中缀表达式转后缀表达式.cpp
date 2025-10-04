#include<iostream>
#include<vector>
#include<string>
#include<stack>

using namespace std;


int cal(int a, int b, char ch) {
    switch (ch) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
    throw "";
}

int evalRPN(vector<string> &tokens) {
    stack<int> stack;
    for (string str: tokens) {
        if (str.size() == 1 && (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/')) {
            int r = stack.top();
            stack.pop();
            int l = stack.top();
            stack.pop();
            stack.push(cal(l, r, str[0]));
        } else {
            stack.push(stoi(str));
        }
    }
    return stack.top();
}

bool priority(char ch, char topCh) {
    if (topCh == '(') return true;
    if ((ch == '*' || ch == '/') && (topCh == '+' || topCh == '-')) return true;
    return false;
}

vector<string> mtoE(string &str) {
    vector<string> result;
    stack<char> stack;
    string num;
    for (int i = 0; i < str.size(); i++) {
        char ch = str[i];
        if (ch == ' ') {
            str[i] = str[i-1];  // 类似于 去空格
            continue;
        }
        if (isdigit(ch)) {
            if(str[i-1] == '-')  num+= '-';
            num += ch;
            continue;
        } else {
            if (!num.empty()) {
                result.push_back(num);
                num.clear();
            }
        }
        if(ch == '-' && (i == 0 || !isdigit(str[i-1]))) continue;  // 为了可以记录 负数
        if (ch == '(' || stack.empty()) {
            stack.push(ch);
            continue;
        }
        if (ch != ')') {
            if (!priority(ch, stack.top())) {
                result.emplace_back(1, stack.top());
                stack.pop();
            }
            stack.push(ch);
            continue;
        }
        while (!stack.empty()) {
            if (stack.top() == '(') {
                stack.pop();
                break;
            }
            result.emplace_back(1, stack.top());
            stack.pop();
        }
    }
    if (!num.empty()) {
        result.push_back(num);
        num.clear();
    }
    while (!stack.empty()) {
        result.emplace_back(1, stack.top());
        stack.pop();
    }
    return result;
}

int main() {
    string str = "((10 * (6 / ((9 + 3) * -11))) + 17) + 5";
    vector<string> s = mtoE(str);
    for (const string &ele: s) {
        cout << '"' << ele << '"' <<" ";
    }
    cout << endl;
    cout << evalRPN(s) << endl;
    return 0;
}