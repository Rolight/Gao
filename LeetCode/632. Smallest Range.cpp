#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Solution {
    inline void update(pair<int, int> &ans, int c, int d) {
        int a = ans.first, b = ans.second;
        if (b - a == d - c) {
            if (c < a) {
                ans.first = c;
                ans.second = d;
            }
        } else if (d - c < b - a) {
            ans.first = c;
            ans.second = d;
        }
    }

   public:
    vector<int> smallestRange(vector<vector<int> > &nums) {
        priority_queue<pair<int, pair<int, int> > > q;
        int k = nums.size();
        for (int i = 0; i < k; i++) {
            q.push(make_pair(-nums[i][0], make_pair(0, i)));
        }
        pair<int, int> ans = make_pair(0, (int)1e9);
        int cur_l = -1, cur_r = -1, cur_k = 0;
        vector<int> vals(k);
        vector<bool> vis(k);
        multiset<int> st;
        while (!q.empty()) {
            pair<int, pair<int, int> > cur_top = q.top();
            q.pop();
            int val = -cur_top.first, pos = cur_top.second.first,
                list_id = cur_top.second.second;
            // printf("%d(%d, %d) ", val, list_id, vals[list_id]);
            if (pos + 1 < nums[list_id].size()) {
                q.push(make_pair(-nums[list_id][pos + 1],
                                 make_pair(pos + 1, list_id)));
            }

            if (vis[list_id]) {
                multiset<int>::iterator iter = st.lower_bound(vals[list_id]);
                st.erase(iter);
                // printf("remove %d\n", vals[list_id]);
            } else {
                cur_k++;
                vis[list_id] = true;
            }
            st.insert(val);
            vals[list_id] = val;

            if (cur_k < k) continue;
            multiset<int>::iterator iter = st.begin();
            cur_l = *iter;
            iter = st.end();
            --iter;
            cur_r = *iter;
            // printf("%d %d\n", cur_l, cur_r);
            update(ans, cur_l, cur_r);
        }
        vector<int> ret;
        ret.push_back(ans.first);
        ret.push_back(ans.second);
        return ret;
    }
};