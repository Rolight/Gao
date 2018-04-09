# Definition for a point.
# class Point:
#     def __init__(self, a=0, b=0):
#         self.x = a
#         self.y = b
from collections import defaultdict
from math import sqrt


class Solution:
    def gcd(self, a, b):
        if b == 0:
            return a
        return self.gcd(b, a % b)

    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        pcount = defaultdict(int)
        upoints = []
        for p in points:
            if pcount[(p.x, p.y)] == 0:
                upoints.append((p.x, p.y))
            pcount[(p.x, p.y)] += 1

        vis = set()
        count = defaultdict(int)

        def agg(x): return x * (x - 1) // 2
        ans = min(1, len(points))
        for i in range(len(upoints)):
            ans = max(ans, pcount[upoints[i]])
            for j in range(i + 1, len(upoints)):
                x1, y1 = upoints[i]
                x2, y2 = upoints[j]
                A = y1 - y2
                B = -(x1 - x2)
                C = y1 * (x1 - x2) - (y1 - y2) * x1

                g = 1
                for v in [abs(v) for v in [A, B, C] if v != 0]:
                    g *= v
                for v in [abs(v) for v in [A, B, C] if v != 0]:
                    g = self.gcd(g, v)
                if (-A // g, -B // g, -C // g) in count:
                    g *= -1
                A, B, C = A // g, B // g, C // g
                # print('cur A, B, C = ', (A, B, C))
                count[(A, B, C)] += pcount[upoints[i]] * pcount[upoints[j]]
                if (A, B, C, i) not in vis:
                    count[(A, B, C)] += agg(pcount[upoints[i]])
                    vis.add((A, B, C, i))
                if (A, B, C, j) not in vis:
                    count[(A, B, C)] += agg(pcount[upoints[j]])
                    vis.add((A, B, C, j))
        for k, v in count.items():
            ans = max(ans, (1 + sqrt(1 + 8 * v)) // 2)
        return int(ans)
