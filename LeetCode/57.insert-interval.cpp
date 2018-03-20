/*
 * [57] Insert Interval
 *
 * https://leetcode.com/problems/insert-interval/description/
 *
 * algorithms
 * Hard (28.85%)
 * Total Accepted:    122.2K
 * Total Submissions: 422.6K
 * Testcase Example:  '[[1,3],[6,9]]\n[2,5]'
 *
 * Given a set of non-overlapping intervals, insert a new interval into the
 * intervals (merge if necessary).
 *
 * You may assume that the intervals were initially sorted according to their
 * start times.
 *
 *
 * Example 1:
 * Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 *
 *
 *
 * Example 2:
 * Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as
 * [1,2],[3,10],[12,16].
 *
 *
 *
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 *
 */
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

#include <algorithm>
#include <map>
#include <vector>

using std::lower_bound;
using std::make_pair;
using std::max;
using std::vector;

bool cmp(const Interval &a, const Interval &b) {
    return make_pair(a.start, a.end) < make_pair(b.start, b.end);
}

class Solution {
   public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval>::iterator ret =
            lower_bound(intervals.begin(), intervals.end(), newInterval, cmp);
        int m = intervals.size();

        if (m == 0) {
            intervals.push_back(newInterval);
            return intervals;
        }

        if (ret == intervals.end()) {
            ret--;
            if (ret->end < newInterval.start) {
                intervals.push_back(newInterval);
            } else {
                ret->end = max(newInterval.end, ret->end);
            }
            return intervals;
        }

        if (ret->start > newInterval.start) {
            if (ret == intervals.begin()) {
                if (newInterval.end < ret->start) {
                    intervals.insert(intervals.begin(), newInterval);
                    return intervals;
                } else {
                    ret->start = newInterval.start;
                }
            } else {
                vector<Interval>::iterator prev = ret - 1;
                if (prev->end < newInterval.start) {
                    if (newInterval.end < ret->start) {
                        intervals.insert(ret, newInterval);
                        return intervals;
                    } else {
                        ret->start = newInterval.start;
                    }
                } else {
                    newInterval.start = prev->start;
                    ret = prev;
                }
            }
        }

        if (ret->start == newInterval.start) {
            if (ret->end >= newInterval.end) {
                return intervals;
            }
            vector<Interval> ans;
            int cur = 0;
            while (intervals[cur].start < ret->start) {
                ans.push_back(intervals[cur++]);
            }
            ++cur;
            while (cur < m && intervals[cur].start <= newInterval.end) {
                newInterval.end = max(intervals[cur++].end, newInterval.end);
            }
            ans.push_back(newInterval);
            while (cur < m) {
                ans.push_back(intervals[cur++]);
            }
            return ans;
        }

        return intervals;
    }
};
