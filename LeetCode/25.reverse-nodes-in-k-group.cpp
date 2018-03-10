/*
 * [25] Reverse Nodes in k-Group
 *
 * https://leetcode.com/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (31.40%)
 * Total Accepted:    120.3K
 * Total Submissions: 382.7K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 *
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes in the end should remain as it is.
 *
 * You may not alter the values in the nodes, only nodes itself may be
 * changed.
 *
 * Only constant memory is allowed.
 *
 * For example,
 * Given this linked list: 1->2->3->4->5
 *
 * For k = 2, you should return: 2->1->4->3->5
 *
 * For k = 3, you should return: 3->2->1->4->5
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  void reverse(ListNode *head, ListNode *tail) {
    ListNode *prev = tail->next, *tmp;
    do {
      tmp = head->next;
      head->next = prev;
      prev = head;
      head = tmp;
    } while (prev != tail);
  }

  ListNode *reverseKGroup(ListNode *head, int k) {
    int step = 0;
    ListNode *cur_head = head, *cur_tail = NULL, *cur = head;
    ListNode *ret_head = NULL, *ret_tail = NULL;
    ListNode *tmp;
    while (cur != NULL) {
      step += 1;
      cur_tail = cur;
      cur = cur->next;

      if (step % k == 0) {
        reverse(cur_head, cur_tail);
        if (ret_head == NULL) {
          ret_head = cur_tail;
          ret_tail = cur_head;
        } else {
          ret_tail->next = cur_tail;
          ret_tail = cur_head;
        }
        cur_head = cur;
        cur_tail = NULL;
      }
    }

    if (ret_head == NULL) {
      return head;
    }
    return ret_head;
  }
};
