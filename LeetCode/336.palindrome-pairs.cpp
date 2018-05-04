/*
 * [336] Palindrome Pairs
 *
 * https://leetcode.com/problems/palindrome-pairs/description/
 *
 * algorithms
 * Hard (27.20%)
 * Total Accepted:    38.6K
 * Total Submissions: 141.9K
 * Testcase Example:  '["abcd","dcba","lls","s","sssll"]'
 *
 *
 * ⁠   Given a list of unique words, find all pairs of distinct indices (i, j)
 * in the given list, so that the concatenation of the two words, i.e. words[i]
 * + words[j] is a palindrome.
 *
 *
 *
 * ⁠   Example 1:
 * ⁠   Given words = ["bat", "tab", "cat"]
 * ⁠   Return [[0, 1], [1, 0]]
 * ⁠   The palindromes are ["battab", "tabbat"]
 *
 *
 * ⁠   Example 2:
 * ⁠   Given words = ["abcd", "dcba", "lls", "s", "sssll"]
 * ⁠   Return [[0, 1], [1, 0], [3, 2], [2, 4]]
 * ⁠   The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
 *
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
    vector<vector<LL> > vhc, vrhc;
    vector<LL> hpow;
    LL hash_seed;
    void initHash(vector<string> &words) {
        hash_seed = 131313131;
        vhc.clear();
        vrhc.clear();
        hpow.clear();
        int max_len = 0;
        for (int i = 0; i < words.size(); i++) {
            string cur_word = words[i];
            max_len = max(max_len, (int)cur_word.length());
            vector<LL> hc, rhc;
            for (int j = 0; j < cur_word.size(); j++) {
                hc.push_back(j == 0 ? cur_word[j]
                                    : hc.back() * hash_seed + cur_word[j]);
            }
            for (int j = cur_word.size() - 1; j >= 0; j--) {
                rhc.push_back(j == cur_word.size() - 1
                                  ? cur_word[j]
                                  : rhc.back() * hash_seed + cur_word[j]);
            }
            vhc.push_back(hc);
            vrhc.push_back(rhc);
        }
        hpow.push_back(1);
        for (int i = 1; i <= max_len * 2; i++) {
            hpow.push_back(hpow.back() * hash_seed);
        }
    }

    LL getHash(vector<LL> &hc, int l, int r) {
        if (l == 0) return hc[r];
        return hc[r] - hc[l - 1] * hpow[r - l + 1];
    }

    LL getRevHash(vector<LL> &rhc, int l, int r) {
        l = rhc.size() - l - 1;
        r = rhc.size() - r - 1;
        if (r == 0) return rhc[l];
        return rhc[l] - rhc[r - 1] * hpow[l - r + 1];
    }

    LL concatHash(LL h1, int len1, LL h2, int len2) {
        return h1 * hpow[len2] + h2;
    }

    bool checkPalindrome(string &w, int i) {
        if (w.length() == 1) return true;
        LL front_hc, back_hc;
        int len = w.length();
        int mid = w.length() / 2;
        if (w.length() % 2 == 0) {
            front_hc = getHash(vhc[i], 0, mid - 1);
            back_hc = getRevHash(vrhc[i], mid, len - 1);
        } else {
            front_hc = getHash(vhc[i], 0, mid - 1);
            back_hc = getRevHash(vrhc[i], mid + 1, len - 1);
        }
        return front_hc == back_hc;
    }

    bool checkConcat(string &w1, string &w2, int i, int j) {
        int len1 = w1.length(), len2 = w2.length();
        if (len1 == 0) return checkPalindrome(w2, j);
        if (len2 == 0) return checkPalindrome(w1, i);
        LL front_hc, back_hc;
        if ((len1 + len2) % 2 == 0) {
            if (len1 == len2) {
                front_hc = getHash(vhc[i], 0, len1 - 1);
                back_hc = getHash(vrhc[j], 0, len2 - 1);
            } else if (len1 > len2) {
                // "abcddc" "ba"
                int mid = (len1 + len2) / 2;
                front_hc = getHash(vhc[i], 0, mid - 1);
                back_hc = concatHash(getRevHash(vrhc[j], 0, len2 - 1), len2,
                                     getRevHash(vrhc[i], mid, len1 - 1),
                                     len1 - 1 - mid + 1);
            } else {
                // "abc" "ddcba"
                int mid = (len1 + len2) / 2;
                front_hc =
                    concatHash(getHash(vhc[i], 0, len1 - 1), len1,
                               getHash(vhc[j], 0, mid - len1 - 1), mid - len1);
                back_hc = getRevHash(vrhc[j], mid - len1, len2 - 1);
            }
        } else {
            int mid = (len1 + len2) / 2;
            if (len1 > len2) {
                // "abcdc" "ba"
                front_hc = getHash(vhc[i], 0, mid - 1);
                back_hc =
                    len1 == len2 + 1
                        ? getRevHash(vrhc[j], 0, len2 - 1)
                        : concatHash(getRevHash(vrhc[j], 0, len2 - 1), len2,
                                     getRevHash(vrhc[i], mid + 1, len1 - 1),
                                     len1 - 1 - (mid + 1) + 1);
            } else {
                // "ab" "cdcba"
                front_hc = len2 == len1 + 1
                               ? getHash(vhc[i], 0, len1 - 1)
                               : concatHash(getHash(vhc[i], 0, len1 - 1), len1,
                                            getHash(vhc[j], 0, mid - len1 - 1),
                                            mid - len1);
                back_hc = getRevHash(vrhc[j], mid - len1 + 1, len2 - 1);
            }
        }
        return front_hc == back_hc;
    }

    vector<int> make_ans(int i, int j) {
        vector<int> ans;
        ans.push_back(i);
        ans.push_back(j);
        return ans;
    }

   public:
    vector<vector<int> > palindromePairs(vector<string> &words) {
        initHash(words);
        vector<vector<int> > ans;
        for (int i = 0; i < words.size(); i++) {
            string &w1 = words[i];
            for (int j = i + 1; j < words.size(); j++) {
                string &w2 = words[j];
                if (checkConcat(w1, w2, i, j)) {
                    ans.push_back(make_ans(i, j));
                }
                if (checkConcat(w2, w1, j, i)) {
                    ans.push_back(make_ans(j, i));
                }
            }
        }
        return ans;
    }
};
