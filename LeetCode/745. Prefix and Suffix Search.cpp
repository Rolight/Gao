#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned long long LL;

const LL hash_seed = 131313131LL;

class WordFilter {
    LL getHash(string s) {
        LL ret = 0;
        for (int i = 0; i < s.length(); i++) {
            ret = ret * hash_seed + s[i];
        }
        return ret;
    }

    vector<LL> getAllhash(string s) {
        int len = s.length();
        vector<LL> ret;
        ret.push_back(getHash(s));
        ret.push_back(getHash("."));
        ret.push_back(getHash("." + s));
        ret.push_back(getHash(s + "."));
        for (int i = 1; i < len; i++) {
            for (int llen = 0; llen + i <= len; llen++) {
                LL cur_val = 0;
                // printf("add: ");
                for (int j = 0; j < len; j++) {
                    if (j == llen) {
                        // putchar('.');
                        cur_val = cur_val * hash_seed + '.';
                    }
                    if (j >= llen && j < llen + i) continue;
                    putchar(s[j]);
                    cur_val = cur_val * hash_seed + s[j];
                }
                ret.push_back(cur_val);
                // puts("");
            }
        }
        return ret;
    }

   public:
    unordered_map<LL, int> dict;
    unordered_map<LL, int> dict1;
    WordFilter(vector<string> words) {
        dict.clear();
        dict1.clear();
        for (int i = 0; i < words.size(); i++) {
            vector<LL> all_hash = getAllhash(words[i]);
            dict1[all_hash[0]] = max(dict1[all_hash[0]], i);
            for (int j = 1; j < all_hash.size(); j++) {
                dict[all_hash[j]] = max(dict[all_hash[j]], i);
            }
        }
    }

    int f(string prefix, string suffix) {
        // printf("query %s %s\n", prefix.c_str(), suffix.c_str());
        LL hh = getHash(prefix + '.' + suffix);
        // printf("try %s\n", (prefix + '.' + suffix).c_str());
        int ret = -1;
        if (dict.count(hh) != 0) {
            ret = max(ret, dict[hh]);
        }
        int len = min(prefix.length(), suffix.length());
        for (int i = 0; i <= len; i++) {
            bool same = true;
            for (int j = 0; j < i; j++) {
                if (prefix[prefix.length() - i + j] != suffix[j]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                string tar = prefix.substr(0, prefix.length() - i) + suffix;
                // printf("try %s\n", tar.c_str());
                LL thash = getHash(tar);
                if (dict1.count(thash) != 0) {
                    ret = max(ret, dict1[thash]);
                }
            }
        }
        return ret;
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter obj = new WordFilter(words);
 * int param_1 = obj.f(prefix,suffix);
 */