/*
 * [295] Find Median from Data Stream
 *
 * https://leetcode.com/problems/find-median-from-data-stream/description/
 *
 * algorithms
 * Hard (29.58%)
 * Total Accepted:    59.9K
 * Total Submissions: 201.9K
 * Testcase Example:
 * '["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]\n[[],[1],[2],[],[3],[]]'
 *
 * Median is the middle value in an ordered integer list. If the size of the
 * list is even, there is no middle value. So the median is the mean of the two
 * middle value.
 * Examples:
 * [2,3,4] , the median is 3
 * [2,3], the median is (2 + 3) / 2 = 2.5
 *
 *
 * Design a data structure that supports the following two operations:
 *
 *
 * void addNum(int num) - Add a integer number from the data stream to the data
 * structure.
 * double findMedian() - Return the median of all elements so far.
 *
 *
 *
 * For example:
 *
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3)
 * findMedian() -> 2
 *
 *
 * Credits:Special thanks to @Louis1992 for adding this problem and creating
 * all test cases.
 */

#include <functional>
#include <queue>

using namespace std;

class MedianFinder {
    void maintain() {
        int lsize = left.size(), rsize = right.size();
        if (lsize == rsize || lsize == rsize + 1) {
            return;
        } else if (lsize == rsize + 2) {
            right.push(left.top());
            left.pop();
        } else if (rsize == lsize + 1) {
            left.push(right.top());
            right.pop();
        }
    }

    priority_queue<int> left;
    priority_queue<int, std::vector<int>, std::greater<int> > right;

   public:
    /** initialize your data structure here. */
    MedianFinder() {
        while (!left.empty()) left.pop();
        while (!right.empty()) right.pop();
    }

    void addNum(int num) {
        if ((left.empty() && right.empty()) ||
            (!left.empty() && num <= left.top())) {
            left.push(num);
        } else {
            right.push(num);
        }
        maintain();
    }

    double findMedian() {
        int lsize = left.size(), rsize = right.size();
        if (lsize == rsize) {
            return ((double)left.top() + (double)right.top()) / 2;
        } else {
            return left.top();
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */

int main() {
    MedianFinder m;
    int op, v;
    while (scanf("%d", &op) != EOF) {
        if (op == 1) {
            scanf("%d", &v);
            m.addNum(v);
        } else {
            printf("%.4f\n", m.findMedian());
        }
    }
}