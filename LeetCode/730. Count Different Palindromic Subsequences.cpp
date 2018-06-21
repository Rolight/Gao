#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;
typedef long long LL;

class Solution {
    vector<int> prev, next;
    vector<vector<int> > f;
    inline void maintain(LL &val) {
        while (val < 0) val += mod;
        val %= mod;
    }
    LL gao(string &s, int i, int j) {
        if (i == j) return 1;
        if (i > j) return 0;
        if (f[i][j] != -1) return f[i][j];
        LL ret = 0;
        if (s[i] == s[j]) {
            ret = 2 * gao(s, i + 1, j - 1);
            if (next[i] > prev[j])
                ret += 2;
            else if (next[i] == prev[j])
                ret += 1;
            else
                ret -= gao(s, next[i] + 1, prev[j] - 1);
            maintain(ret);
        } else {
            ret = gao(s, i, j - 1) + gao(s, i + 1, j) - gao(s, i + 1, j - 1);
            maintain(ret);
        }
        f[i][j] = ret;
        return ret;
    }

   public:
    int countPalindromicSubsequences(string S) {
        int last_pos[26];
        prev.clear();
        next.clear();
        memset(last_pos, -1, sizeof(last_pos));
        for (int i = 0; i < S.size(); i++) {
            int cur = S[i] - 'a';
            prev.push_back(last_pos[cur]);
            last_pos[cur] = i;
        }
        memset(last_pos, -1, sizeof(last_pos));
        for (int i = (int)S.size() - 1; i >= 0; i--) {
            int cur = S[i] - 'a';
            next.push_back(last_pos[cur]);
            last_pos[cur] = i;
        }
        vector<int> tmp = vector<int>(S.length(), -1);
        f = vector<vector<int> >(S.length(), tmp);
        reverse(next.begin(), next.end());
        if (S.length() == 1) return 1;
        int ans = gao(S, 0, S.length() - 1);
        return ans;
    }
};

int main() {
    Solution s;
    string buf;
    while (cin >> buf) {
        cout << s.countPalindromicSubsequences(buf) << endl;
    }
    return 0;
}