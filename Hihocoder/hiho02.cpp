#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1e5 + 10;
const int sigma_size = 26;
const int max_node = maxn * sigma_size;

struct TrieNode {
    TrieNode *ch[sigma_size];
    int sz;
};

TrieNode node[max_node];
int cnt;

void initTrie() {
    cnt = 1;
    memset(node[0].ch, 0, sizeof(node[0].ch));
}

TrieNode *newNode() {
    TrieNode *ret = &node[cnt];
    memset(node[cnt].ch, 0, sizeof(node[cnt].ch));
    ++cnt;
    return ret;
}

void insert(char *buf) {
    TrieNode *u = &node[0];
    for(int i = 0; buf[i] != 0; i++) {
        int cur_ch = buf[i] - 'a';
        ++u->sz;
        if(u->ch[cur_ch] == NULL) {
            u->ch[cur_ch] = newNode();
        }
        u = u->ch[cur_ch];
    }
    ++u->sz;
}

int query(char *buf) {
    TrieNode *u = &node[0];
    int ret = 0;
    for(int i = 0; buf[i] != 0; i++) {
        int cur_ch = buf[i] - 'a';
        if(u->ch[cur_ch] == NULL) return 0;
        u = u->ch[cur_ch];
    }
    return u->sz;
}

char buf[256];

int main() {
    int n, m;
    while(scanf("%d", &n) != EOF) {
        initTrie();
        for(int i = 0; i < n; i++) {
            scanf("%s", buf);
            insert(buf);
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            scanf("%s", buf);
            int ret = query(buf);
            printf("%d\n", ret);
        }
    }
    return 0;
}