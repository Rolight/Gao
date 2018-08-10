#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    int N;
    vector<int> fa;

    int getfa(int x) { return x == fa[x] ? x : fa[x] = getfa(fa[x]); }

    void merge(int x, int y) {
        int fx = getfa(x), fy = getfa(y);
        if (fx > fy) swap(fx, fy);
        fa[fy] = fx;
    }

    bool can(string &a, string &b) {
        if (a.length() != b.length()) return false;
        vector<int> diff_pos;
        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i]) {
                if (diff_pos.size() < 2) {
                    diff_pos.push_back(i);
                } else
                    return false;
            }
        }
        return diff_pos.size() == 0 || diff_pos.size() == 2;
    }

   public:
    int numSimilarGroups(vector<string> &A) {
        N = A.size();
        fa = vector<int>(N, 0);
        for (int i = 0; i < N; i++) fa[i] = i;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                int fi = getfa(i), fj = getfa(j);
                if (fi == fj) continue;
                bool ok = can(A[i], A[j]);
                if (ok) merge(i, j);
            }
        }
        int ans = 0;
        for (int i = 0; i < N; i++)
            if (getfa(i) == i) ans++;
        return ans;
    }
};