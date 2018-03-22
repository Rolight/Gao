/*
 * [68] Text Justification
 *
 * https://leetcode.com/problems/text-justification/description/
 *
 * algorithms
 * Hard (19.91%)
 * Total Accepted:    68.7K
 * Total Submissions: 344.5K
 * Testcase Example:  '[""]\n0'
 *
 *
 * Given an array of words and a length L, format the text such that each line
 * has exactly L characters and is fully (left and right) justified.
 * ⁠
 *
 *
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly L characters.
 *
 *
 *
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line do not divide evenly between words, the empty
 * slots on the left will be assigned more spaces than the slots on the
 * right.
 *
 *
 *
 * For the last line of text, it should be left justified and no extra space is
 * inserted between words.
 *
 *
 *
 * For example,
 * words: ["This", "is", "an", "example", "of", "text", "justification."]
 * L: 16.
 *
 *
 *
 * Return the formatted lines as:
 *
 * [
 * ⁠  "This    is    an",
 * ⁠  "example  of text",
 * ⁠  "justification.  "
 * ]
 *
 *
 *
 *
 * Note: Each word is guaranteed not to exceed L in length.
 *
 *
 *
 * click to show corner cases.
 *
 * Corner Cases:
 *
 *
 * A line other than the last line might contain only one word. What should you
 * do in this case?
 * In this case, that line should be left-justified.
 *
 *
 */

#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
   public:
    string justifyOneLine(vector<string>& words, int maxWidth,
                          bool last = false) {
        int num_words = words.size(), total_len = 0;
        string ret = "";
        for (int i = 0; i < num_words; i++) {
            total_len += words[i].length();
        }
        int total_empty_count = maxWidth - total_len;
        for (int i = 0; i < num_words; i++) {
            if (i > 0) {
                if (last) {
                    ret += ' ';
                } else {
                    int spaces = total_empty_count / (num_words - 1);
                    if (i <= total_empty_count % (num_words - 1)) spaces++;
                    while (spaces--) ret += ' ';
                }
            }
            ret += words[i];
        }
        while (ret.length() < maxWidth) ret += ' ';
        return ret;
    }
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        if (maxWidth == 0) return words;
        vector<string> buf, ret;
        int cur_length = 0, m = words.size();
        for (int i = 0; i < m; i++) {
            if (buf.size() > 0 &&
                cur_length + words[i].length() + buf.size() > maxWidth) {
                ret.push_back(justifyOneLine(buf, maxWidth));
                buf.clear();
                cur_length = 0;
            }
            cur_length += words[i].length();
            buf.push_back(words[i]);
        }
        ret.push_back(justifyOneLine(buf, maxWidth, true));
        return ret;
    }
};
