#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<string> stks;
    string target;

    int full_mask;
    vector<int> f;

    int add(int mask, string &word) {
        int wpos = 0;
        for (int mpos = 0; mpos < target.length(); mpos++) {
            if (mask & (1 << mpos)) continue;
            while (wpos < word.size() && word[wpos] < target[mpos]) wpos++;
            if (wpos == word.size()) break;
            if (word[wpos] == target[mpos]) {
                mask |= (1 << mpos);
                ++wpos;
            }
        }
        return mask;
    }

    int gao(int cur) {
        if (cur == full_mask) return 0;
        if (f[cur] != -2) return f[cur];
        int ret = -1;
        for (int i = 0; i < stks.size(); i++) {
            int next_state = add(cur, stks[i]);
            if (next_state == cur) continue;
            int cur_ret = gao(next_state);
            if (cur_ret == -1) continue;
            if (ret == -1 || cur_ret + 1 < ret) {
                ret = cur_ret + 1;
            }
        }
        f[cur] = ret;
        return ret;
    }

   public:
    int minStickers(vector<string> &stickers, string target) {
        this->stks = stickers;
        this->target = target;
        this->full_mask = (1 << target.length()) - 1;
        sort(this->target.begin(), this->target.end());
        for (int i = 0; i < stks.size(); i++) {
            sort(stks[i].begin(), stks[i].end());
        }
        f = vector<int>(full_mask + 1, -2);
        return gao(0);
    }
};