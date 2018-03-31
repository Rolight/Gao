/*
 * [123] Best Time to Buy and Sell Stock III
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
 *
 * algorithms
 * Hard (30.33%)
 * Total Accepted:    105.7K
 * Total Submissions: 348.6K
 * Testcase Example:  '[]'
 *
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 *
 * Design an algorithm to find the maximum profit. You may complete at most two
 * transactions.
 *
 * Note:
 * You may not engage in multiple transactions at the same time (ie, you must
 * sell the stock before you buy again).
 */
import static java.lang.Math.*;
class Solution {
    public int maxProfit(int[] prices) {
        if (prices.length < 2) {
            return 0;
        }
        int maxProf[] = new int[prices.length];
        int curMin = prices[0];
        int ans = 0;
        for (int i = 1; i < prices.length; i++) {
            curMin = min(curMin, prices[i]);
            maxProf[i] = max(maxProf[i - 1], prices[i] - curMin);
            ans = max(ans, maxProf[i]);
        }
        int curMax = prices[prices.length - 1];
        for (int i = prices.length - 2; i >= 0; i--) {
            curMax = max(curMax, prices[i]);
            if (i - 1 > 0) {
                ans = max(ans, maxProf[i - 1] + curMax - prices[i]);
            }
        }
        return ans;
    }
}
