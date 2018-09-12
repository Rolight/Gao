// Hiho01 Manacher Algorithm

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;
char buf[maxn], str[maxn * 2];
int f[maxn * 2];

int manacher(char *buf, int *f, int len) {
    f[0] = 0;
    int max_pos = 0;
    int ans = 0;
    int loop = 0;
    for(int i = 1; i < len; i++) {
        int max_right = max_pos + f[max_pos];
        if(i > max_right) {
            f[i] = 0;
        } else {
           f[i] = min(max_right - i, f[max_pos - i + max_pos]);
        }
        for(;buf[i - f[i]] == buf[i + f[i]]; f[i]++) ;
        ans = max(ans, f[i]);
        if(i + f[i] > f[max_pos] + max_pos) {
            max_pos = i;
        }
    }
    return ans - 1;
}

int main() {
    int T;
    scanf("%d", &T);
    for(int kase = 1; kase <= T; kase++) {
        scanf("%s", buf);
        int cnt = 0;
        str[cnt++] = '$';
        str[cnt++] = '#';
        for (int i = 0; buf[i] != 0; i++) {
            str[cnt++] = buf[i];
            str[cnt++] = '#';
        }
        int ans = manacher(str, f, cnt);
        printf("%d\n", ans);
    }
    return 0;
}