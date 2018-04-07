import javax.sound.sampled.ReverbType;

/*
 * [145] Binary Tree Postorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-postorder-traversal/description/
 *
 * algorithms
 * Hard (42.08%)
 * Total Accepted:    175.5K
 * Total Submissions: 416.2K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the postorder traversal of its nodes' values.
 *
 * For example:
 * Given binary tree [1,null,2,3],
 *
 *
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠   /
 * ⁠  3
 *
 *
 *
 *
 * return [3,2,1].
 *
 * Note: Recursive solution is trivial, could you do it iteratively?
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
class Solution {
    public void revTraversal(TreeNode from, TreeNode to, List<Integer> ans) {
        if (from == to) {
            ans.add(from.val);
            return;
        }
        TreeNode prev = from, cur = from.right, tmp;
        while (prev != to) {
            tmp = cur.right;
            cur.right = prev;
            prev = cur;
            cur = tmp;
        }
        cur = to;
        while (true) {
            ans.add(cur.val);
            if (cur == from) {
                break;
            }

            cur = cur.right;
        }

        prev = to;
        cur = prev.right;
        while (prev != to) {
            tmp = cur.right;
            cur.right = prev;
            prev = cur;
            cur = tmp;
        }
    }

    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<Integer>();

        // Morris Traversal
        TreeNode dump = new TreeNode(-1);
        dump.left = root;
        dump.right = null;

        TreeNode cur = dump;
        while (cur != null) {
            System.out.println(cur.val);
            if (cur.left == null) {
                cur = cur.right;
            } else {
                // find previous node in middle traversal
                TreeNode node = cur.left;
                while (node.right != null && node.right != cur) {
                    node = node.right;
                }
                if (node.right == null) {
                    node.right = cur;
                    cur = cur.left;
                } else if (node.right == cur) {
                    node.right = null;
                    // reverse from -> to
                    revTraversal(cur.left, node, ans);
                    cur = cur.right;
                }
            }
        }
        return ans;
    }
}