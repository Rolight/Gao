/*
 * [23] Merge k Sorted Lists
 *
 * https://leetcode.com/problems/merge-k-sorted-lists/description/
 *
 * algorithms
 * Hard (28.04%)
 * Total Accepted:    207.3K
 * Total Submissions: 739.5K
 * Testcase Example:  '[]'
 *
 *
 * Merge k sorted linked lists and return it as one sorted list. Analyze and
 * describe its complexity.
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

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

#include <map>
#include <set>
#include <vector>

using std::vector;

typedef std::pair<int, ListNode *> Tp;

bool operator<(const Tp &a, const Tp &b) {
  if (a.first != b.first) {
    return a.first < b.first;
  } else {
    return (long long)a.second < (long long)b.second;
  }
}

class Solution {
public:
  int pop_val(std::set<Tp> &heads) {
    Tp cur = *(heads.begin());
    int cur_val = cur.first;
    ListNode *cur_list = cur.second;
    heads.erase(heads.begin());
    if (cur_list->next != NULL) {
      heads.insert(std::make_pair(cur_list->next->val, cur_list->next));
    }
    return cur_val;
  }

  ListNode *mergeKLists(vector<ListNode *> &lists) {
    std::set<Tp> heads;
    for (vector<ListNode *>::iterator iter = lists.begin(); iter != lists.end();
         ++iter) {
      if (*iter != NULL) {
        heads.insert(std::make_pair((*iter)->val, *iter));
      }
    }
    ListNode *cur = NULL, *head = NULL;
    while (heads.size() > 0) {
      int cur_val = pop_val(heads);
      ListNode *newnode = new ListNode(cur_val);
      if (head == NULL) {
        head = cur = newnode;
      } else {
        cur->next = newnode;
        cur = newnode;
      }
    }
    return head;
  }
};
