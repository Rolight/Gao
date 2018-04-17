/*
 * [224] Basic Calculator
 *
 * https://leetcode.com/problems/basic-calculator/description/
 *
 * algorithms
 * Hard (28.71%)
 * Total Accepted:    65.6K
 * Total Submissions: 228.3K
 * Testcase Example:  '"1 + 1"'
 *
 * Implement a basic calculator to evaluate a simple expression string.
 *
 * The expression string may contain open ( and closing parentheses ), the plus
 * + or minus sign -, non-negative integers and empty spaces  .
 *
 * You may assume that the given expression is always valid.
 *
 * Some examples:
 *
 * "1 + 1" = 2
 * " 2-1 + 2 " = 3
 * "(1+(4+5+2)-3)+(6+8)" = 23
 *
 *
 *
 *
 * Note: Do not use the eval built-in library function.
 *
 */
#include <iostream>
#include <stack>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;

class Solution {
   public:
    bool is_num(char c) { return c >= '0' && c <= '9'; }
    void eat_empty(string &s, int &pos) {
        while (pos < s.length() && s[pos] == ' ') pos++;
    }
    int get_num(string &s, int &pos) {
        int ret = 0;
        while (pos < s.length() && is_num(s[pos])) {
            ret = ret * 10 + s[pos] - '0';
            pos++;
        }
        return ret;
    }

    int do_op(stack<char> &op, stack<int> &num) {
        int a = num.top();
        num.pop();
        int b = num.top();
        num.pop();
        char opr = op.top();
        op.pop();
        if (opr == '+')
            return a + b;
        else
            return b - a;
    }
    template <class T>
    void printStack(stack<T> stk) {
        while (!stk.empty()) {
            cout << stk.top() << " ";
            stk.pop();
        }
        cout << endl;
    }
    int calculate(string s) {
        stack<char> op;
        stack<int> num;
        num.push(0);
        int pos = 0, ans = 0;
        while (pos < s.length()) {
            eat_empty(s, pos);
            // printStack(num);
            // printStack(op);
            if (pos == s.length()) break;
            if (is_num(s[pos])) {
                int cur_num = get_num(s, pos);
                num.push(cur_num);
            } else {
                if (s[pos] == '+' || s[pos] == '-') {
                    if (!op.empty() && (op.top() == '+' || op.top() == '-')) {
                        int cur_num = do_op(op, num);
                        num.push(cur_num);
                    }
                    op.push(s[pos]);
                } else if (s[pos] == '(') {
                    op.push(s[pos]);
                } else {
                    if (op.top() == '+' || op.top() == '-') {
                        int cur_num = do_op(op, num);
                        num.push(cur_num);
                    }
                    op.pop();
                }
                pos++;
            }
        }
        if (!op.empty()) {
            int cur_num = do_op(op, num);
            num.push(cur_num);
        }
        ans = num.top();
        return ans;
    }
};

int main() {
    string buf;
    while (cin >> buf) {
        Solution s;
        cout << s.calculate(buf) << endl;
    }
    return 0;
}