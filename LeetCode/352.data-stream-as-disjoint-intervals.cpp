/*
 * [352] Data Stream as Disjoint Intervals
 *
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/description/
 *
 * algorithms
 * Hard (41.04%)
 * Total Accepted:    17.3K
 * Total Submissions: 42.1K
 * Testcase Example:
 * '["SummaryRanges","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals"]\n[[],[1],[],[3],[],[7],[],[2],[],[6],[]]'
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, ...,
 * summarize the numbers seen so far as a list of disjoint intervals.
 *
 * For example, suppose the integers from the data stream are 1, 3, 7, 2, 6,
 * ..., then the summary will be:
 *
 * [1, 1]
 * [1, 1], [3, 3]
 * [1, 1], [3, 3], [7, 7]
 * [1, 3], [7, 7]
 * [1, 3], [6, 7]
 *
 *
 * Follow up:
 * What if there are lots of merges and the number of disjoint intervals are
 * small compared to the data stream's size?
 *
 *
 * Credits:Special thanks to @yunhong for adding this problem and creating most
 * of the test cases.
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
    int start, end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class SummaryRanges {
    unordered_map<int, int> fa, maxv;
    unordered_set<int> is;

    int getfa(int x) {
        if (fa.count(x) == 0) return -1;
        return fa[x] == x ? x : fa[x] = getfa(fa[x]);
    }

   public:
    /** Initialize your data structure here. */
    SummaryRanges() {}

    void addNum(int val) {
        if (getfa(val) != -1) return;
        int right_fa = getfa(val + 1);
        if (right_fa != -1) {
            maxv[val] = maxv[right_fa];
            fa[right_fa] = val;
            is.erase(right_fa);
        } else {
            maxv[val] = val;
        }

        is.insert(val);

        int left_fa = getfa(val - 1);
        if (left_fa != -1) {
            fa[val] = left_fa;
            maxv[left_fa] = maxv[val];
            is.erase(val);
        } else {
            fa[val] = val;
        }
    }

    vector<Interval> getIntervals() {
        vector<int> start_pos;
        for (unordered_set<int>::iterator iter = is.begin(); iter != is.end();
             ++iter) {
            start_pos.push_back(*iter);
        }
        sort(start_pos.begin(), start_pos.end());
        vector<Interval> ans;
        for (int i = 0; i < start_pos.size(); i++) {
            ans.push_back(Interval(start_pos[i], maxv[start_pos[i]]));
        }
        return ans;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
