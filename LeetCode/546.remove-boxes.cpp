/*
 * [546] Remove Boxes
 *
 * https://leetcode.com/problems/remove-boxes/description/
 *
 * algorithms
 * Hard (35.97%)
 * Total Accepted:    6.1K
 * Total Submissions: 16.9K
 * Testcase Example:  '[1,3,2,2,2,3,4,3,1]'
 *
 * Given several boxes with different colors represented by different positive
 * numbers.
 * You may experience several rounds to remove boxes until there is no box
 * left. Each time you can choose some continuous boxes with the same color
 * (composed of k boxes, k >= 1), remove them and get k*k points.
 * Find the maximum points you can get.
 *
 *
 * Example 1:
 * Input:
 *
 * [1, 3, 2, 2, 2, 3, 4, 3, 1]
 *
 * Output:
 *
 * 23
 *
 * Explanation:
 *
 * [1, 3, 2, 2, 2, 3, 4, 3, 1]
 * ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
 * ----> [1, 3, 3, 3, 1] (1*1=1 points)
 * ----> [1, 1] (3*3=9 points)
 * ----> [] (2*2=4 points)
 *
 *
 *
 * Note:
 * The number of boxes n would not exceed 100.
 *
 *
 */
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// [1,2,2,1,2,2,2,1,1,2,1,1]

class Solution {
    int n;
    vector<int> b;

   public:
    int removeBoxes(vector<int> &boxes) {
        n = boxes.size();
        b = boxes;
        int f[n][n][n + 1], maxk[n][n], g[n][n];
        memset(maxk, 0, sizeof(maxk));
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                for (int k = i; k <= j; k++) {
                    if (boxes[k] == boxes[j]) ++maxk[i][j];
                }
            }
        }
        for (int j = 0; j < n; j++) {
            f[j][j][0] = f[j][j][1] = g[j][j] = 1;
            for (int i = j - 1; i >= 0; i--) {
                f[i][j][0] = f[i][j][1] = g[i][j - 1] + 1;
                g[i][j] = 0;
                for (int k = 1; k <= maxk[i][j]; k++) {
                    if (boxes[j] == boxes[j - 1]) {
                        f[i][j][k] =
                            max(f[i][j][i],
                                f[i][j - 1][k - 1] - (k - 1) * (k - 1) + k * k);
                    } else if (boxes[i] == boxes[j]) {
                        f[i][j][k] =
                            max(f[i][j][k], max(f[i + 1][j][k] + 1,
                                                f[i + 1][j][k - 1] -
                                                    (k - 1) * (k - 1) + k * k));
                    } else {
                        for (int tk = i; tk < j; tk++) {
                            if (boxes[tk] != boxes[j]) continue;
                            if (maxk[i][tk] >= k) {
                                f[i][j][k] =
                                    max(f[i][j][k], f[i][tk][k] + g[tk + 1][j]);
                            }
                            if (maxk[i][tk] >= k - 1) {
                                f[i][j][k] =
                                    max(f[i][j][k],
                                        f[i][tk][k - 1] + g[tk + 1][j - 1] -
                                            (k - 1) * (k - 1) + k * k);
                            }
                        }
                    }
                    g[i][j] = max(g[i][j], f[i][j][k]);
                }
            }
        }
        return g[0][n - 1];
    }
};

int main() {
    vector<int> tmp;
    int buf;
    int n;
    while (cin >> n) {
        tmp.clear();
        for (int i = 0; i < n; i++) {
            cin >> buf;
            tmp.push_back(buf);
        }
        Solution s;
        cout << s.removeBoxes(tmp) << endl;
    }
    return 0;
}