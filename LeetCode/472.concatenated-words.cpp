/*
 * [472] Concatenated Words
 *
 * https://leetcode.com/problems/concatenated-words/description/
 *
 * algorithms
 * Hard (30.93%)
 * Total Accepted:    11.9K
 * Total Submissions: 38.3K
 * Testcase Example:
 * '["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]'
 *
 * Given a list of words (without duplicates), please write a program that
 * returns all concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at
 * least two shorter words in the given array.
 *
 * Example:
 *
 * Input:
 * ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
 *
 * Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
 *
 * Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
 * "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; "ratcatdogcat"
 * can be concatenated by "rat", "cat", "dog" and "cat".
 *
 *
 *
 * Note:
 *
 * The number of elements of the given array will not exceed 10,000
 * The length sum of elements in the given array will not exceed 600,000.
 * All the input string will only include lower case letters.
 * The returned elements order does not matter.
 *
 *
 */

// MLE

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Solution {
    struct TrieNode {
        TrieNode *next[26];
        TrieNode *fail;
        int length;
        bool exists;

        TrieNode() : exists(false), fail(0) { memset(next, 0, sizeof(next)); }
    };

    struct AC_automation {
        TrieNode *trie_root;
        vector<TrieNode *> node_pool;
        int sigma_size;

        TrieNode *newNode() {
            node_pool.push_back(new TrieNode());
            return node_pool.back();
        }

        AC_automation() : sigma_size(26) {
            trie_root = newNode();
            trie_root->fail = trie_root;
        }

        ~AC_automation() {
            for (int i = 0; i < node_pool.size(); i++) {
                // cout << "delete " << i << endl;
                delete node_pool[i];
            }
        }

        TrieNode *insert(string &str) {
            TrieNode *u = trie_root;
            for (int i = 0; i < str.length(); i++) {
                int cur_id = str[i] - 'a';
                if (u->next[cur_id] == 0) {
                    u->next[cur_id] = newNode();
                }
                u = u->next[cur_id];
            }
            u->length = str.length();
            u->exists = true;
            return u;
        }

        void construct() {
            queue<TrieNode *> q;
            for (int i = 0; i < sigma_size; i++) {
                if (trie_root->next[i] != 0) {
                    q.push(trie_root->next[i]);
                    trie_root->next[i]->fail = trie_root;
                } else
                    trie_root->next[i] = trie_root;
            }

            // bfs to construct ac_automation
            while (!q.empty()) {
                TrieNode *u = q.front();
                q.pop();
                for (int i = 0; i < sigma_size; i++) {
                    if (u->next[i] == 0) {
                        u->next[i] = u->fail->next[i];
                    } else {
                        u->next[i]->fail = u->fail->next[i];
                        q.push(u->next[i]);
                    }
                }
            }
        }

        bool gao(string &str, TrieNode *node) {
            // 0: non-vis, 1: first-vis, 2: after first vis
            vector<int> vis(str.length() + 1, 0);
            TrieNode *u = trie_root;
            for (int i = 1; i <= str.length(); i++) {
                int cur_id = str[i - 1] - 'a';
                u = u->next[cur_id];
                if (u == NULL) u = trie_root;
                for (TrieNode *tmp = u; tmp != trie_root; tmp = tmp->fail) {
                    if (tmp->exists) {
                        if (i - tmp->length == 0 && vis[i] == 0)
                            vis[i] = 1;
                        else if (vis[i - tmp->length] != 0)
                            vis[i] = 2;
                    }
                }
            }
            return vis[str.length()] == 2;
        }
    };

   public:
    vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
        AC_automation *ac = new AC_automation();
        vector<TrieNode *> nodes;
        vector<string> ans;
        vector<int> ans_id;
        for (int i = 0; i < words.size(); i++) {
            TrieNode *node = ac->insert(words[i]);
            nodes.push_back(node);
        }
        ac->construct();
        for (int i = 0; i < words.size(); i++) {
            if (ac->gao(words[i], nodes[i])) {
                ans_id.push_back(i);
            }
        }
        delete ac;
        for (int i = 0; i < ans_id.size(); i++) {
            ans.push_back(words[ans_id[i]]);
        }
        return ans;
    }
};