class Solution:
    def get_limits(self, n):
        self.limits_value = int(n)
        self.limits = []
        while n > 0:
            self.limits.append(n % 10)
            n //= 10
        self.limits.reverse()
        self.total_len = len(self.limits)
        self.f = self._f[self.total_len]
        # print('for %d, limits is %s' % (n, self.limits))

    def gao(self, cur_pos, start_pos, bound, cur_num):
        if start_pos != -1:
            cur_len = cur_pos - start_pos
            total_needed_len = self.total_len - start_pos
            if cur_len * 2 >= total_needed_len:
                if not bound:
                    return 1
                else:
                    cur_num = str(cur_num)
                    cc_pos = cur_pos - 1 if cur_len * 2 == total_needed_len else cur_pos - 2
                    # print(cur_num, cc_pos, self.limits)
                    while cc_pos >= 0:
                        cc_num = int(cur_num[cc_pos])
                        # print('compare ', (cc_num, self.limits[cur_pos]))
                        if cc_num > self.limits[cur_pos]:
                            return 0
                        elif cc_num < self.limits[cur_pos]:
                            return 1
                        cc_pos -= 1
                        cur_pos += 1
                    return 1

        if start_pos != -1 and not bound and self.f[cur_pos][start_pos] != -1:
            return self.f[cur_pos][start_pos]
            # pass

        # print(self.total_len)
        if cur_pos == self.total_len:
            # print(start_pos, cur_num)
            return 1

        lim = self.limits[cur_pos] if bound else 9
        ret = 0
        for i in range(0, lim + 1):
            n_start_pos = start_pos
            if n_start_pos == -1 and i != 0:
                n_start_pos = cur_pos
            n_bound = bound and i == lim
            ret += self.gao(cur_pos + 1, n_start_pos,
                            n_bound, cur_num * 10 + i)

        if start_pos != -1 and not bound:
            self.f[cur_pos][start_pos] = ret

        return ret

    def get_count(self, n):
        if n < 0:
            return 0
        if n == 0:
            return 1

        self.get_limits(n)

        return self.gao(0, -1, True, 0)

    def find_smaller(self, n, baseline):
        # print('cur baseline = ', baseline)
        l, r = 0, n - 1
        if l > r:
            return -1
        ans = -1
        while l <= r:
            mid = (l + r) // 2
            cur_count = self.get_count(mid - 1)
            # print('l, r', (l, r))
            # print('mid = ', mid, 'cur_count = ', cur_count, ' baseline - cur_count = ', baseline - cur_count)
            if baseline - cur_count >= 1:
                ans = mid
                l = mid + 1
            else:
                r = mid - 1
        return ans

    def find_bigger(self, n, baseline, sr):
        l, r = n + 1, n * 2 + 1
        if sr != -1:
            r = n + sr + 10
        ans = -1
        while l <= r:
            mid = (l + r) // 2
            cur_count = self.get_count(mid)
            if cur_count - baseline >= 1:
                ans = mid
                r = mid - 1
            else:
                l = mid + 1
        return ans

    def __init__(self):
        self._f = [[[-1 for _ in range(20)]
                    for _ in range(20)] for _ in range(20)]

    def nearestPalindromic(self, n):
        """
        :type n: str
        :rtype: str
        """
        """
            f(i, j) means cur_pos at i, start_pos at j
        """
        n = int(n)
        ans = self.find_smaller(n, self.get_count(n - 1))
        ans1 = self.find_bigger(n, self.get_count(
            n), -1 if ans == -1 else n - ans)
        if ans == -1:
            return str(ans1)
        elif ans1 == -1:
            return str(ans)
        else:
            if (n - ans) > (ans1 - n):
                return str(ans1)
            else:
                return str(ans)
