/*
 * [99] Recover Binary Search Tree
 *
 * https://leetcode.com/problems/recover-binary-search-tree/description/
 *
 * algorithms
 * Hard (30.88%)
 * Total Accepted:    86.8K
 * Total Submissions: 280K
 * Testcase Example:  '[0,1]'
 *
 *
 * Two elements of a binary search tree (BST) are swapped by mistake.
 *
 * Recover the tree without changing its structure.
 *
 *
 * Note:
 * A solution using O(n) space is pretty straight forward. Could you devise a
 * constant space solution?
 *
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <algorithm>

using std::swap;

class Solution {
   public:
    void traversal(TreeNode *cur, TreeNode *&bad1, TreeNode *&bad2,
                   TreeNode *&prev) {
        if (prev == NULL) {
            prev = cur;
            return;
        }
        if (cur->val < prev->val) {
            if (bad1 == NULL) {
                bad1 = prev;
                bad2 = cur;
            } else {
                bad2 = cur;
            }
        }
        prev = cur;
    }

    void recoverTree(TreeNode *root) {
        TreeNode *bad1 = NULL, *bad2 = NULL;
        TreeNode *prev = NULL, *cur = root;
        // Morris Traversal
        while (cur != NULL) {
            if (cur->left == NULL) {
                traversal(cur, bad1, bad2, prev);
                cur = cur->right;
            } else {
                TreeNode *pred = cur->left;
                while (pred->right != NULL && pred->right != cur)
                    pred = pred->right;
                // thread
                if (pred->right == NULL) {
                    pred->right = cur;
                    cur = cur->left;
                } else {
                    pred->right = NULL;
                    traversal(cur, bad1, bad2, prev);
                    cur = cur->right;
                }
            }
        }
        swap(bad1->val, bad2->val);
    }
};