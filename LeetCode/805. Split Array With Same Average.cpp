#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool splitArraySameAverage(vector<int> &A) {
        int n = A.size();
        if (n == 1) return false;
        vector<unordered_set<int> > mp(n + 1);
        int first_size = n / 2, last_size = n - first_size;
        int first_sum = 0, last_sum = 0;

        for (int i = 0; i < n; i++) {
            if (i < first_size)
                first_sum += A[i];
            else
                last_sum += A[i];
        }

        for (int i = 0; i < (1 << first_size); ++i) {
            int cur_sum = 0, cur_count = 0;
            for (int j = 0; j < first_size; j++) {
                if ((1 << j) & i) {
                    cur_sum += A[j];
                    cur_count++;
                }
            }
            mp[cur_count].insert(cur_count);
        }

        for (int i = 0; i < (1 << last_size); ++i) {
            int cur_sum = 0, cur_count = 0;
            for (int j = 0; j < last_size; j++) {
                if ((1 << j) & i) {
                    cur_sum += A[j + first_size];
                    cur_count++;
                }
            }
            int S1 = cur_sum, C1 = cur_count;
            int N = n, Sum = first_sum + last_sum;
            for (int C = 0; C <= first_size; C++) {
                int meng = (Sum - S1) * (C + C1) - S1 * (N - C - C1);
                if (meng % N != 0) continue;
                if (mp[C].count(meng / N) != 0) {
                    return true;
                }
            }
        }
        return false;
    }
};