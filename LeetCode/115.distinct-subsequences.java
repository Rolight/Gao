/*
 * [115] Distinct Subsequences
 *
 * https://leetcode.com/problems/distinct-subsequences/description/
 *
 * algorithms
 * Hard (32.14%)
 * Total Accepted:    81.8K
 * Total Submissions: 254K
 * Testcase Example:  '""\n"a"'
 *
 *
 * Given a string S and a string T, count the number of distinct subsequences
 * of S which equals T.
 *
 *
 *
 * A subsequence of a string is a new string which is formed from the original
 * string by deleting some (can be none) of the characters without disturbing
 * the relative positions of the remaining characters. (ie, "ACE" is a
 * subsequence of "ABCDE" while "AEC" is not).
 *
 *
 *
 * Here is an example:
 * S = "rabbbit", T = "rabbit"
 *
 *
 * Return 3.
 *
 */
class Solution {
    public int numDistinct(String s, String t) {
        int f[][] = new int[s.length() + 1][t.length() + 1];
        for (int i = 0; i <= s.length(); i++) f[i][0] = 1;
        for (int j = 1; j <= t.length(); j++) {
            for (int i = 1; i <= s.length(); i++) {
                f[i][j] = f[i - 1][j];
                if (s.charAt(i - 1) == t.charAt(j - 1)) {
                    f[i][j] += f[i - 1][j - 1];
                }
            }
        }
        return f[s.length()][t.length()];
    }
}
