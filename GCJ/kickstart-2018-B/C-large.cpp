#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long LL;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

const int maxn = 1e6 + 10;

int A, B, C, D, E, F, V1, H1, N, M;
vector<LL> points_value;
vector<pair<LL, LL> > points;
LL up_left[maxn], up_right[maxn], down_left[maxn], down_right[maxn];

// BIT
LL sum[maxn];

inline int lowbit(int x) { return x & (-x); }

void addv(int lim, int pos, int x) {
    while (pos <= lim) {
        sum[pos] += x;
        pos += lowbit(pos);
    }
}

LL query(int pos) {
    LL ret = 0;
    while (pos > 0) {
        ret += sum[pos];
        pos -= lowbit(pos);
    }
    return ret;
}

LL query(int l, int r) {
    if (r < l) return 0;
    return query(r) - query(l - 1);
}

int getID(LL value) {
    return lower_bound(points_value.begin(), points_value.end(), value) -
           points_value.begin() + 1;
}

LL solve() {
    // 离散化
    points_value.clear();
    for (int i = 0; i < N; i++) {
        points_value.push_back(points[i].first);
        points_value.push_back(points[i].second);
    }
    sort(points_value.begin(), points_value.end());
    points_value.erase(unique(points_value.begin(), points_value.end()),
                       points_value.end());
    // 对所有点进行排序
    sort(points.begin(), points.end());
    /*
    cout << "all points: " << endl;
    for (int i = 0; i < N; i++) {
        cout << points[i].first << ", " << points[i].second << endl;
    }
    */
    // 统计每个点的左上角和右上角有多少点
    int n = points_value.size();
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < points.size(); i++) {
        for (int j = i; j < points.size() && points[j].first == points[i].first;
             j++) {
            // 左上方的点
            int cur_H = getID(points[j].second);
            up_left[j] = query(1, cur_H - 1);
            // 右上方的点
            up_right[j] = query(cur_H + 1, n);
        }
        // 将当前V相同的的点的H值都插入到线段树中
        int j;
        for (j = i; j < points.size() && points[j].first == points[i].first;
             j++) {
            addv(n, getID(points[j].second), 1);
        }
        i = j - 1;
    }
    // 统计每个点左下角和右下角有多少个点
    memset(sum, 0, sizeof(sum));
    for (int i = points.size() - 1; i >= 0; i--) {
        for (int j = i; j >= 0 && points[j].first == points[i].first; j--) {
            // 左下方的点
            int cur_H = getID(points[j].second);
            down_left[j] = query(1, cur_H - 1);
            // 右下方的点
            down_right[j] = query(cur_H + 1, n);
        }
        int j;
        for (j = i; j >= 0 && points[j].first == points[i].first; j--) {
            addv(n, getID(points[j].second), 1);
        }
        i = j + 1;
    }
    // 统计每个点被多少个bounding box 包含
    LL ans = 0;
    for (int i = 0; i < points.size(); i++) {
        ans = ans + up_left[i] * down_right[i] + up_right[i] * down_left[i];
    }
    LL total = (LL)N * (LL)(N - 1) * (LL)(N - 2) / 2 / 3;
    // cout << "total: " << total << " ans: " << ans << endl;
    return total - ans;
}

int main() {
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; kase++) {
        points.clear();
        cin >> N >> V1 >> H1 >> A >> B >> C >> D >> E >> F >> M;
        points.push_back(make_pair(V1, H1));
        /*
            Vi = (A × Vi-1 + B × Hi-1 + C) modulo M
            Hi = (D × Vi-1 + E × Hi-1 + F) modulo M
        */
        LL last_V = V1, last_H = H1;
        for (int i = 1; i < N; i++) {
            LL cur_V = (A * last_V + B * last_H + C) % M;
            LL cur_H = (D * last_V + E * last_H + F) % M;
            points.push_back(make_pair(cur_V, cur_H));
            last_V = cur_V;
            last_H = cur_H;
        }
        LL ans = solve();
        cout << "Case #" << kase << ": " << ans << endl;
    }
    return 0;
}