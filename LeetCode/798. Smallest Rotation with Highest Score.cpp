#include <vector>

using namespace std;

class Solution {
   public:
    int bestRotation(vector<int> &A) {
        vector<int> pos(A.size() * 2 + 10, 0);
        int n = A.size();
        for (int i = n - 1; i >= 0; i--) {
            // join in
            pos[i - A[i] + n] += 1;
            // take out
            pos[i] -= 1;
        }
        for (int i = 2 * n - 1; i >= 0; i--) {
            pos[i] += pos[i + 1];
        }
        int ans = 0, ans_val = 0;
        for (int i = 0; i < n; i++) {
            if (pos[i] + pos[i + n] > ans_val) {
                ans_val = pos[i] + pos[i + n];
                ans = i;
            }
        }
        return ans;
    }
};