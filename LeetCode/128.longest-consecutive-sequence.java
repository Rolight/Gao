/*
 * [128] Longest Consecutive Sequence
 *
 * https://leetcode.com/problems/longest-consecutive-sequence/description/
 *
 * algorithms
 * Hard (38.19%)
 * Total Accepted:    137.3K
 * Total Submissions: 359.3K
 * Testcase Example:  '[100,4,200,1,3,2]'
 *
 *
 * Given an unsorted array of integers, find the length of the longest
 * consecutive elements sequence.
 *
 *
 * For example,
 * Given [100, 4, 200, 1, 3, 2],
 * The longest consecutive elements sequence is [1, 2, 3, 4]. Return its
 * length: 4.
 *
 *
 * Your algorithm should run in O(n) complexity.
 *
 */
import java.util.*;

class Solution {
    class Node {
        public Node father;
        public int value;

        public Node() {
            this.father = this;
            this.value = 1;
        }
    }

    HashMap<Integer, Node> mset;

    public Node getFather(Node cur) {
        if (cur.father == cur) {
            return cur;
        } else {
            Node ret = getFather(cur.father);
            cur.father = ret;
            return ret;
        }
    }

    public int longestConsecutive(int[] nums) {
        int ans = 0;
        mset = new HashMap<Integer, Node>();
        for (int i = 0; i < nums.length; i++) {
            int cur = nums[i];
            if (mset.get(cur) != null) {
                continue;
            }
            Node left = mset.get(cur - 1), right = mset.get(cur + 1);
            Node curNode = new Node();
            mset.put(cur, curNode);
            if (left == null && right != null) {
                right = getFather(right);
                right.father = curNode;
                curNode.value = right.value + 1;
            } else if (right == null && left != null) {
                left = getFather(left);
                curNode.father = left;
                left.value += 1;
            } else if (left != null && right != null) {
                right = getFather(right);
                left = getFather(left);
                int new_value = left.value + right.value + 1;
                curNode.father = left;
                right.father = left;
                left.value = new_value;
            }
            int curValue = getFather(curNode).value;
            if (curValue > ans) {
                ans = curValue;
            }
        }
        return ans;
    }
}