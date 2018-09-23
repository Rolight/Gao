#include <cstdio>
#include <cstring>
#include <map>
#include <string>

using namespace std;

const int maxn = 1e5 + 10;

map<string, int> mp;

int getID(string str) {
    int cur_id = mp.size() + 1;
    if(mp.count(str) == 0) {
        mp[str] = cur_id;
    } else {
        cur_id = mp[str];
    }
    return cur_id;
}

char buf[2048];

int getstr() {
    scanf("%s", buf);
    return getID(buf);
}

int fa[maxn], relationship[maxn];
int n, N;
int ir[maxn], s1[maxn], s2[maxn];

void init() {
    for(int i = 1; i <= N; i++) {
        fa[i] = i;
        relationship[i] = 0;
    }
}

int getfa(int x) {
    return x == fa[x] ? x: fa[x] = getfa(fa[x]);
}

void merge(int a, int b)  {
    int fx = getfa(a), fy = getfa(b);
    if(fx != fy) {
        fa[fx] = fy;
    }
}

bool query(int a, int b) {
    int fx = getfa(a), fy = getfa(b);
    return fx == fy;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &ir[i]);
        s1[i] = getstr();
        s2[i] = getstr();
    }
    N = mp.size();
    init();
    for(int i = 0; i < n; i++) {
        if(ir[i] == 0) {
            merge(s1[i], s2[i]);
        } else {
            puts(query(s1[i], s2[i]) ? "yes" : "no");
        }
    }
    return 0;
}