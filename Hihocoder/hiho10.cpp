#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 128;
char pre[maxn], mid[maxn];
int N;

void gao(int pl, int pr, int ml, int mr) {
    if(pl > pr) return;
    char root = pre[pl];
    int root_pos = ml;
    while(mid[root_pos] != root) ++root_pos;
    int lsize = root_pos - ml;
    int rsize = mr - root_pos;
    gao(pl + 1, pl + lsize, ml, root_pos - 1);
    gao(pr - rsize + 1, pr, root_pos + 1, mr);
    putchar(root);
}

int main() {
    scanf("%s%s", pre, mid);
    N = strlen(pre);
    gao(0, N - 1, 0, N - 1);
    puts("");
    return 0;
}