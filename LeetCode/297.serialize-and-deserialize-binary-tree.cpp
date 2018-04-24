/*
 * [297] Serialize and Deserialize Binary Tree
 *
 * https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/
 *
 * algorithms
 * Hard (35.06%)
 * Total Accepted:    102.2K
 * Total Submissions: 290.6K
 * Testcase Example:  '[1,2,3,null,null,4,5]'
 *
 * Serialization is the process of converting a data structure or object into a
 * sequence of bits so that it can be stored in a file or memory buffer, or
 * transmitted across a network connection link to be reconstructed later in
 * the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no
 * restriction on how your serialization/deserialization algorithm should work.
 * You just need to ensure that a binary tree can be serialized to a string and
 * this string can be deserialized to the original tree structure.
 *
 * For example, you may serialize the following tree
 *
 *
 * ⁠   1
 * ⁠  / \
 * ⁠ 2   3
 * ⁠    / \
 * ⁠   4   5
 *
 *
 * as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a
 * binary tree. You do not necessarily need to follow this format, so please be
 * creative and come up with different approaches yourself.
 *
 *
 *
 * Note: Do not use class member/global/static variables to store states. Your
 * serialize and deserialize algorithms should be stateless.
 *
 * Credits:
 * Special thanks to @Louis1992 for adding this problem and creating all test
 * cases.
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
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
    int atoi(string& buf) {
        stringstream sin(buf);
        int ret;
        sin >> ret;
        return ret;
    }

    string itoa(int val) {
        stringstream sout;
        sout << val;
        return sout.str();
    }

   public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == NULL) return "[]";
        queue<TreeNode*> q;
        q.push(root);
        string ret = "[" + itoa(root->val);
        while (!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();
            ret += cur->left == NULL ? ",null" : "," + itoa(cur->left->val);
            ret += cur->right == NULL ? ",null" : "," + itoa(cur->right->val);
            if (cur->left != NULL) q.push(cur->left);
            if (cur->right != NULL) q.push(cur->right);
        }
        ret += "]";
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.length() == 2) return NULL;
        data = data.substr(1, data.length() - 2);
        string buf = "";
        int pos = 0;
        while (pos < data.length() && data[pos] != ',') {
            buf += data[pos++];
        }
        pos++;
        TreeNode* root = new TreeNode(atoi(buf));
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();
            string lval = "", rval = "";
            while (pos < data.length() && data[pos] != ',') {
                lval += data[pos++];
            }
            pos++;
            while (pos < data.length() && data[pos] != ',') {
                rval += data[pos++];
            }
            pos++;
            if (lval != "null") {
                TreeNode* newNode = new TreeNode(atoi(lval));
                cur->left = newNode;
                q.push(newNode);
            }
            if (rval != "null") {
                TreeNode* newNode = new TreeNode(atoi(rval));
                cur->right = newNode;
                q.push(newNode);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
