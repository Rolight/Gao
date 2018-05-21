/*
 * [488] Zuma Game
 *
 * https://leetcode.com/problems/zuma-game/description/
 *
 * algorithms
 * Hard (37.12%)
 * Total Accepted:    6K
 * Total Submissions: 16.3K
 * Testcase Example:  '"WRRBBW"\n"RB"'
 *
 * Think about Zuma Game. You have a row of balls on the table, colored red(R),
 * yellow(Y), blue(B), green(G), and white(W). You also have several balls in
 * your hand.
 *
 * Each time, you may choose a ball in your hand, and insert it into the row
 * (including the leftmost place and rightmost place). Then, if there is a
 * group of 3 or more balls in the same color touching, remove these balls.
 * Keep doing this until no more balls can be removed.
 *
 * Find the minimal balls you have to insert to remove all the balls on the
 * table. If you cannot remove all the balls, output -1.
 *
 *
 * Examples:
 * Input: "WRRBBW", "RB"
 * Output: -1
 * Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW
 *
 * Input: "WWRRBBWW", "WRBRW"
 * Output: 2
 * Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW ->
 * empty
 *
 * Input:"G", "GGGGG"
 * Output: 2
 * Explanation: G -> G[G] -> GG[G] -> empty
 *
 * Input: "RBYYBBRRB", "YRBGB"
 * Output: 3
 * Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] ->
 * BB[B] -> empty
 *
 *
 *
 * Note:
 *
 * You may assume that the initial row of balls on the table won’t have any 3
 * or more consecutive balls with the same color.
 * The number of balls on the table won't exceed 20, and the string represents
 * these balls is called "board" in the input.
 * The number of balls in your hand won't exceed 5, and the string represents
 * these balls is called "hand" in the input.
 * Both input strings will be non-empty and only contain characters
 * 'R','Y','B','G','W'.
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

typedef long long LL;

using namespace std;

class Solution {
    struct List {
        List *prev, *next;
        char val;

        List() : prev(this), next(this), val('#') {}

        void display() {
            for (List *node = this->next; node != this; node = node->next) {
                printf("-> %c ", node->val);
            }
            puts("");
        }
    };

    unordered_map<int, int> ch2id;
    unordered_map<LL, unordered_map<LL, int> > mp;

    void shot(string &board, int pos, char bullet) { int same_count = 0; }

    LL encode_list(List *head) {
        LL ret = 0;
        for (List *cur = head->next; cur != head; cur = cur->next) {
            ret = ret << 3 | ch2id[cur->val];
        }
        return ret;
    }

    int cur_min_dep;
    int dfs(List *cur_board, List *cur_hand, int cur_dep) {
        if (cur_board->next == cur_board) {
            cur_min_dep = min(cur_dep, cur_min_dep);
            return 0;
        }
        if (cur_dep + 1 >= cur_min_dep) return -1;
        if (cur_hand->next == cur_hand) return -1;

        LL hx = encode_list(cur_board), hy = encode_list(cur_hand);
        if (mp.count(hx) != 0 && mp[hx].count(hy) != 0) {
            return mp[hx][hy];
        }

        // cur_board->display();
        // cur_hand->display();
        int ret = -1;
        // choose which bullet to shot
        for (List *bullet = cur_hand->next; bullet != cur_hand;
             bullet = bullet->next) {
            if (bullet->val == bullet->prev->val) continue;
            // remove cur_bullet from list
            bullet->prev->next = bullet->next;
            bullet->next->prev = bullet->prev;

            // choose which position to insert
            for (List *shot_pos = cur_board;; shot_pos = shot_pos->next) {
                if (shot_pos->prev->val != bullet->val &&
                    shot_pos->val != bullet->val) {
                    if (shot_pos->next == cur_board)
                        break;
                    else
                        continue;
                }
                // insert bullet before shot_pos
                List *newNode = new List();
                newNode->val = bullet->val;
                newNode->prev = shot_pos->prev;
                newNode->next = shot_pos;

                shot_pos->prev->next = newNode;
                shot_pos->prev = newNode;
                // check if need remove continuous node
                int lcount = 0, rcount = 0;
                bool combined = false;
                List *lnode, *rnode;
                for (lnode = newNode->prev; lnode->val == newNode->val;
                     lnode = lnode->prev)
                    lcount++;
                for (rnode = newNode->next; rnode->val == newNode->val;
                     rnode = rnode->next)
                    rcount++;
                lnode = lnode->next;
                rnode = rnode->prev;

                if (lcount + rcount + 1 >= 3) {
                    // combine the continuous same node and remove them
                    combined = true;
                    // cascade combine
                    while (true) {
                        List *clnode, *crnode, *cnode = lnode->prev;
                        int clcount = 0, crcount = 0;
                        for (clnode = lnode->prev; clnode->val == cnode->val;
                             clnode = clnode->prev)
                            clcount++;
                        for (crnode = rnode->next; crnode->val == cnode->val;
                             crnode = crnode->next)
                            crcount++;
                        if (clcount + crcount >= 3) {
                            lnode = clnode->next;
                            rnode = crnode->prev;
                        } else {
                            break;
                        }
                    }
                    lnode->prev->next = rnode->next;
                    rnode->next->prev = lnode->prev;
                }

                // dfs forward
                int cur_ret = dfs(cur_board, cur_hand, cur_dep + 1);
                if (cur_ret != -1 && (ret == -1 || cur_ret + 1 < ret)) {
                    ret = cur_ret + 1;
                }

                // recover cur_board

                if (combined) {
                    lnode->prev->next = lnode;
                    rnode->next->prev = rnode;
                }

                newNode->prev->next = newNode->next;
                newNode->next->prev = newNode->prev;
                delete newNode;

                // end of loop
                if (shot_pos->next == cur_board) break;
            }

            // recover cur_bullet to list
            bullet->prev->next = bullet->next->prev = bullet;
        }
        mp[hx][hy] = ret;
        return ret;
    }

   public:
    Solution() {
        string encode = "RYBGW";
        for (int i = 0; i < encode.size(); i++) {
            ch2id[encode[i]] = i + 1;
        }
    }

    int findMinStep(string board, string hand) {
        sort(hand.begin(), hand.end());
        List *list = new List(), *hlist = new List();
        // convert string to list
        for (int i = 0; i < board.length(); i++) {
            List *curNode = new List();
            curNode->val = board[i];
            curNode->prev = list->prev;
            curNode->next = list;
            list->prev->next = curNode;
            list->prev = curNode;
        }

        for (int i = 0; i < hand.length(); i++) {
            List *curNode = new List();
            curNode->val = hand[i];
            curNode->prev = hlist->prev;
            curNode->next = hlist;
            hlist->prev->next = curNode;
            hlist->prev = curNode;
        }

        mp.clear();
        cur_min_dep = 1e6;
        return dfs(list, hlist, 0);
    }
};

int main() {
    string board, hand;
    Solution s;
    while (cin >> board >> hand) {
        cout << s.findMinStep(board, hand) << endl;
    }
    return 0;
}