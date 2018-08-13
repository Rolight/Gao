#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

const int max_state = 46656 + 10;

using namespace std;

class Solution {
    int slen;
    unordered_map<string, int> hashp;

    int dis(string &a, string &b) {
        int ret = 0;
        for (int i = 0; i < slen; i++) {
            if (a[i] != b[i]) ret++;
        }
        return ret;
    }

   public:
    int bfs(string ori, string tar) {
        hashp.clear();
        queue<string> q;
        q.push(ori);
        hashp[ori] = 0;
        while (!q.empty()) {
            string now = q.front();
            q.pop();
            for (int i = 0; i < now.length(); i++) {
                if (now[i] == tar[i]) continue;
                for (int j = i + 1; j < now.length(); j++) {
                    if (now[j] != tar[j] && tar[j] == now[i]) {
                        string buf = now;
                        swap(buf[i], buf[j]);
                        if (hashp.count(buf)) continue;
                        hashp[buf] = hashp[now] + 1;
                        if (buf == tar) return hashp[buf];
                        q.push(buf);
                    }
                }
                break;
            }
        }
        return -1;
    }

    int kSimilarity(string A, string B) {
        if (A == B) return 0;
        slen = A.length();
        return bfs(A, B);
    }
};

int main() {
    string a, b;
    Solution s;
    while (cin >> a >> b) {
        cout << s.kSimilarity(a, b) << endl;
    }
    return 0;
}