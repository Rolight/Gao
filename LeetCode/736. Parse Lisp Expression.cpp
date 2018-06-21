#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    vector<unordered_map<string, int> > scope;

    int variable_value(string name) {
        for (int i = scope.size() - 1; i >= 0; i--) {
            if (scope[i].count(name) != 0) {
                return scope[i][name];
            }
        }
        return -1;
    }

    string get_cmd(string &buf, int &pos) {
        string cmd;
        while (buf[pos] >= 'a' && buf[pos] <= 'z') {
            cmd += buf[pos];
            pos++;
        }
        cout << "get cmd " << cmd << endl;
        return cmd;
    }

    string get_variable_name(string &buf, int &pos) {
        string name;
        while (buf[pos] >= 'a' && buf[pos] <= 'z' ||
               buf[pos] >= '0' && buf[pos] <= '9') {
            name += buf[pos];
            pos++;
        }
        cout << "get variable name " << name << endl;
        return name;
    }

    int get_integer(string &buf, int &pos) {
        int ret = 0;
        bool neg_flag = false;
        if (buf[pos] == '-') {
            neg_flag = true;
            pos++;
        }
        while (buf[pos] >= '0' && buf[pos] <= '9') {
            ret = ret * 10 + buf[pos] - '0';
            pos++;
        }
        if (neg_flag) ret = -ret;
        printf("get integer %d\n", ret);
        return ret;
    }

    int gao(string &buf, int &pos) {
        int ret;
        if (buf[pos] != '(') {
            // single integer or variable
            if (buf[pos] >= 'a' && buf[pos] <= 'z') {
                ret = variable_value(get_variable_name(buf, pos));
            } else {
                ret = get_integer(buf, pos);
            }
            printf("get single expression %d\n", ret);
            return ret;
        }
        scope.push_back(unordered_map<string, int>());

        pos++;  // head bracket
        // expression
        string cmd = get_cmd(buf, pos);
        pos++;  // skip single space
        if (cmd == "let") {
            // let expression
            while (1) {
                if (buf[pos] >= 'a' && buf[pos] <= 'z') {
                    // variable name
                    string name = get_variable_name(buf, pos);
                    if (buf[pos] == ' ') {
                        // var exp
                        pos++;  // skip space
                        int variable_value = gao(buf, pos);
                        // assign variable
                        scope.back()[name] = variable_value;
                        // skip space
                        pos++;
                    } else if (buf[pos] == ')') {
                        // variable as expression
                        ret = variable_value(name);
                        break;
                    }
                } else if (buf[pos] == '(') {
                    // expression
                    ret = gao(buf, pos);
                    break;
                } else if (buf[pos] >= '0' && buf[pos] <= '9' ||
                           buf[pos] == '-') {
                    ret = get_integer(buf, pos);
                    break;
                }
            }
        } else if (cmd == "add") {
            // add expression (add e1 e2)
            int e1 = gao(buf, pos);
            pos++;  // skip single space
            int e2 = gao(buf, pos);
            ret = e1 + e2;
        } else {
            // multi expression
            int e1 = gao(buf, pos);
            pos++;  // skip single space
            int e2 = gao(buf, pos);
            ret = e1 * e2;
        }
        pos++;  // tail bracket

        scope.pop_back();
        return ret;
    }

   public:
    int evaluate(string expression) {
        int pos = 0;
        return gao(expression, pos);
    }
};

int main() {
    string buf;
    getline(cin, buf);
    Solution s;
    cout << s.evaluate(buf) << endl;
    return 0;
}