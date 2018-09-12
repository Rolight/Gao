#include <vector>


class Solution {
    vector<int> limits;
    set<int> digits;
    vector<int> f;
    void get_limit(int N) {
        limits.clear();
        while(N) {
            limits.push_back(N % 10);
            N /= 10;
        }
    }
    
    int dfs(int pos, bool bound, bool str) {
        if(pos == 0) return 1;
        int m = bound ? limits[pos  - 1] : 9;
        if(bound == false && str == true && f[pos] != -1) return f[pos]; 
        int ret = 0;
        for(int i = 0; i <= m; i++) {
            if(digits.count(i) != 0 || (i == 0 && str == false)) {
                ret += dfs(pos - 1, bound && i == limits[pos - 1], str || i != 0);
            }
        }
        if(bound == false && str == true) f[pos] = ret;
        return ret;
    }
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        digits.clear();
        f = vector<int>(50, -1);
        for(int i = 0; i < D.size(); i++) digits.insert(D[i][0] - '0');
        get_limit(N);
        return dfs(limits.size(), true, false) - 1;
    }
};