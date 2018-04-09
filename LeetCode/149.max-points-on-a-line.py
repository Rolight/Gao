/*
 * [149] Max Points on a Line
 *
 * https://leetcode.com/problems/max-points-on-a-line/description/
 *
 * algorithms
 * Hard (15.19%)
 * Total Accepted:    91.9K
 * Total Submissions: 605.3K
 * Testcase Example:  '[]'
 *
 * Given n points on a 2D plane, find the maximum number of points that lie on
 * the same straight line.
 */
/**
 * Definition for a point.
 * class Point {
 *     int x;
 *     int y;
 *     Point() { x = 0; y = 0; }
 *     Point(int a, int b) { x = a; y = b; }
 * }
 */
import java.util.*;

import static java.lang.Math.*;

/*
x1, x2, y1, y2
y = k * x + b
b = y1 - k * x1
k = (y1 - y2) / (x1 - x2)
y = (y1 - y2) * x / (x1 - x2) + y1 - (y1 - y2) * x1 / (x1 - x2)
(x1 - x2) * y = (y1 - y2) * x + y1 * (x1 - x2) - (y1 - y2) * x1
(y1 - y2) * x - (x1 - x2) *y + y1 * (x1 - x2) - (y1 - y2) * x1 = 0
A * x + B * y + C = 0
A = y1 - y2
B = - (x1 - x2)
C = y1 * (x1 - x2) - (y1 - y2) * x1
*/

/*
C(N, 2) = N * (N - 1) / 2 = V
N ^ 2 - N - 2 * V = 0
delta = 1 + 8 * V
N = (1 + sqrt(1 + 8 * V)) / 2
*/

class Solution {
    public int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    public int gcd(int a, int b, int c) {
        return gcd(abs(a), gcd(abs(b), abs(c)));
    }
    public int maxPoints(Point[] points) {
        HashMap<Integer, HashMap<Integer, HashMap<Integer, Integer> > > hasht = new HashMap<>();
        HashMap<Integer, HashMap<Integer, HashMap<Integer, HashMap<Integer, Boolean> > > > vis =
            new HashMap<>();
        HashMap<Integer, HashMap<Integer, Integer> > pcount = new HashMap<>();
        List<Point> up = new ArrayList<Point>();

        for (int i = 0; i < points.length; i++) {
            int x = points[i].x, y = points[i].y;
            if (pcount.get(x) == null) {
                pcount.put(x, new HashMap<>());
            }
            if (pcount.get(x).get(y) == null) {
                up.add(points[i]);
                pcount.get(x).put(y, 1);
            } else {
                int val = pcount.get(x).get(y);
                pcount.get(x).put(y, val + 1);
            }
        }

        int ans = min(1, points.length);
        for (int i = 0; i < up.size(); i++) {
            int x = up.get(i).x, y = up.get(i).y;
            int cur_count = pcount.get(x).get(y);
            ans = max(ans, cur_count);
            for (int j = i + 1; j < up.size(); j++) {
                int x1 = up.get(i).x, x2 = up.get(j).x;
                int y1 = up.get(i).y, y2 = up.get(j).y;
                int A = y1 - y2;
                int B = -(x1 - x2);
                int C = y1 * (x1 - x2) - (y1 - y2) * x1;
                int[] arr = {A, B, C};
                int g = 1;
                for (int k = 0; k < 3; k++)
                    if (arr[k] != 0)
                        g *= arr[k];
                for (int k = 0; k < 3; k++) {
                    if (arr[k] != 0) {
                        g = gcd(g, arr[k]);
                    }
                }
                A /= g;
                B /= g;
                C /= g;
                int val = 0, count1 = pcount.get(x1).get(y1), count2 = pcount.get(x2).get(y2);
                if (hasht.get(A) == null) {
                    hasht.put(A, new HashMap<>());
                    vis.put(A, new HashMap<>());
                }
                if (hasht.get(A).get(B) == null) {
                    hasht.get(A).put(B, new HashMap<>());
                    vis.get(A).put(B, new HashMap<>());
                }
                if (vis.get(A).get(B).get(C) == null) {
                    vis.get(A).get(B).put(C, new HashMap<>());
                }

                if (vis.get(A).get(B).get(C).get(i) == null) {
                    vis.get(A).get(B).get(C).put(i, true);
                    val += (count1 - 1) * count1 / 2;
                }
                if (vis.get(A).get(B).get(C).get(j) == null) {
                    vis.get(A).get(B).get(C).put(j, true);
                    val += (count2 - 1) * count2 / 2;
                }
                val += count1 * count2;
                if (hasht.get(A).get(B).get(C) == null) {
                    val += hasht.get(A).get(B).get(C);
                }
                System.out.printf("(%dx+%dy+%d=0), count=%d\n", A, B, C, val);
                hasht.get(A).get(B).put(C, val);
                int delta = 1 + 8 * val;
                int sqrt_delta = (int) sqrt(delta);
                if (delta == sqrt_delta * sqrt_delta && (1 + sqrt_delta) % 2 == 0) {
                    int count = (1 + sqrt_delta) / 2;
                    ans = max(ans, count);
                }
            }
        }
        return ans;
    }
}
