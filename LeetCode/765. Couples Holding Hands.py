class Solution:
    def minSwapsCouples(self, row):
        """
        :type row: List[int]
        :rtype: int
        """
        vis = [False] * len(row)
        pos = [-1] * len(row)
        # get all pos
        for idx, num in enumerate(row):
            pos[num] = idx

        ans = 0
        for idx, num in enumerate(row):
            if vis[idx]:
                continue
            cur = idx
            now_count = 0
            while not vis[cur]:
                vis[cur] = True
                val = row[cur] ^ 1
                epos = cur ^ 1
                vis[epos] = True
                cur = pos[val] ^ 1
                now_count += 1
            ans += now_count - 1
        return ans
