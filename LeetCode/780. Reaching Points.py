from collections import deque
import math


class Solution:
    def reachingPoints(self, sx, sy, tx, ty):
        while True:
            if tx == sx and ty == sy:
                return True
            if tx < sx or ty < sy:
                break
            if (tx, sy) < (ty, sx):
                dis = ty - max(tx, sy)
                count = math.ceil(dis / tx)
                count = max(1, count)
                ty -= count * tx
            else:
                dis = tx - max(ty, sx)
                count = math.ceil(dis / ty)
                count = max(1, count)
                tx -= count * ty
        return False
