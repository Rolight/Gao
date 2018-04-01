/*
 * [124] Binary Tree Maximum Path Sum
 *
 * https://leetcode.com/problems/binary-tree-maximum-path-sum/description/
 *
 * algorithms
 * Hard (27.12%)
 * Total Accepted:    124K
 * Total Submissions: 457.4K
 * Testcase Example:  '[1,2,3]'
 *
 *
 * Given a binary tree, find the maximum path sum.
 *
 *
 * For this problem, a path is defined as any sequence of nodes from some
 * starting node to any node in the tree along the parent-child connections.
 * The path must contain at least one node and does not need to go through the
 * root.
 *
 *
 * For example:
 * Given the below binary tree,
 *
 * ⁠      1
 * ⁠     / \
 * ⁠    2   3
 *
 *
 *
 * Return 6.
 *
 */
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */

import static java.lang.Math.*;

public class TreeNode {
    int val;
    TreeNode left, right;
    TreeNode(int x) {
        val = x;
    }
}

class Solution {
    public int dfs(TreeNode cur, int[] ans) {
        int left_val = 0, right_val = 0;
        if (cur.left != null) {
            left_val = max(dfs(cur.left, ans), left_val);
        }
        if (cur.right != null) {
            right_val = max(dfs(cur.right, ans), right_val);
        }
        int cur_val = max(left_val, right_val) + cur.val;
        ans[0] = max(ans[0], left_val + right_val + cur.val);
        return cur_val;
    }
    public int maxPathSum(TreeNode root) {
        int[] ans = new int[1];
        // -inf
        ans[0] = -100000000;
        dfs(root, ans);
        return ans[0];
    }
}
