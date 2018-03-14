/*
 * [41] First Missing Positive
 *
 * https://leetcode.com/problems/first-missing-positive/description/
 *
 * algorithms
 * Hard (25.82%)
 * Total Accepted:    127K
 * Total Submissions: 491.9K
 * Testcase Example:  '[1,2,0]'
 *
 *
 * Given an unsorted integer array, find the first missing positive integer.
 *
 *
 *
 * For example,
 * Given [1,2,0] return 3,
 * and [3,4,-1,1] return 2.
 *
 *
 *
 * Your algorithm should run in O(n) time and uses constant space.
 *
 */

/*
  First, Let's remove negative numbers in the array, get parr.
  Then, assuming parr's length is l, the missing number must in range(1, l+1),
  therefore we just need hash the number in range(1, l+1), it cost a constant
  space O(N).
*/

#include <cstdlib>
#include <vector>

using std::vector;

class Solution {
public:
  int firstMissingPositive(vector<int> &nums) {
    vector<int> pnums;
    // remove negative numbers
    for (vector<int>::iterator iter = nums.begin(); iter != nums.end();
         ++iter) {
      if (*iter > 0) {
        pnums.push_back(*iter);
      }
    }
    // init hash table
    int hash_size = (int)pnums.size() + 2;
    int *hash = new int[hash_size];
    memset(hash, 0, sizeof(int) * hash_size);
    for (vector<int>::iterator iter = pnums.begin(); iter != pnums.end();
         ++iter) {
      if (*iter < hash_size) {
        hash[*iter] = 1;
      }
    }
    int ans = 1;
    for (; ans < hash_size && hash[ans] == 1; ans++)
      ;
    return ans;
  }
};
