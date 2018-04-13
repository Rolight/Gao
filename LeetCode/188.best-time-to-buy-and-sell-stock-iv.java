/*
 * [188] Best Time to Buy and Sell Stock IV
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
 *
 * algorithms
 * Hard (24.89%)
 * Total Accepted:    60.6K
 * Total Submissions: 243.4K
 * Testcase Example:  '2\n[]'
 *
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 *
 * Design an algorithm to find the maximum profit. You may complete at most k
 * transactions.
 *
 * Note:
 * You may not engage in multiple transactions at the same time (ie, you must
 * sell the stock before you buy again).
 *
 * Credits:Special thanks to @Freezen for adding this problem and creating all
 * test cases.
 */
import java.util.*;
import static java.lang.Math.*;
class Solution {
    public int maxProfit(int k, int[] prices) {
        if (prices.length < 2 || k == 0)
            return 0;
        k = min(k, prices.length / 2);
        if (k == prices.length / 2) {
            int ans = 0;
            for (int i = 1; i < prices.length; i++) {
                if (prices[i] - prices[i - 1] > 0) {
                    ans += prices[i] - prices[i - 1];
                }
            }
            return ans;
        }
        int[] sale = new int[k + 1];
        int[] buy = new int[k + 1];
        for (int i = 1; i <= k; i++) {
            buy[i] = Integer.MIN_VALUE;
        }
        for (int i = 0; i < prices.length; i++) {
            for (int j = 1; j <= k; j++) {
                buy[j] = max(buy[j], sale[j - 1] - prices[i]);
                sale[j] = max(sale[j], buy[j] + prices[i]);
            }
        }
        return sale[k];
    }
}
