class Solution:

    def f(self, t, n, a):
        return a ** t - n * a + n - 1

    def gao(self, t, n):
        l, r = 2, n
        while l <= r:
            mid = (l + r) // 2
            ret = self.f(t, n, mid)
            if ret == 0:
                return mid
            if ret > 0:
                r = mid - 1
            else:
                l = mid + 1
        return -1

    def smallestGoodBase(self, n):
        """
        :type n: str
        :rtype: str
        """
        n = int(n)
        ans = []
        for t in range(1, 71):
            ret = self.gao(t, n)
            if ret != -1:
                ans.append(ret)
        ans.sort()
        return str(ans[0])
