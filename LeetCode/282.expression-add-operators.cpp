/*
 * [282] Expression Add Operators
 *
 * https://leetcode.com/problems/expression-add-operators/description/
 *
 * algorithms
 * Hard (30.60%)
 * Total Accepted:    46.6K
 * Total Submissions: 152.1K
 * Testcase Example:  '"123"\n6'
 *
 *
 * Given a string that contains only digits 0-9 and a target value, return all
 * possibilities to add binary operators (not unary) +, -, or * between the
 * digits so they evaluate to the target value.
 *
 *
 * Examples:
 * "123", 6 -> ["1+2+3", "1*2*3"]
 * "232", 8 -> ["2*3+2", "2+3*2"]
 * "105", 5 -> ["1*0+5","10-5"]
 * "00", 0 -> ["0+0", "0-0", "0*0"]
 * "3456237490", 9191 -> []
 *
 *
 * Credits:Special thanks to @davidtan1890 for adding this problem and creating
 * all test cases.
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

class Solution {
    vector<string> ans;
    string num;
    LL target;
    string all_opr = "+-*";

   public:
    void calc(vector<char> &oprs, vector<LL> &nums) {
        if (oprs.size() == 0) return;
        LL a = nums.back();
        nums.pop_back();
        LL b = nums.back();
        nums.pop_back();
        LL ans;
        char last_opr = oprs.back();
        oprs.pop_back();
        if (last_opr == '*') {
            ans = a * b;
        }
        if (last_opr == '+') {
            ans = a + b;
        }
        if (last_opr == '-') {
            ans = b - a;
        }
        nums.push_back(ans);
    }
    void dfs(LL cur_pos, string &cur_exp, vector<LL> nums, vector<char> oprs) {
        if (cur_pos == num.size()) {
            while (oprs.size() > 0) {
                calc(oprs, nums);
            }
            LL cur_val = nums[0];
            if (cur_val == target) ans.push_back(cur_exp);
            return;
        }
        // pass
        if (nums.back() != 0) {
            LL n = nums.size();
            LL cur_back = nums[n - 1];
            nums[n - 1] = cur_back * 10 + num[cur_pos] - '0';
            if (nums[n - 1] <= 1e17 && nums[n - 1] >= -1e17) {
                cur_exp.push_back(num[cur_pos]);
                dfs(cur_pos + 1, cur_exp, nums, oprs);
                cur_exp.pop_back();
            }
            nums[n - 1] = cur_back;
        }
        // add opr
        // exp: xxxx + x
        vector<char> tmp_oprs = oprs;
        vector<LL> tmp_nums = nums;
        for (LL i = 0; i < all_opr.size(); i++) {
            char copr = all_opr[i];
            while (oprs.size() > 0 && (copr != '*' || oprs.back() == '*')) {
                calc(oprs, nums);
            }
            oprs.push_back(copr);
            nums.push_back(num[cur_pos] - '0');
            cur_exp.push_back(copr);
            cur_exp.push_back(num[cur_pos]);
            dfs(cur_pos + 1, cur_exp, nums, oprs);
            cur_exp.pop_back();
            cur_exp.pop_back();
            oprs = tmp_oprs;
            nums = tmp_nums;
        }
    }
    vector<string> addOperators(string num, int target) {
        this->num = num;
        this->ans.clear();
        this->target = target;
        if (num.size() == 0) return ans;
        string cur_exp = string("") + num[0];
        vector<LL> nums;
        nums.push_back(num[0] - '0');
        vector<char> oprs;
        dfs(1, cur_exp, nums, oprs);
        return this->ans;
    }
};

int main() {
    string num;
    LL target;
    Solution s;
    while (cin >> num >> target) {
        vector<string> ans = s.addOperators(num, target);
        cout << "found " << ans.size() << endl;
        for (LL i = 0; i < ans.size(); i++) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
