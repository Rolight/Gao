/*
 * [218] The Skyline Problem
 *
 * https://leetcode.com/problems/the-skyline-problem/description/
 *
 * algorithms
 * Hard (29.03%)
 * Total Accepted:    60.8K
 * Total Submissions: 209.2K
 * Testcase Example:  '[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]'
 *
 * A city's skyline is the outer contour of the silhouette formed by all the
 * buildings in that city when viewed from a distance. Now suppose you are
 * given the locations and height of all the buildings as shown on a cityscape
 * photo (Figure A), write a program to output the skyline formed by these
 * buildings collectively (Figure B).
 *
 *
 *
 * ⁠
 *
 *
 *
 *
 * ⁠
 *
 *
 *
 *
 *
 * The geometric information of each building is represented by a triplet of
 * integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and
 * right edge of the ith building, respectively, and Hi is its height. It is
 * guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You
 * may assume all buildings are perfect rectangles grounded on an absolutely
 * flat surface at height 0.
 *
 * For instance, the dimensions of all buildings in Figure A are recorded as: [
 * [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .
 *
 * The output is a list of "key points" (red dots in Figure B) in the format of
 * [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key
 * point is the left endpoint of a horizontal line segment. Note that the last
 * key point, where the rightmost building ends, is merely used to mark the
 * termination of the skyline, and always has zero height. Also, the ground in
 * between any two adjacent buildings should be considered part of the skyline
 * contour.
 *
 * For instance, the skyline in Figure B should be represented as:[ [2 10], [3
 * 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].
 *
 * Notes:
 *
 * ⁠The number of buildings in any input list is guaranteed to be in the range
 * [0, 10000].
 * ⁠The input list is already sorted in ascending order by the left x position
 * Li.
 * ⁠The output list must be sorted by the x position.
 * ⁠There must be no consecutive horizontal lines of equal height in the
 * output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is
 * not acceptable; the three lines of height 5 should be merged into one in the
 * final output as such: [...[2 3], [4 5], [12 7], ...]
 *
 *
 *
 * Credits:Special thanks to @stellari for adding this problem, creating these
 * two awesome images and all test cases.
 */
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <vector>

using std::make_pair;
using std::pair;
using std::set;
using std::sort;
using std::vector;

struct Seg {
    int x, h, l;
    Seg(int x, int h, int l) : x(x), h(h), l(l) {}
    bool operator<(const Seg& s) const { return x < s.x; }
};

class Solution {
   public:
    vector<pair<int, int> > getSkyline(vector<vector<int> >& buildings) {
        vector<Seg> segs;
        for (int i = 0; i < buildings.size(); i++) {
            vector<int>& curb = buildings[i];
            int L = curb[0], R = curb[1], H = curb[2];
            segs.push_back(Seg(L, H, L));
            segs.push_back(Seg(R, H, L));
        }
        sort(segs.begin(), segs.end());
        vector<pair<int, int> > ans;
        set<pair<int, int> > st;
        st.insert(make_pair(0, -1));
        int last = 0;
        for (int i = 0; i < segs.size(); i++) {
            int j = i;
            while (j < segs.size() && segs[j].x == segs[i].x) {
                if (segs[j].l == segs[j].x) {
                    st.insert(make_pair(segs[j].h, segs[j].x));
                } else {
                    st.erase(make_pair(segs[j].h, segs[j].l));
                }
                j++;
            }
            i = j - 1;

            set<pair<int, int> >::iterator iter = st.end();
            --iter;
            int cur_top = iter->first;
            if (cur_top != last) {
                ans.push_back(make_pair(segs[i].x, cur_top));
                last = cur_top;
            }
        }
        return ans;
    }
};
