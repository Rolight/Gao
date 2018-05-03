/*
 * [330] Patching Array
 *
 * https://leetcode.com/problems/patching-array/description/
 *
 * algorithms
 * Hard (32.67%)
 * Total Accepted:    26.4K
 * Total Submissions: 80.8K
 * Testcase Example:  '[1,3]\n6'
 *
 * Given a sorted positive integer array nums and an integer n, add/patch
 * elements to the array such that any number in range [1, n] inclusive can be
 * formed by the sum of some elements in the array. Return the minimum number
 * of patches required.
 *
 *
 * Example 1:
 * nums = [1, 3], n = 6
 * Return 1.
 *
 * Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3,
 * 4.
 * Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3],
 * [2,3], [1,2,3].
 * Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
 * So we only need 1 patch.
 *
 * Example 2:
 * nums = [1, 5, 10], n = 20
 * Return 2.
 * The two patches can be [2, 4].
 *
 * Example 3:
 * nums = [1, 2, 2], n = 5
 * Return 0.
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef long long LL;

/*
    SOLUTION EXPLANATION

   We can maintain a range which indicate that we can form any number in this
   range with current numbers.
   Then we update our range to make it can cover all numbers in [1, n]
   First, We can use number in nums to extend our range. The variable can_reach
   mean the right margin of the current range. For any number in nums, We can
   use this number to extend our range if it samller or equal than can_reach
   + 1.
   Another case is that we can't find any number in nums to extend our range, so
   in this case, we should add new number in nums to extend our range. We just
   add can_reach + 1 to nums.
   Why add can_reach + 1 is optimal? Beacuse the number can_reach + 1 is
   missing, and our range must cover it. So add the number which larger than
   can_reach + 1 is useless. Adding the can_reach + 1 to nums can make our range
   become larger than adding any other number less than can_reach + 1 to nums.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
   public:
    int minPatches(vector<int>& nums, int n) {
        LL can_reach = 0;
        int pos = 0;
        int ans = 0;

        while (can_reach < n) {
            while (pos < nums.size() && nums[pos] <= can_reach + 1) {
                can_reach = can_reach + nums[pos++];
            }
            if (can_reach >= n) break;
            if (pos == nums.size() || nums[pos] != can_reach + 1) {
                // cannot reach next number, add it and update can_reach
                ++ans;
                can_reach = (can_reach + 1) + can_reach;
            }
        }

        return ans;
    }
};
