#include <cstdio>
#include <string>
#include <vector>

using namespace std;

const int maxn = 1e6 + 10;
char pattern[maxn], buf[maxn];
int fail[maxn];

int get_fail(char *buf) {
    int i;
    fail[0] = 0;
    for(i = 1; buf[i] != 0; ++i) {
        int j = fail[i - 1];
        while(j > 0 && buf[i] != buf[j]) j = fail[j - 1];
        fail[i] = buf[i] == buf[j] ? j + 1 : 0;
    }
    return i;
}

int match_count(char *buf, char *pattern, int *fail) {
    int ret = 0;
    for(int i = 0, j = 0; ;) {
        if(pattern[i] == 0) {
            ++ret;
        }
        if(buf[j] == 0) break;
        if(pattern[i] == buf[j]) {
            ++i; ++j;
        } else if(i == 0) {
            ++j;
        }
        else {
            while(i > 0 && pattern[i] != buf[j]) i = fail[i - 1];
        }
    }
    return ret;
}

int main() {
    int N;
    scanf("%d", &N);
    for(int kase = 1; kase <= N; kase++) {
        scanf("%s%s", pattern, buf);
        // scanf("%s", pattern);
        get_fail(pattern);
        printf("%d\n", match_count(buf, pattern, fail));
    }
    return 0;
}