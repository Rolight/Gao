#include <cstdio>
#include <cstring>
#include <map>
#include <string>

using namespace std;

const int maxn = 1e5 + 100;

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

int ans[maxn];
int state[maxn];
int fa[maxn];
int n;
int k;

char buf[maxn];

int getstr() {
    scanf("%s", buf);
    return getID(buf);
}

int query(int a, int b, int id) {
    for(int i = a; i != 0; i = fa[i]) {
        state[i] = id;
        if(i == b) return b;
    }
    for(int i = b; i != 0; i = fa[i]) {
        if(state[i] == id) return i;
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int a = getstr();
        int b = getstr();
        fa[b] = a;
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        int a = getstr();
        int b = getstr();
        ans[i] = query(a, b, i + 1);
        if(ans[i] == -1) puts("-1");
        else printf("%s\n", i2s[ans[i]].c_str());
    }
    return 0;
}