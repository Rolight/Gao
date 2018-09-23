#include <cstdio>
#include <cstring>
#include <map>
#include <string>

using namespace std;

const int maxn = 3e5 + 100;

map<string, int> mp;
map<int, string> i2s;


int getID(string str) {
    int cur_id = mp.size() + 1;
    if(mp.count(str) == 0) {
        mp[str] = cur_id;
        i2s[cur_id] = str;
        // printf("%d: %s\n", cur_id, i2s[cur_id].c_str());
    } else {
        cur_id = mp[str];
    }
    return cur_id;
}

int head[maxn], nxt[maxn << 1], v[maxn << 1], ecnt;
int value[maxn], dep[maxn], out[maxn], vcnt;
pair<int, int> f[maxn][20];
int n, k;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

void init() {
    memset(head, -1, sizeof(head));
    vcnt = 0;
    ecnt = 0;
    mp.clear();
    i2s.clear();
}

void adde(int _u, int _v) {
    v[ecnt] = _v;
    nxt[ecnt] = head[_u];
    head[_u] = ecnt++;
}

void dfs(int now, int nowfa, int nowdep) {
    value[++vcnt] = now;
    dep[vcnt] = nowdep;
    for(int i = head[now]; i != -1; i = nxt[i]) {
        if(v[i] == nowfa) continue;
        dfs(v[i], now, nowdep + 1);
        value[++vcnt] = now;
        dep[vcnt] = nowdep;
    }
    out[now] = vcnt;
}

void initRMQ() {
   for(int i = 1; i <= vcnt; i++) f[i][0] = make_pair(dep[i], value[i]);
    for(int k = 1; (1 << k) <= vcnt; k++) {
        for(int i = 1; i + (1 << k) <= vcnt + 1; i++) {
            f[i][k] = min(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int query(int a, int b) {
    if(a > b) swap(a, b);
    int len = b - a + 1;
    int k = 0;
    while(1 << (k + 1) <= len) ++k;
    return min(f[a][k], f[b - (1 << k) + 1][k]).second;
}

char buf[1024];

int getstr() {
    scanf("%s", buf);
    return getID(buf);
}

int isroot[maxn];

int main() { 
    int n, N;
    scanf("%d", &n);
    init();
    memset(isroot, -1, sizeof(isroot));
    for(int i = 0; i < n; i++) {
        int uu = getstr();
        int vv = getstr();
        adde(uu, vv);
        isroot[vv] = 0;
    }
    N = mp.size();
    for(int i = 1; i <= N; i++) {
        if(isroot[i] == -1) {
            // printf("find root %d\n", i);
            dfs(i, -1, 1);
            break;
        }
    }
    // for(int i = 1; i <= vcnt; i++) printf("%d ", dep[i]); puts("");
    initRMQ();
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        int ql = getstr();
        int qr = getstr();
        int ans = query(out[ql], out[qr]);
        printf("%s\n", i2s[ans].c_str());
    }
    return 0;
}