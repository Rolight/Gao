#include <cstdio>
#include <cstring>
#include <map>
#include <string>

using namespace std;

const int maxn = 1e5 + 100;

map<string, int> mp;
map<int, string> i2s;
map<int, map<int, int> > query;


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
int headQ[maxn], nxtQ[maxn << 1], vQ[maxn << 1], ansQ[maxn << 1], ecntQ;
int fa[maxn];
int ans[maxn];
int state[maxn];
int n, k;

void init() {
    memset(head, -1, sizeof(head));
    memset(headQ, -1, sizeof(headQ));
    ecnt = 0;
    ecntQ = 0;
    mp.clear();
    i2s.clear();
    memset(ans, -1, sizeof(ans));
    memset(state, -1, sizeof(state));
}

void adde(int _u, int _v) {
    v[ecnt] = _v;
    nxt[ecnt] = head[_u];
    head[_u] = ecnt++;
}

void addQ(int _u, int _v, int _id) {
    vQ[ecntQ] = _v;
    ansQ[ecntQ] = _id;
    nxtQ[ecntQ] = headQ[_u];
    headQ[_u] = ecntQ++;
}

// tarjan

int getfa(int x) {
    return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}

void dfs(int now, int nowfa) {
    state[now] = 0;
    // printf("%d, %d\n", now, nowfa);
    for(int i = headQ[now]; i != -1; i = nxtQ[i]) {
        if(state[vQ[i]] >= 0 && ans[ansQ[i]] == -1) {
            ans[ansQ[i]] = getfa(vQ[i]);
        }
    }
    for(int i = head[now]; i != -1; i = nxt[i]) {
        if(v[i] == nowfa) continue;
        dfs(v[i], now);
        fa[v[i]] = now;
    }
    state[now] = 1;
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
        int uu = getstr(), vv = getstr();
        adde(uu, vv);
        isroot[vv] = 0;
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        int ql = getstr(), qr = getstr();
        addQ(ql, qr, i);
        addQ(qr, ql, i);
    }
    N = mp.size();
    for(int i = 1; i <= N; i++) fa[i] = i;
    for(int i = 1; i <= N; i++) {
        if(isroot[i] == -1) {
            // printf("find root %d\n", i);
            dfs(i, -1);
            break;
        }
    }
    for(int i = 0; i < k; i++) {
        // printf("ans: %d\n", ans[i]);
        if(ans[i] == -1) puts("-1");
        else printf("%s\n", i2s[ans[i]].c_str());
    }
    return 0;
}