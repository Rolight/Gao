#include <algorithm>
#include <cstdio>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int deno_id, numo_id;
    vector<int> *A;

    Node(vector<int> *A, int numo_id, int deno_id)
        : A(A), numo_id(numo_id), deno_id(deno_id) {}

    bool operator<(const Node &x) {
        double cur_val = (double)(*A)[numo_id] / (double)(*A)[deno_id];
        double x_val = (double)(*A)[x.numo_id] / (double)(*A)[x.deno_id];
        return cur_val > x_val;
    }
};

class Solution {
   public:
    vector<int> kthSmallestPrimeFraction(vector<int> &A, int K) {
        priority_queue<Node> pq;
        // init queue
        for (int i = 1; i < A.size(); i++) {
            pq.push(Node(&A, 0, i));
        }

        for (int i = 1; i < K; i++) {
            Node cur = pq.top();
            pq.pop();
            if (cur.numo_id + 1 < cur.deno_id) {
                cur.numo_id++;
                pq.push(cur);
            }
        }

        vector<int> ans;
        ans.push_back(A[pq.top().numo_id]);
        ans.push_back(A[pq.top().deno_id]);
        return ans;
    }
};