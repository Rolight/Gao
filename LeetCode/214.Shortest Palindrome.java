import static java.lang.Math.*;

class Solution {
    long[] hc;
    long[] rhc;
    long hash_seed = 1313131;
    long[] hashp;

    public void inithc(String s) {
        hc = new long[s.length()];
        rhc = new long[s.length()];
        hashp = new long[s.length()];

        hashp[0] = 1;
        for(int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            char rc = s.charAt(s.length() - i - 1);
            if(i > 0) {
                hc[i] = hc[i - 1] * hash_seed;
                rhc[i] = rhc[i - 1] * hash_seed;
                hashp[i] = hashp[i - 1] * hash_seed;
            }
            hc[i] += (long)c;
            rhc[i] += (long)rc;
        }
    }

    // 12345

    public long gethc(int l, int r) {
        long ret = hc[r];
        if(l > 0) {
            ret -= hc[l - 1] * hashp[r - l + 1];
        }
        return ret;
    }

    public long getrhc(int n, int l, int r) {
        int rl = n - r - 1, rr = n - l - 1;
        long ret = rhc[rr];
        if (rl > 0) {
            ret -= rhc[rl - 1] * hashp[rr - rl + 1];
        }
        return ret;
    }

    public String shortestPalindrome(String s) {
        if(s.length() == 0) return s;
        inithc(s);
        int max_len = 0;
        for(int i = 0; i + i + 1 < s.length(); i++) {
            // even
            int ll = 0, lr = i, rl = i + 1, rr = i + 1 + i;
            if(gethc(ll, lr) == getrhc(s.length(), rl, rr)) {
                max_len = max(max_len, i + i + 1);
            }
            // odd
            ll = 0;
            lr = i;
            rl = i + 1 + 1;
            rr = i + 1 + 1 + i;
            if(rr >= s.length()) continue;
            if(gethc(ll, lr) == getrhc(s.length(), rl, rr)) {
                max_len = max(max_len, i + i + 1 + 1);
            }
        }
        String ret = "";
        for(int i = max_len + 1; i < s.length(); i++) {
            ret = s.charAt(i) + ret;
        }
        return ret + s;
    }
}
