/*
 * [132] Palindrome Partitioning II
 *
 * https://leetcode.com/problems/palindrome-partitioning-ii/description/
 *
 * algorithms
 * Hard (24.81%)
 * Total Accepted:    80.4K
 * Total Submissions: 324K
 * Testcase Example:  '"aab"'
 *
 *
 * Given a string s, partition s such that every substring of the partition is
 * a palindrome.
 *
 *
 * Return the minimum cuts needed for a palindrome partitioning of s.
 *
 *
 * For example, given s = "aab",
 * Return 1 since the palindrome partitioning ["aa","b"] could be produced
 * using 1 cut.
 *
 */
import static java.lang.Math.*;

class Solution {
    int hash_seed = 1313131;
    long[] h;
    long[] rh;
    long[] powv;

    // bkdr hash
    void initHash(String s) {
        h = new long[s.length()];
        rh = new long[s.length()];
        powv = new long[s.length()];
        for (int i = 0; i < s.length(); i++) {
            int ch = (int) s.charAt(i);
            int rch = (int) s.charAt(s.length() - i - 1);
            if (i == 0) {
                powv[i] = 1;
                h[i] = ch;
                rh[i] = rch;
            } else {
                powv[i] = powv[i - 1] * hash_seed;
                h[i] = h[i - 1] * hash_seed + ch;
                rh[i] = rh[i - 1] * hash_seed + rch;
            }
        }
    }

    public boolean check(int l, int r, String s) {
        if (l == r)
            return true;
        int ll = l, lr, rl, rr = r;
        if ((r - l + 1) % 2 == 0) {
            lr = (l + r) / 2;
            rl = lr + 1;
        } else {
            lr = (l + r) / 2 - 1;
            rl = (l + r) / 2 + 1;
        }
        /*
            a b c d e
            a 1
            ab 14
            abc 148
            abcd 1482
            abcde 14829
            bcd = abcd - a... = 1482 - 1000
            cd = abcd - ab.. = 1482 - 1400
            hash = h[r] - h[l - 1] * powv[r - l + 1];
        */
        rl = s.length() - rl - 1;
        rr = s.length() - rr - 1;
        long rhash = h[lr];
        if (ll > 0) {
            rhash -= h[ll - 1] * powv[lr - ll + 1];
        }
        long lhash = rh[rl];
        if (rr > 0) {
            lhash -= rh[rr - 1] * powv[rl - rr + 1];
        }
        /*
        System.out.printf("(%d %d), %s\n", l, r, s.substring(l, r + 1));
        System.out.printf("ll,lr = (%d, %d), rl, rr = (%d, %d)\n", ll, lr, rl, rr);
        System.out.println(lhash);
        System.out.println(rhash);
        */
        return rhash == lhash;
    }

    public int minCut(String s) {
        initHash(s);
        int[] f = new int[s.length() + 1];
        f[0] = 0;
        for (int i = 1; i <= s.length(); i++) {
            f[i] = f[i - 1] + 1;
            if (check(0, i - 1, s)) {
                f[i] = 0;
                continue;
            }
            for (int j = 2; j < i; j++) {
                if (check(j - 1, i - 1, s)) {
                    f[i] = min(f[i], f[j - 1] + 1);
                }
            }
        }
        return f[s.length()];
    }
}
