#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1e5 + 10;
int cnt[maxn];
int N;

vector<int> gao(int prev_count) {
    vector<int> ret;
    ret.push_back(0);
    ret.push_back(prev_count);
    for(int i = 2; i <= N; i++) {
        ret.push_back(cnt[i - 1] - prev_count);
        prev_count -= ret[i - 2];
        prev_count += ret.back();
    }
    /*
    printf("%d\n", (int)ret.size());
    printf("prev: %d\n", prev_count);
    for(int i = 1; i <= N; i++) printf("%d ", ret[i]); puts("");
    */
    return ret;
}

bool valid(vector<int> &ret) {
    for(int i = 1; i <= N; i++) {
        if(ret[i] < 0 || ret[i] > 1) return false;
        int sumv = ret[i] + ret[i - 1];
        if(i < N) sumv += ret[i + 1];
        if(sumv != cnt[i]) return false;
    }
    return true;
}

int main() {
    int T; 
    scanf("%d", &T);
    for(int kase = 1; kase <= T; kase++) {
        scanf("%d", &N);
        for(int i = 1; i <= N; i++) {
            scanf("%d", &cnt[i]);
        }
        if(N == 1) {
            if(cnt[1] == 1) printf("1 1\n0\n");
            else printf("0\n1 1\n");
            continue;
        }
        vector<int> ans;
        vector<int> ret = gao(0);
        if(valid(ret)) {
            ans = ret;
        }
        ret = gao(1);
        if(valid(ret)) {
            if(ans.size() == 0) {
                ans = ret;
            } else {
                for(int i = 1; i <= N; i++) {
                    if(ans[i] != ret[i]) {
                        ans[i] = -1;
                    }
                }
            }
        }
        int empty_count = 0, mine_count = 0;
        for(int i = 1; i <= N; i++) {
            if(ans[i] == 1) {
                ++mine_count;
            } else if(ans[i] == 0) {
                ++empty_count;
            }
        }
        printf("%d", mine_count);
        for(int i = 1; i <= N; i++) {
            if(ans[i] == 1) {
                printf(" %d", i);
            }
        }
        puts("");
        printf("%d", empty_count);
        for(int i = 1; i <= N; i++) {
            if(ans[i] == 0) {
                printf(" %d", i);
            }
        }
        puts("");
    }
    return 0;
}