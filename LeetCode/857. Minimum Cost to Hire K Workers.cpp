#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage,
                                int K) {
        vector<pair<double, int> > vec;
        int N = quality.size();
        if (N == 1) return wage[0];
        for (int i = 0; i < N; i++)
            vec.push_back(make_pair((double)wage[i] / (double)quality[i], i));
        sort(vec.begin(), vec.end());
        priority_queue<int> pq;
        double ans = 1e18, cur_sum = 0;
        for (int i = 0; i < K - 1; i++) {
            cur_sum += quality[vec[i].second];
            pq.push(quality[vec[i].second]);
        }
        for (int i = K - 1; i < N; i++) {
            double cur_ans = (cur_sum + quality[vec[i].second]) * vec[i].first;
            ans = min(ans, cur_ans);
            if (!pq.empty() && quality[vec[i].second] < pq.top()) {
                cur_sum -= pq.top();
                cur_sum += quality[vec[i].second];
                pq.pop();
                pq.push(quality[vec[i].second]);
            }
        }
        return ans;
    }
};
