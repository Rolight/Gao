/*
 * [65] Valid Number
 *
 * https://leetcode.com/problems/valid-number/description/
 *
 * algorithms
 * Hard (12.94%)
 * Total Accepted:    82.8K
 * Total Submissions: 639.7K
 * Testcase Example:  '"3"'
 *
 * Validate if a given string is numeric.
 *
 *
 * Some examples:
 * "0" => true
 * "   0.1  " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 *
 *
 * Note: It is intended for the problem statement to be ambiguous. You should
 * gather all requirements up front before implementing one.
 *
 *
 *
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. If you still see your
 * function signature accepts a const char * argument, please click the reload
 * button  to reset your code definition.
 *
 */
#include <iostream>
#include <string>

using std::string;

class Automata {
    string buf;
    int pos, m;
    bool ok;

   public:
    Automata(string &buf) : buf(buf), pos(0), ok(false) { m = buf.length(); }

    bool run() {
        start();
        return ok;
    }

    void start() { negativeSign(); }

    void negativeSign() {
        if (buf[pos] == '-' || buf[pos] == '+') pos++;
        if (pos < m) integerPart();
    }

    void integerPart() {
        bool exist = false;
        while (pos < m && buf[pos] <= '9' && buf[pos] >= '0') {
            pos++;
            exist = true;
        }
        if (pos == m) {
            ok = true;
        } else {
            dot(exist);
        }
    }

    void dot(bool integer) {
        if (buf[pos] == '.') {
            pos++;
            if (pos == m && integer) {
                ok = true;
            } else {
                decimalPart(integer);
            }
        } else if (integer) {
            e();
        }
    }

    void decimalPart(bool integer) {
        bool exist = false;
        while (pos < m && buf[pos] <= '9' && buf[pos] >= '0') {
            exist = true;
            pos++;
        }
        if (pos == m && (integer || exist)) {
            ok = true;
        } else if (integer || exist) {
            e();
        }
    }

    void e() {
        if (buf[pos] == 'e') {
            pos++;
            if (pos < m) exponentNegativeSign();
        }
    }

    void exponentNegativeSign() {
        if (buf[pos] == '-' || buf[pos] == '+') pos++;
        if (pos < m) exponentInteger();
    }

    void exponentInteger() {
        while (pos < m && buf[pos] <= '9' && buf[pos] >= '0') {
            pos++;
        }
        if (pos == m) {
            ok = true;
        }
    }
};

class Solution {
   public:
    bool isempty(char c) { return c == '\n' || c == ' ' || c == '\t'; }
    string strip(string &s) {
        string::iterator head = s.begin(), tail = s.end();
        while (head != tail && isempty(*head)) ++head;
        while (head != tail && isempty(*(tail - 1))) --tail;
        return string(head, tail);
    }
    bool isNumber(string s) {
        s = strip(s);
        int m = s.length();

        std::cout << "after strip the s is: " << s << std::endl;
        Automata a = Automata(s);
        return a.run();
    }
};

int main() {
    string buf;
    while (std::cin >> buf) {
        Solution s;
        std::cout << s.isNumber(buf) << std::endl;
    }
}