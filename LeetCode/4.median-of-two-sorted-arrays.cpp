/*
 * [4] Median of Two Sorted Arrays
 *
 * https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (22.83%)
 * Total Accepted:    237.7K
 * Total Submissions: 1M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 *
 * Example 1:
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 *
 *
 * Example 2:
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 *
 *
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>

using std::vector;

double eps = 1e-5;

class Solution {
public:
  int findKthInOne(vector<int> &nums1, vector<int> &nums2, int k) {
    if (nums2.size() == 0) {
      return nums1[k - 1];
    }
    int l = 0, r = nums1.size() - 1;
    int ans = -1;
    while (l <= r && ans == -1) {
      int pos1 = (l + r) / 2;
      if (pos1 >= k) {
        r = pos1 - 1;
        continue;
      }

      int pos2 = k - 1 - pos1, v = nums1[pos1];
      if (pos2 == 0) {
        if (nums2[0] >= v) {
          ans = v;
        } else {
          r = pos1 - 1;
        }
      } else if (pos2 > nums2.size()) {
        l = pos1 + 1;
      } else if (pos2 == nums2.size()) {
        if (v >= nums2[nums2.size() - 1]) {
          ans = v;
        } else {
          l = pos1 + 1;
        }
      } else {
        assert(pos2 > 0 && pos2 < nums2.size());
        if (nums2[pos2 - 1] <= v && nums2[pos2] >= v) {
          ans = v;
        } else if (nums2[pos2 - 1] > v) {
          l = pos1 + 1;
        } else if (nums2[pos2] < v) {
          r = pos1 - 1;
        }
      }
    }
    return ans;
  }

  int findKth(vector<int> &nums1, vector<int> &nums2, int k) {
    int ans = findKthInOne(nums1, nums2, k);
    if (ans == -1) {
      ans = findKthInOne(nums2, nums1, k);
    }
    return ans;
  }

  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int len1 = nums1.size(), len2 = nums2.size();
    printf("len1 = %d, len2 = %d\n", len1, len2);
    double ans;
    if ((len1 + len2) % 2 == 1) {
      int k = (len1 + len2 + 1) / 2;
      ans = findKth(nums1, nums2, k);
    } else {
      int k1 = (len1 + len2) / 2;
      double ans1 = findKth(nums1, nums2, k1),
             ans2 = findKth(nums1, nums2, k1 + 1);
      printf("ans1 = %.2f, ans2 = %.2f\n", ans1, ans2);
      ans = (ans1 + ans2) / 2;
    }
    return ans;
  }
};