/*
 * [587] Erect the Fence
 *
 * https://leetcode.com/problems/erect-the-fence/description/
 *
 * algorithms
 * Hard (33.66%)
 * Total Accepted:    4.7K
 * Total Submissions: 14K
 * Testcase Example:  '[[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]'
 *
 * There are some trees, where each tree is represented by (x,y) coordinate in
 * a two-dimensional garden. Your job is to fence the entire garden using the
 * minimum length of rope as it is expensive. The garden is well fenced only if
 * all the trees are enclosed. Your task is to help find the coordinates of
 * trees which are exactly located on the fence perimeter.
 *
 * Example 1:
 *
 * Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
 * Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
 * Explanation:
 *
 *
 *
 *
 * Example 2:
 *
 * Input: [[1,2],[2,2],[4,2]]
 * Output: [[1,2],[2,2],[4,2]]
 * Explanation:
 *
 * Even you only have trees in a line, you need to use rope to enclose
 * them.
 *
 *
 *
 * ⁠Note:
 *
 * All trees should be enclosed together. You cannot cut the rope to enclose
 * trees that will separate them in more than one group.
 * All input integers will range from 0 to 100.
 * The garden has at least one tree.
 * All coordinates are distinct.
 * Input points have NO order. No order required for output.
 *
 *
 */
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

const double eps = 1e-7;

using namespace std;

double cross_product(Point a, Point b) { return a.x * b.y - a.y * b.x; }

Point sub(Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }

int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

double dist(Point a, Point b) {
    int d = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    double ans = sqrt((double)d);
    // cout << ans << endl;
    return ans;
}

int cross(Point a, Point b, Point c) {
    return sgn((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

bool cmp(const Point &p1, const Point &p2) {
    if (fabs(p1.y - p2.y) < eps) return p1.x < p2.x;
    return p1.y < p2.y;
}

class Solution {
    vector<Point> graham(vector<Point> &points) {
        vector<Point> plist = points;
        sort(plist.begin(), plist.end(), cmp);
        vector<int> ans(plist.size() * 2);
        vector<Point> ret;
        ans[0] = 0;
        ans[1] = 1;

        int top = 1;

        for (int i = 2; i < plist.size(); i++) {
            while (top > 0 &&
                   cross(plist[ans[top - 1]], plist[ans[top]], plist[i]) < 0) {
                top--;
            }
            ans[++top] = i;
        }

        int temp = top;
        for (int i = plist.size() - 2; i >= 0; i--) {
            while (top > temp &&
                   cross(plist[ans[top - 1]], plist[ans[top]], plist[i]) < 0) {
                top--;
            }
            ans[++top] = i;
        }
        ans.erase(ans.begin() + top, ans.end());
        vector<bool> vis(plist.size(), false);
        for (int i = 0; i < ans.size(); i++) {
            if (!vis[ans[i]]) {
                ret.push_back(plist[ans[i]]);
                vis[ans[i]] = true;
            }
        }
        return ret;
    }

   public:
    vector<Point> outerTrees(vector<Point> &points) {
        if (points.size() <= 2) return points;
        return graham(points);
    }
};