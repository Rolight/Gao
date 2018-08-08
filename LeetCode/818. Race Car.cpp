#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>
#include <vector>

const int maxn = 1e4 + 10;
const int inf = 1e9;
const int R = 0;
const int A = 1;

using namespace std;

int f[maxn * 3][30];
map<int, int> s2r, r2s;
int N;

// speed level
// -14 .... -2 -1 -0 0 1 2 .... 14
// total 30

int get_speed(int speed) {
    speed -= 15;
    bool neg = false;
    if (speed < 0) {
        neg = true;
        speed = -speed;
        speed -= 1;
    }
    speed = (1 << speed);
    if (neg) speed = -speed;
    return speed;
}

void init() {
    for (int i = 0; i < 30; i++) {
        int speed = get_speed(i);
        s2r[i] = speed;
        r2s[speed] = i;
    }
    memset(f, -1, sizeof(f));
}

class QNode {
   public:
    int pos, speed, step;
    QNode(int pos, int speed, int step) : pos(pos), speed(speed), step(step) {}
};

class Solution {
    int bfs(int target) {
        if (target == 0) return 0;
        queue<QNode> q;
        q.push(QNode(0, r2s[1], 0));
        while (!q.empty()) {
            QNode node = q.front();
            q.pop();
            // A
            int cur_real_speed = s2r[node.speed];
            do {
                if (cur_real_speed > 0 && node.pos > target) {
                    break;
                }
                int next_pos = node.pos + cur_real_speed;
                int next_speed = r2s[cur_real_speed * 2];
                if (next_pos < -target || next_pos > 2 * target) break;
                if (next_speed < 0 || next_speed >= 30) break;
                if (f[next_pos + target][next_speed] != -1) break;
                f[next_pos + target][next_speed] = node.step + 1;
                q.push(QNode(next_pos, next_speed, node.step + 1));
                if (next_pos == target) return f[next_pos + target][next_speed];
            } while (false);
            // R
            do {
                int next_pos = node.pos;
                int next_speed = cur_real_speed;
                if (next_speed > 0)
                    next_speed = r2s[-1];
                else
                    next_speed = r2s[1];
                if (f[next_pos + target][next_speed] != -1) break;
                f[next_pos + target][next_speed] = node.step + 1;
                q.push(QNode(next_pos, next_speed, node.step + 1));
                if (next_pos == target) return f[next_pos + target][next_speed];
            } while (false);
        }
        return -1;
    }

   public:
    int racecar(int target) {
        init();
        return bfs(target);
    }
};

int main() {
    int n;
    scanf("%d", &n);
    Solution s;
    printf("%d\n", s.racecar(n));
    return 0;
}