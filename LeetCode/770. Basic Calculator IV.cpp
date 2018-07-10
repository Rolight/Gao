#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct ExpNode {
    int coff;
    vector<string> tokens;

    string to_str() const {
        ostringstream os;
        os << coff;
        for (vector<string>::const_iterator iter = tokens.cbegin();
             iter != tokens.cend(); ++iter) {
            os << "*" << *iter;
        }
        return os.str();
    }

    int deg() { return tokens.size(); }

    bool operator<(const ExpNode &x) const { return tokens < x.tokens; }
};

bool output_cmp(ExpNode a, ExpNode b) {
    if (a.deg() == b.deg()) {
        return a.tokens < b.tokens;
    } else {
        return a.deg() > b.deg();
    }
}

class Solution {
    unordered_map<string, int> evallist;
    unordered_map<char, int> op_priority;

    void prepare_eval(vector<string> &evalvars, vector<int> &evalints) {
        evallist.clear();
        for (int i = 0; i < evalvars.size(); i++) {
            evallist[evalvars[i]] = evalints[i];
        }
    }

    ExpNode node_mul(ExpNode &a, ExpNode &b) {
        ExpNode ret;
        ret.coff = a.coff * b.coff;
        for (int i = 0; i < a.tokens.size(); i++) {
            ret.tokens.push_back(a.tokens[i]);
        }
        for (int j = 0; j < b.tokens.size(); j++) {
            ret.tokens.push_back(b.tokens[j]);
        }
        sort(ret.tokens.begin(), ret.tokens.end());
        return ret;
    }

    vector<ExpNode> exp_mul(vector<ExpNode> &a, vector<ExpNode> &b) {
        vector<ExpNode> ret;
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                ret.push_back(node_mul(a[i], b[j]));
            }
        }
        sort(ret.begin(), ret.end());
        return ret;
    }

    vector<ExpNode> exp_add(vector<ExpNode> &a, vector<ExpNode> &b) {
        vector<ExpNode> ret;
        int n = a.size(), m = b.size();
        int i = 0, j = 0;
        while (i < n || j < m) {
            if (i == n) {
                ret.push_back(b[j++]);
            } else if (j == m) {
                ret.push_back(a[i++]);
            } else if (a[i].tokens < b[j].tokens) {
                ret.push_back(a[i++]);
            } else if (a[i].tokens > b[j].tokens) {
                ret.push_back(b[j++]);
            } else {
                ExpNode e = a[i];
                e.coff += b[j].coff;
                if (e.coff != 0) ret.push_back(e);
                i++;
                j++;
            }
        }
        return ret;
    }

    vector<ExpNode> exp_sub(vector<ExpNode> &a, vector<ExpNode> &b) {
        vector<ExpNode> ret;
        int n = a.size(), m = b.size();
        int i = 0, j = 0;
        while (i < n || j < m) {
            if (i == n) {
                ret.push_back(b[j++]);
                ret.back().coff *= -1;
            } else if (j == m) {
                ret.push_back(a[i++]);
            } else if (a[i].tokens < b[j].tokens) {
                ret.push_back(a[i++]);
            } else if (a[i].tokens > b[j].tokens) {
                ret.push_back(b[j++]);
                ret.back().coff *= -1;
            } else {
                ExpNode e = a[i];
                e.coff -= b[j].coff;
                if (e.coff != 0) ret.push_back(e);
                i++;
                j++;
            }
        }
        return ret;
    }

    vector<ExpNode> calc(vector<string> &exp, int l, int r) {
        printf("%d->%d calc: ", l, r);
        for (int i = l; i <= r; i++) {
            printf("%s ", exp[i].c_str());
        }
        puts("");
        vector<ExpNode> ret;
        if (l > r) {
            ExpNode node;
            node.coff = 1;
            ret.push_back(node);
            return ret;
        }
        if (l == r) {
            ExpNode node;
            if (exp[l][0] >= 'a' && exp[l][0] <= 'z') {
                if (evallist.count(exp[l]) != 0) {
                    node.coff = evallist[exp[l]];
                    ret.push_back(node);
                    return ret;
                } else {
                    node.coff = 1;
                    node.tokens.push_back(exp[l]);
                    ret.push_back(node);
                    return ret;
                }
            } else {
                node.coff = 0;
                for (int i = 0; i < exp[l].size(); i++) {
                    node.coff = node.coff * 10 + exp[l][i] - '0';
                }
                ret.push_back(node);
                return ret;
            }
        }
        int now_dep = 0;
        int lowest_op_pos = -1;
        for (int i = l; i <= r; i++) {
            if (exp[i] == "(") {
                now_dep++;
            } else if (exp[i] == ")") {
                now_dep--;
            } else if (op_priority.count(exp[i][0]) != 0) {
                if (now_dep != 0) continue;
                if (lowest_op_pos == -1 ||
                    op_priority[exp[i][0]] <=
                        op_priority[exp[lowest_op_pos][0]]) {
                    lowest_op_pos = i;
                }
            }
        }
        if (exp[l] == "(" && exp[r] == ")" && lowest_op_pos == -1) {
            return calc(exp, l + 1, r - 1);
        }
        vector<ExpNode> lret = calc(exp, l, lowest_op_pos - 1),
                        rret = calc(exp, lowest_op_pos + 1, r);
        string op = exp[lowest_op_pos];
        if (op == "+") ret = exp_add(lret, rret);
        if (op == "-") ret = exp_sub(lret, rret);
        if (op == "*") ret = exp_mul(lret, rret);
        return ret;
    }

   public:
    vector<string> basicCalculatorIV(string expression,
                                     vector<string> &evalvars,
                                     vector<int> &evalints) {
        prepare_eval(evalvars, evalints);
        op_priority['+'] = 0;
        op_priority['-'] = 0;
        op_priority['*'] = 1;
        vector<string> buf;
        // remove space
        for (int i = 0; i < expression.length(); i++) {
            if (expression[i] == ' ')
                continue;
            else if (expression[i] == '(' || expression[i] == ')' ||
                     op_priority.count(expression[i]) != 0) {
                buf.push_back(string("") + expression[i]);
            } else if (buf.size() == 0) {
                buf.push_back(string("") + expression[i]);
            } else if (expression[i] >= '0' && expression[i] <= '9') {
                if (buf.back()[0] >= '0' && buf.back()[0] <= '9') {
                    buf.back().push_back(expression[i]);
                } else {
                    buf.push_back(string("") + expression[i]);
                }
            } else if (expression[i] >= 'a' && expression[i] <= 'z') {
                if (buf.back()[0] >= 'a' && buf.back()[0] <= 'z') {
                    buf.back().push_back(expression[i]);
                } else {
                    buf.push_back(string("") + expression[i]);
                }
            }
        }

        printf("split exp to ");
        for (int i = 0; i < buf.size(); i++) {
            printf("%s ", buf[i].c_str());
        }
        puts("");

        vector<ExpNode> res = calc(buf, 0, buf.size() - 1);
        sort(res.begin(), res.end(), output_cmp);
        vector<ExpNode> ans;
        vector<string> ret;
        for (int i = 0; i < res.size(); i++) {
            if (ans.size() > 0 && res[i].tokens == ans.back().tokens) {
                ans.back().coff += res[i].coff;
                if (ans.back().coff == 0) {
                    ans.pop_back();
                }
            } else if (res[i].coff != 0) {
                ans.push_back(res[i]);
            }
        }
        for (int i = 0; i < ans.size(); i++) ret.push_back(ans[i].to_str());
        return ret;
    }
};