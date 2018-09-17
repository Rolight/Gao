#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;


const int maxn = 1e6 + 10;
const int maxnode = maxn;
const int sigma_size = 26;

struct AC_automaton {
    int sz;
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int fail[maxnode];

    void init() {
        memset(ch[0], 0, sizeof(ch[0]));
        fail[0] = val[0] = 0;
        sz = 1;
    }

    inline int idx(char c) {
        return c - 'a';
    }

    void insert(char *str) {
        int u = 0;
        for(int i = 0; str[i] != 0; i++) {
            int c = idx(str[i]);
            if(ch[u][c] == 0) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                fail[sz] = val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u]++;
    }

    void construct() {
        queue<int> q;
        int u = 0;
        for(int i = 0; i < sigma_size; i++) {
            if(ch[u][i]) {
                fail[ch[u][i]] = 0;
                q.push(ch[u][i]);
            }
        }
        while(!q.empty()) {
            u = q.front(); 
            q.pop();
            for(int i = 0; i < sigma_size; i++) {
                int &v = ch[u][i];
                if(v) {
                    q.push(v);
                    fail[v] = ch[fail[u]][i];
                } else {
                    v = ch[fail[u]][i];
                }
            }
        }
    }

    int query(char *str) {
        int u = 0;
        int ans = 0;
        for(int i = 0; str[i] != 0; i++) {
            int c = idx(str[i]);
            u = ch[u][c];
            int v = u;
            while(v && val[v] != 0) {
                ans += val[v];
                // val[v] =  0;
                v = fail[v];
            }
        }
        return ans;
    }
};

char buf[maxn];
AC_automaton ac;

int main() {
    ac.init();
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%s", buf);
        ac.insert(buf);
    }
    ac.construct();
    scanf("%s", buf);
    int ret = ac.query(buf);
    // printf("ans: %d\n", ret);
    if(ret > 0) puts("YES");
    else puts("NO");
    return 0;
}