from collections import deque


class Solution:

    def slidingPuzzle(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        val = 0
        for b in board:
            for c in b:
                val = val * 10 + c
        if val == 123450:
            return 0
        q = deque()
        q.append(val)
        mp = dict()
        mp[val] = 0

        while(len(q)):
            now = q.popleft()
            now = "%06d" % now
            # print(now[:3] + '\n' + now[3:])

            for pos, val in enumerate(now):
                if val == '0':
                    break

            shift_vals = {
                0: [1, 3],
                1: [-1, 1, 3],
                2: [-1, 3],
                3: [1, -3],
                4: [-1, 1, -3],
                5: [-1, -3]
            }

            for sv in shift_vals[pos]:

                newval = list(now)
                # print('sv: ', pos, pos + sv, '->', newval)
                newval[pos + sv], newval[pos] = newval[pos], newval[pos + sv]
                newval = int(''.join(newval))

                if newval in mp:
                    continue

                mp[newval] = mp[int(now)] + 1
                q.append(newval)

                if newval == 123450:
                    return mp[newval]
        return -1
