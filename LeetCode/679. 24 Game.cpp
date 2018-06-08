#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

const double eps = 1e-6;

class Solution {
    bool dfs(vector<double> &nums) {
        if (nums.size() == 1) {
            return fabs(nums[0] - 24) < eps;
        }
        // search flow
        // 1. choose and remove arbitrarily two number in nums
        // 2. apply with a operation
        // 3. push it into nums
        vector<double> old = nums;
        for (int i = 0; i < old.size(); i++) {
            for (int j = i + 1; j < old.size(); j++) {
                // add
                double a = old[i], b = old[j];
                nums.erase(nums.begin() + i);
                nums.erase(nums.begin() + j - 1);
                vector<double> gt = nums;
                nums.push_back(a + b);
                if (dfs(nums)) return true;
                nums = gt;
                // substract
                nums.push_back(a - b);
                if (dfs(nums)) return true;
                nums = gt;

                nums.push_back(b - a);
                if (dfs(nums)) return true;
                nums = gt;

                // multiply
                nums.push_back(a * b);
                if (dfs(nums)) return true;
                nums = gt;

                // divide
                if (b != 0) {
                    nums.push_back(a / b);
                    if (dfs(nums)) return true;
                    nums = gt;
                }

                if (a != 0) {
                    nums.push_back(b / a);
                    if (dfs(nums)) return true;
                }

                nums = old;
            }
        }
        return false;
    }

   public:
    bool judgePoint24(vector<int> &nums) {
        vector<double> db;
        for (int i = 0; i < nums.size(); i++) {
            db.push_back(nums[i]);
        }
        return dfs(db);
    }
};