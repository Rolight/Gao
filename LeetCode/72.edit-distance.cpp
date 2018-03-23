/*
 * [72] Edit Distance
 *
 * https://leetcode.com/problems/edit-distance/description/
 *
 * algorithms
 * Hard (32.46%)
 * Total Accepted:    112.3K
 * Total Submissions: 345.8K
 * Testcase Example:  '""\n""'
 *
 *
 * Given two words word1 and word2, find the minimum number of steps required
 * to convert word1 to word2. (each operation is counted as 1 step.)
 *
 *
 *
 * You have the following 3 operations permitted on a word:
 *
 *
 *
 * a) Insert a character
 * b) Delete a character
 * c) Replace a character
 *
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::min;
using std::string;
using std::vector;

class Solution {
    void initVector(int n, int m, vector<vector<int> > &f, int init_val = 0) {
        std::cout << "init " << n << " " << m << std::endl;
        f.clear();
        for (int i = 0; i < n; i++) {
            vector<int> tmp;
            f.push_back(tmp);
            for (int j = 0; j < m; j++) {
                f[i].push_back(init_val);
            }
        }
    }

   public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int> > f;
        initVector(n + 1, m + 1, f, 1e8);
        f[0][0] = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) continue;
                // if i == 0  or  j == 0 we can only insert a character
                if (i == 0) {
                    f[i][j] = f[i][j - 1] + 1;
                } else if (j == 0) {
                    f[i][j] = f[i - 1][j] + 1;
                } else {
                    if (word1[i - 1] == word2[j - 1]) {
                        f[i][j] = f[i - 1][j - 1];
                    } else {
                        // a a b
                        // a a c
                        // replace a character
                        f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
                        // delete a character
                        f[i][j] =
                            min(f[i][j], min(f[i][j - 1] + 1, f[i - 1][j] + 1));
                        // insert a character
                    }
                }
            }
        }
        return f[n][m];
    }
};

int main() {
    string a, b;
    while (std::cin >> a >> b) {
        Solution s;
        std::cout << s.minDistance(a, b) << std::endl;
    }
    return 0;
}