/*
 * [135] Candy
 *
 * https://leetcode.com/problems/candy/description/
 *
 * algorithms
 * Hard (25.25%)
 * Total Accepted:    77.6K
 * Total Submissions: 307K
 * Testcase Example:  '[0]'
 *
 *
 * There are N children standing in a line. Each child is assigned a rating
 * value.
 *
 *
 * You are giving candies to these children subjected to the following
 * requirements:
 *
 *
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 *
 *
 * What is the minimum candies you must give?
 *
 */
class Solution {
    public int candy(int[] ratings) {
        int last = -1;
        int ans = 0;
        for (int i = 0; i < ratings.length; i++) {
            if (i == 0 || ratings[i] == ratings[i - 1]) {
                // equals to the previous element, just add 1
                last = 1;
                ans += 1;
            } else if (ratings[i] > ratings[i - 1]) {
                // large than previous element, put last + 1
                last += 1;
                ans += last;
            } else {
                // less then previous element, finding descending sequence.
                // we should adjust the last candy amount to large than descending sequence length
                int dec_len = 0;
                while (i < ratings.length && ratings[i] < ratings[i - 1]) {
                    i++;
                    dec_len++;
                }
                i--;

                if (last <= dec_len) {
                    ans += dec_len + 1 - last;
                }

                ans += (1 + dec_len) * dec_len / 2;
                last = 1;
            }
        }
        return ans;
    }
}
