#include <deque>

using std::deque;

struct Node {
    int pos, val;
    Node(int pos, int val): pos(pos), val(val) {}
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<Node> q;
        vector<int> ans;
        for(int i = 0; i < nums.size(); i++) {
            while(!q.empty() && q.front().pos <= i - k) {
                q.pop_front();
            }
            while(!q.empty() && q.back().val <= nums[i]) {
                q.pop_back();
            }
            q.push_back(Node(i, nums[i]));
            if(i >= k - 1) {
                ans.push_back(q.front().val);
            }
        }
        return ans;
    }
};
