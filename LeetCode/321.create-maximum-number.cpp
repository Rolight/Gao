/*
 * [321] Create Maximum Number
 *
 * https://leetcode.com/problems/create-maximum-number/description/
 *
 * algorithms
 * Hard (24.80%)
 * Total Accepted:    23.4K
 * Total Submissions: 94.1K
 * Testcase Example:  '[3,4,6,5]\n[9,1,2,5,8,3]\n5'
 *
 *
 * ⁠   Given two arrays of length m and n with digits 0-9 representing two
 * numbers.
 * ⁠   Create the maximum number of length k  from digits of the two. The
 * relative order of the digits
 * ⁠   from the same array must be preserved. Return an array of the k digits.
 * You should try to optimize your time and space complexity.
 *
 *
 *
 * ⁠   Example 1:
 *
 *
 * ⁠   nums1 = [3, 4, 6, 5]
 * ⁠   nums2 = [9, 1, 2, 5, 8, 3]
 * ⁠   k = 5
 * ⁠   return [9, 8, 6, 5, 3]
 *
 *
 * ⁠   Example 2:
 *
 *
 * ⁠   nums1 = [6, 7]
 * ⁠   nums2 = [6, 0, 4]
 * ⁠   k = 5
 * ⁠   return [6, 7, 6, 0, 4]
 *
 *
 * ⁠   Example 3:
 *
 *
 * ⁠   nums1 = [3, 9]
 * ⁠   nums2 = [8, 9]
 * ⁠   k = 3
 * ⁠   return [9, 8, 9]
 *
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<int> cur_ans;
    list<int> a1, a2;
    void merge(list<int>& a, list<int>& b) {
        cur_ans.clear();
        list<int>::iterator pa = a.begin(), pb = b.begin();
        for (int i = 0; i < a.size() + b.size(); i++) {
            if (pa == a.end()) {
                cur_ans.push_back(*pb);
                ++pb;
            } else if (pb == b.end()) {
                cur_ans.push_back(*pa);
                ++pa;
            } else {
                list<int>::iterator tpa = pa, tpb = pb;
                while (tpa != a.end() && tpb != b.end() && *tpa == *tpb) {
                    ++tpa;
                    ++tpb;
                }
                if (tpa == a.end()) {
                    cur_ans.push_back(*pb);
                    ++pb;
                } else if (tpb == b.end()) {
                    cur_ans.push_back(*pa);
                    ++pa;
                } else if (*tpa > *tpb) {
                    cur_ans.push_back(*pa);
                    ++pa;
                } else {
                    cur_ans.push_back(*pb);
                    ++pb;
                }
            }
        }
    }

    void getMax(vector<int>& nums, int k, list<int>& ans) {
        ans.clear();
        k = nums.size() - k;
        if (k == nums.size()) return;
        for (int i = 0; i < nums.size(); i++) ans.push_back(nums[i]);
        for (int i = 0; i < k; i++) {
            list<int>::iterator iter;
            for (iter = ans.begin(); next(iter) != ans.end(); ++iter) {
                if (*iter < *(next(iter))) {
                    break;
                }
            }
            ans.erase(iter);
        }
    }

   public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> ans;
        for (int i = 0; i <= k && i <= nums1.size(); i++) {
            int j = k - i;
            if (j > nums2.size()) continue;
            getMax(nums1, i, a1);
            getMax(nums2, j, a2);
            merge(a1, a2);
            if (ans.size() == 0)
                ans = cur_ans;
            else {
                for (int tt = 0; tt < ans.size(); tt++) {
                    if (cur_ans[tt] > ans[tt]) {
                        ans = cur_ans;
                        break;
                    }
                    if (cur_ans[tt] != ans[tt]) break;
                }
            }
        }
        return ans;
    }
};

int main() {
    int n, m, k;
    vector<int> nums1, nums2;
    while (cin >> n >> m >> k) {
        nums1.clear();
        nums2.clear();
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
            nums1.push_back(tmp);
        }
        for (int i = 0; i < m; i++) {
            int tmp;
            cin >> tmp;
            nums2.push_back(tmp);
        }
        Solution s;
        vector<int> ans = s.maxNumber(nums1, nums2, k);
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}