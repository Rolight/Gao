#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<string> tag_stack;
    string buf;

    bool is_upper_case(char c) { return c >= 'A' && c <= 'Z'; }

    bool is_num(char c) { return c >= '0' && c <= '9'; }

    bool is_valid_tag_ch(char c) { return is_upper_case(c) || is_num(c); }

    string read_tag(int &pos) {
        // printf("start read tag at pos = %d\n", pos);

        string ret = "";
        if (buf[pos] != '<') {
            throw(1);
        }
        pos++;
        bool end_tag_flag = false;
        if (pos < buf.size() && buf[pos] == '/') {
            end_tag_flag = true;
            pos++;
        }
        while (pos < buf.size() && is_valid_tag_ch(buf[pos])) ret += buf[pos++];
        if (pos == buf.size() || buf[pos] != '>') {
            throw(1);
        }
        // printf("end read tag at pos = %d\n", pos);
        // printf("tag_name = %s\n", ret.c_str());
        if (ret.length() < 1 || ret.length() > 9) throw(1);
        if (end_tag_flag) ret = '/' + ret;
        ++pos;
        return ret;
    }

    void read_cdata(int &pos) {
        string cdata_head = "<![CDATA[";
        for (int i = 0; i < cdata_head.size(); i++) {
            if (pos + i == buf.size()) throw(1);
            if (buf[pos + i] != cdata_head[i]) throw(1);
        }
        pos += cdata_head.size();
        while (
            pos + 2 < buf.size() &&
            !(buf[pos] == ']' && buf[pos + 1] == ']' && buf[pos + 2] == '>')) {
            pos++;
        }
        if (pos + 2 == buf.size()) throw(1);
        pos += 3;
    }

    void read_tag_with_content(int &pos) {
        string tag_name = read_tag(pos);
        if (tag_name[0] == '/') throw(1);
        while (pos < buf.size()) {
            // printf("cur buf[pos] is %c\n", buf[pos]);
            if (buf[pos] == '<') {
                if (pos + 1 < buf.size() && buf[pos + 1] == '!') {
                    read_cdata(pos);
                } else if (pos + 1 < buf.size() && buf[pos + 1] == '/') {
                    string e_tag_name = read_tag(pos);
                    if (e_tag_name[0] == '/' && e_tag_name == '/' + tag_name) {
                        return;
                    } else {
                        throw(1);
                    }
                } else {
                    read_tag_with_content(pos);
                }
            } else {
                // printf("read normal tag content %c at %d\n", buf[pos], pos);
                pos++;
            }
        }
        throw(1);
    }

   public:
    bool isValid(string code) {
        buf = code;
        try {
            int pos = 0;
            read_tag_with_content(pos);
            if (pos != buf.size()) return false;
        } catch (int p) {
            // cout << "check invalid " << p << endl;
            return false;
        }
        return true;
    }
};