#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

bool cmp(const vector<int> &a, const vector<int> &b) { return a[1] < b[1]; }

class Solution {
   public:
    int scheduleCourse(vector<vector<int> > &courses) {
        if (courses.size() <= 1) return courses.size();
        sort(courses.begin(), courses.end(), cmp);
        priority_queue<int> q;
        int cur_sum = 0;
        for (int i = 0; i < courses.size(); i++) {
            int t = courses[i][0], d = courses[i][1];
            if (t > d) continue;
            // printf("cur_sum = %d, %d %d\n", cur_sum, t, d);
            if (cur_sum + t <= d) {
                q.push(t);
                cur_sum += t;
            } else if (q.top() > t) {
                cur_sum -= q.top();
                cur_sum += t;
                q.pop();
                q.push(t);
            }
        }
        return q.size();
    }
};