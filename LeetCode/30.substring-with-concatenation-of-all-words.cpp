/*
 * [30] Substring with Concatenation of All Words
 *
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * algorithms
 * Hard (22.26%)
 * Total Accepted:    94.2K
 * Total Submissions: 422.9K
 * Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
 *
 *
 * You are given a string, s, and a list of words, words, that are all of the
 * same length. Find all starting indices of substring(s) in s that is a
 * concatenation of each word in words exactly once and without any intervening
 * characters.
 *
 *
 *
 * For example, given:
 * s: "barfoothefoobarman"
 * words: ["foo", "bar"]
 *
 *
 *
 * You should return the indices: [0,9].
 * (order does not matter).
 *
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
  std::map<string, int> mp, maxv;
  int word_count, bad_count;

  void init(vector<string> words) {
    mp.clear();
    maxv.clear();
    word_count = bad_count = 0;
    for (vector<string>::iterator iter = words.begin(); iter != words.end();
         ++iter) {
      maxv[*iter] += 1;
      mp[*iter] = 0;
    }
  }

  void add(string &word) {
    if (mp.count(word) == 0)
      return;
    int cur_val = mp[word], max_val = maxv[word];
    if (cur_val == max_val) {
      bad_count += 1;
    } else {
      word_count += 1;
    }
    mp[word] = cur_val + 1;
  }

  void del(string &word) {
    if (mp.count(word) == 0)
      return;
    int cur_val = mp[word], max_val = maxv[word];
    if (cur_val == max_val + 1) {
      bad_count -= 1;
    } else {
      word_count -= 1;
    }
    mp[word] = cur_val - 1;
  }

  vector<int> findSubstring(string s, vector<string> &words) {
    vector<int> answer;
    int word_length = words[0].length(), word_count = words.size();
    for (int init_pos = 0; init_pos < word_length; init_pos++) {
      init(words);
      for (int i = init_pos; i + word_length <= s.length(); i += word_length) {
        string cur_word = string(s.begin() + i, s.begin() + i + word_length);
        add(cur_word);
        if (i >= word_count * word_length) {
          string prev_word =
              string(s.begin() + i - word_count * word_length,
                     s.begin() + i - word_count * word_length + word_length);
          del(prev_word);
        }
        if (word_count == this->word_count) {
          answer.push_back(i - word_count * word_length + word_length);
        }
      }
    }
    std::sort(answer.begin(), answer.end());
    return answer;
  }
};
