/*
 * [164] Maximum Gap
 *
 * https://leetcode.com/problems/maximum-gap/description/
 *
 * algorithms
 * Hard (30.02%)
 * Total Accepted:    55.4K
 * Total Submissions: 184.2K
 * Testcase Example:  '[]'
 *
 * Given an unsorted array, find the maximum difference between the successive
 * elements in its sorted form.
 *
 * Try to solve it in linear time/space.
 *
 * Return 0 if the array contains less than 2 elements.
 *
 * You may assume all elements in the array are non-negative integers and fit
 * in the 32-bit signed integer range.
 *
 * Credits:Special thanks to @porker2008 for adding this problem and creating
 * all test cases.
 */
import static java.lang.Math.*;

class Solution {
    class TreeNode {
        public long min_val, max_val;
        public TreeNode[] ch;
        TreeNode() {
            ch = new TreeNode[2];
            ch[0] = ch[1] = null;
            max_val = -1;
            min_val = 1L << 33;
        }
    }
    void insert(long val, TreeNode root) {
        TreeNode now = root;
        for (long i = 32; i >= 0; i--) {
            int cur = 0;
            if ((val & (1L << i)) != 0) {
                cur = 1;
            }
            now.max_val = max(now.max_val, val);
            now.min_val = min(now.min_val, val);
            if (now.ch[cur] == null) {
                now.ch[cur] = new TreeNode();
            }
            now = now.ch[cur];
        }
        now.max_val = max(now.max_val, val);
        now.min_val = min(now.min_val, val);
    }
    long query(long val, TreeNode root) {
        TreeNode now = root;
        long pred = -1, nxt = -1;
        for (int i = 32; i >= 0; i--) {
            int cur = 0;
            if ((val & (1L << i)) != 0) {
                cur = 1;
            }
            if (cur == 0 && now.ch[1] != null) {
                if (nxt == -1 || now.ch[1].min_val < nxt) {
                    nxt = now.ch[1].min_val;
                }
            }
            if (cur == 1 && now.ch[0] != null) {
                if (pred == -1 || now.ch[0].max_val > pred) {
                    pred = now.ch[0].max_val;
                }
            }
            now = now.ch[cur];
        }
        long gap = 0;
        if (pred != -1) {
            gap = max(gap, val - pred);
        }
        if (nxt != -1) {
            gap = max(gap, nxt - val);
        }
        return gap;
    }
    public int maximumGap(int[] nums) {
        if (nums.length < 2)
            return 0;
        TreeNode trie = new TreeNode();
        long ans = 0;
        for (int i = 0; i < nums.length; i++) {
            insert(nums[i], trie);
        }
        for (int i = 0; i < nums.length; i++) {
            long ret = query(nums[i], trie);
            ans = max(ret, ans);
        }
        return (int) ans;
    }
}
