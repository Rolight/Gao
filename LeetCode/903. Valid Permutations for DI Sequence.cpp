#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL mod = 1e9 + 7;
const int maxn = 205;
LL f[maxn][maxn];
class Solution {
    vector<int> peak;
    void get_peak(string S) {
        peak.clear();
        if(S[0] == 'D') peak.push_back(1);
        for(int i = 1; i < S.length(); i++) {
            peak.push_back((int)(S[i - 1] == 'I' && S[i] == 'D'));
        }
        if(S.back() == 'I') peak.push_back(1);
        else peak.push_back(0);
        
        cout << "peak: ";
        for(int i = 0; i < peak.size(); i++) cout << peak[i] << " ";
        cout << endl;
    }
public:
    int numPermsDISequence(string S) {
        /*
        get_peak(S);
        vector<LL> f;
        f.push_back(1);
        int peak_sum = peak[0];
        for(int i = 1; i < peak.size(); i++) {
            peak_sum += peak[i];
            f.push_back(f.back() * peak_sum);
            if(S[i - 1] == 'D' && i > 1) {
                f.back() = f.back() + 1;
            }
        }
        return f.back();
        */
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for(int i = 1; i <= S.size(); i++) {
            char curS = S[i - 1];
            if(curS == 'D') {
                for(int j = 0; j <= i; j++) {
                    for(int k = j; k <= i; k++) {
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
                    }
                }
            } else {
                for(int j = 0; j <= i; j++) {
                    for(int k = 0; k < j; k++) {
                        f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
                    }
                }
            }
        }
        LL ans = 0;
        for(int i = 0; i <= S.size(); i++) {
            ans = (ans + f[S.size()][i]) % mod;
        }
        return ans;
    }
};