#include <vector>

using namespace std;

class Solution {
   public:
    int intersectionSizeTwo(vector<vector<int> > &intervals) {
        sort(intervals.begin(), intervals.end(),
             [](vector<int> &v1, vector<int> &v2) {
                 return v1[1] < v2[1] || (v1[1] == v2[1] && v1[0] > v2[0]);
             });
        vector<int> pool{-1, -1};
        for (auto &e : intervals) {
            int sz = pool.size();
            if (e[0] <= pool[sz - 2]) continue;
            if (e[0] > pool[sz - 1]) pool.push_back(e[1] - 1);
            pool.push_back(e[1]);
        }

        return pool.size() - 2;
    }
};