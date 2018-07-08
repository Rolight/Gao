#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

class Solution {
    void cover(vector<int> &chunk_id, int l, int r, int id) {
        for (int i = l; i <= r; i++) chunk_id[i] = id;
    }

   public:
    int maxChunksToSorted(vector<int> &arr) {
        vector<PII> arr_with_idx;
        for (int i = 0; i < arr.size(); i++) {
            arr_with_idx.push_back(make_pair(arr[i], i));
        }
        sort(arr_with_idx.begin(), arr_with_idx.end());
        vector<int> chunk_id(arr.size(), -1);
        int pos = 0;
        int chunk_cnt = 0;
        while (pos < arr.size()) {
            int cur_min_pos = pos, cur_max_pos = pos;
            set<int> cur_vals;
            cur_vals.insert(chunk_id[pos]);
            for (int cur_pos = arr_with_idx[pos].second; cur_pos != pos;
                 cur_pos = arr_with_idx[cur_pos].second) {
                cur_min_pos = min(cur_min_pos, cur_pos);
                cur_max_pos = max(cur_max_pos, cur_pos);
                cur_vals.insert(chunk_id[cur_pos]);
            }
            if (cur_vals.size() == 1 && *cur_vals.begin() == -1) {
                cover(chunk_id, cur_min_pos, cur_max_pos, ++chunk_cnt);
            } else {
                cur_vals.erase(-1);
                cover(chunk_id, cur_min_pos, cur_max_pos, *cur_vals.begin());
            }
            pos++;
        }
        set<int> final_vals;
        for (int i = 0; i < arr.size(); i++) final_vals.insert(chunk_id[i]);
        // for(int i = 0; i < arr.size(); i++) printf("%d ", chunk_id[i]);
        // puts("");
        chunk_cnt = final_vals.size();
        return chunk_cnt;
    }
};