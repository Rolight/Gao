/*
 *   Simple 2d-KDTree implement to solve http://acm.split.hdu.edu.cn/showproblem.php?pid=2966
 *   The question is given a certain amount of points and find each point's nearest point and
 *   output the distance
 */

// 大数据对拍了好久都没错，但就是WA 不想费时间调了

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>

struct Point {
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
    Point operator-(const Point &p) {
        return Point(x-p.x, y-p.y);
    }
    std::string intstr() {
        char buf[128];
        sprintf(buf, "(%.0f, %.0f)", x, y);
        return std::string(buf);
    }
    bool operator == (const Point &p) {
        return x == p.x && y == p.y;
    }
};

typedef Point Vector;

struct Rect {
    Point lt, rd;
    Rect(Point lt, Point rd): lt(lt), rd(rd) {}
    Rect() {}
};

struct KDNode {
    Point point;
    Rect region;
    KDNode *lch, *rch, *father;
    KDNode() {}
};

double distance(Point p1, Point p2) {
    Point p = p1 - p2;
    return std::sqrt(p.x * p.x + p.y * p.y);
}

double norm(Vector v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

double Dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

const double eps = 1e-9;

double point_segment_distance(Point p, Point a, Point b)
{
    Vector AP = p - a, AB = b - a;
    double dot = Dot(AP, AB);
    double dab = norm(AB) * norm(AB);
    if (dot < eps)
         return distance(p, a);
    if (dot > dab + eps)
        return distance(p, b);

    double r = dot / dab;
    double cx = a.x + (b.x - a.x) * r;
    double cy = a.y + (b.y - a.y) * r;
    return distance(p, Point(cx, cy));
}


double point_region_distance(Point p, Rect region) {
    Point lt = region.lt, rd = region.rd;
    // Point in this region
    if(p.x >= lt.x && p.x <= rd.x && p.y <= lt.y && p.y >= rd.y) {
        return 0;
    }
    Point a0 = Point(lt.x, lt.y),
          a1 = Point(lt.x, rd.y),
          a2 = Point(rd.x, rd.y),
          a3 = Point(rd.x, lt.y);
    // printf("%s, %s %s, %s\n",
    //         a0.intstr().c_str(),
    //         a1.intstr().c_str(),
    //         a2.intstr().c_str(),
    //         a3.intstr().c_str()
    //       );
    /*
    printf("%.4f %.4f %.4f %.4f\n",
                point_segment_distance(p, a0, a1),
                point_segment_distance(p, a1, a2),
                point_segment_distance(p, a2, a3),
                point_segment_distance(p, a3, a0));
    */



    double ret = std::min(
            std::min(
                point_segment_distance(p, a0, a1),
                point_segment_distance(p, a1, a2)
            ),
            std::min(
                point_segment_distance(p, a2, a3),
                point_segment_distance(p, a3, a0)
            )
    );
    return ret;
}

const int maxn = 2e5 + 10;
const double DINF = 1e20;

Point p[maxn], orip[maxn];
KDNode node[maxn];
int nodesz;

void init() {
    nodesz = 0;
}

KDNode *newNode() {
    return &node[nodesz++];
}

// cmp function for nth_element
bool cmp0(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool cmp1(const Point &a, const Point &b) {
    return a.y < b.y;
}

typedef bool (*cmp_function)(const Point &, const Point &);
cmp_function cmps[2] = {cmp0, cmp1};


KDNode *build_kdtree(int l, int r, int d, Point lt, Point rd, KDNode *father=NULL) {
    if (l > r) return NULL;

    int mid = (l + r + 1) / 2;

    std::nth_element(p + l, p + mid, p + r + 1, cmps[d % 2]);

    KDNode *now = newNode();
    // current kdnode region and point
    now->point = p[mid];
    //printf("current mid is %s\n", now->point.intstr().c_str());
    now->region = Rect(lt, rd);
    now->father = father;
    // child region, left lt, left rd, right lt, right rd
    Point llt, lrd, rlt, rrd;
    if (d % 2 == 0) {
        // split by x
        llt = lt;
        lrd = Point(p[mid].x, rd.y);
        rlt = Point(p[mid].x, lt.y);
        rrd = rd;
    } else {
        // split by y
        llt = Point(lt.x, p[mid].y);
        lrd = rd;
        rlt = lt;
        rrd = Point(rd.x, p[mid].y);
    }
    now->lch = build_kdtree(l, mid - 1, d + 1, llt, lrd, now);
    now->rch = build_kdtree(mid + 1, r, d + 1, rlt, rrd, now);
    return now;
}

int kdcount = 0;
void kdFind(Point p, double &min_dis, KDNode *cur) {
    kdcount++;
    double cur_dis = p == cur->point ? DINF * DINF : distance(p, cur->point);
    double dl = DINF * DINF, dr = DINF * DINF;
    min_dis = std::min(min_dis, cur_dis);
    if(cur->lch != NULL) {
        dl = point_region_distance(p, cur->lch->region);
    }
    if(cur->rch != NULL) {
        dr = point_region_distance(p, cur->rch->region);
    }
    // printf("dl = %lf\ndr = %lf\n", dl, dr);
    /*
     *  if dl < dr search lchild first, otherwise search rchild first
     */
    if (dl < dr) {
        if (dl < min_dis) {
            kdFind(p, min_dis, cur->lch);
        }
        if (dr < min_dis) {
            kdFind(p, min_dis, cur->rch);
        }
    } else {
        if (dr < min_dis) {
            kdFind(p, min_dis, cur->rch);
        }
        if (dl < min_dis) {
            kdFind(p, min_dis, cur->lch);
        }
    }
}

void printTree(KDNode *now) {
    if (now == NULL) return;
    printf("%s, region= %s, %s\n", now->point.intstr().c_str(),
            now->region.lt.intstr().c_str(),
            now->region.rd.intstr().c_str());
    printTree(now->lch);
    printTree(now->rch);
}

int main() {
    int T; scanf("%d", &T);
    for(int kase = 1; kase <=T; ++kase) {
        init();
        int n; scanf("%d", &n);
        double maxv = 0;
        for(int i = 1; i <= n; i++) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            orip[i] = p[i] = Point(x, y);
            maxv = std::max(maxv, std::max(x, y));
        }
        // region boundary value
        maxv += 10;
        KDNode *tree = build_kdtree(1, n, 0, Point(0, maxv), Point(maxv, 0));
        for(int i = 1; i <= n; i++) {
            double min_dis = DINF * DINF;
            kdFind(orip[i], min_dis, tree);
            printf("%.0f\n", std::round(min_dis * min_dis));
        }
        // printf("kdcount = %d\n", kdcount);
    }
    return 0;
}
