#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 1e5 + 10;
int N, M;
char cmd;
int val;

int heap[maxn << 2], hsize;

void init() {
    hsize = 0;
}

void push(int val) {
    heap[++hsize] = val;
    int u = hsize;
    while(u > 1 && heap[u] > heap[u / 2]) {
        swap(heap[u], heap[u / 2]);
        u >>= 1;
    }
}

int top() {
    return heap[1];
}

void pop() {
    swap(heap[1], heap[hsize]);
    --hsize;
    int u = 1;
    while(u <= hsize) {
        int swap_id = u;
        if(u * 2 <= hsize && heap[u * 2] > heap[swap_id]) swap_id = u * 2;
        if(u * 2 + 1 <= hsize && heap[u * 2 + 1] > heap[swap_id]) swap_id = u * 2 + 1;
        if(swap_id == u) break;
        swap(heap[swap_id], heap[u]);
        u = swap_id;
    }
}


int main() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf(" %c", &cmd);
        if(cmd == 'T') {
            printf("%d\n", top());
            pop();
        } else {
            scanf("%d", &val);
            push(val);
        }
    }
    return 0;
}