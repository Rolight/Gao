#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
   public:
    int minRefuelStops(int target, int startFuel,
                       vector<vector<int> > &stations) {
        int N = stations.size();
        vector<int> f(N + 1, 0);
        f[0] = startFuel;
        for (int i = 0; i < N; i++) {
            for (int j = N; j > 0; j--) {
                if (f[j - 1] >= stations[i][0]) {
                    f[j] = max(f[j], f[j - 1] + stations[i][1]);
                }
            }
            for (int j = 0; j <= N; j++) {
                cout << f[j] << " ";
            }
            cout << endl;
        }
        int ans = -1;
        for (int i = 0; i <= N; i++) {
            if (f[i] >= target) {
                ans = i;
                break;
            }
        }
        return ans;
    }
};