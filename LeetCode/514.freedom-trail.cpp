/*
 * [514] Freedom Trail
 *
 * https://leetcode.com/problems/freedom-trail/description/
 *
 * algorithms
 * Hard (39.16%)
 * Total Accepted:    8.8K
 * Total Submissions: 22.4K
 * Testcase Example:  '"godding"\n"gd"'
 *
 *
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to
 * reach a metal dial called the "Freedom Trail Ring", and use the dial to
 * spell a specific keyword in order to open the door.
 *
 *
 *
 * Given a string ring, which represents the code engraved on the outer ring
 * and another string key, which represents the keyword needs to be spelled.
 * You need to find the minimum number of steps in order to spell all the
 * characters in the keyword.
 *
 * Initially, the first character of the ring is aligned at 12:00 direction.
 * You need to spell all the characters in the string key one by one by
 * rotating the ring clockwise or anticlockwise to make each character of the
 * string key aligned at 12:00 direction and then by pressing the center
 * button.
 *
 *
 * At the stage of rotating the ring to spell the key character key[i]:
 *
 * You can rotate the ring clockwise or anticlockwise one place, which counts
 * as 1 step. The final purpose of the rotation is to align one of the string
 * ring's characters at the 12:00 direction, where this character must equal to
 * the character key[i].
 *
 * If the character key[i] has been aligned at the 12:00 direction, you need to
 * press the center button to spell, which also counts as 1 step. After the
 * pressing, you could begin to spell the next character in the key (next
 * stage), otherwise, you've finished all the spelling.
 *
 *
 *
 *
 * Example:
 *
 *
 *
 *
 *
 * Input: ring = "godding", key = "gd"
 * Output: 4
 * Explanation: For the first key character 'g', since it is already in place,
 * we just need 1 step to spell this character.  For the second key character
 * 'd', we need to rotate the ring "godding" anticlockwise by two steps to make
 * it become "ddinggo". Also, we need 1 more step for spelling. So the final
 * output is 4.
 *
 *
 *
 * Note:
 *
 * Length of both ring and key will be in range 1 to 100.
 * There are only lowercase letters in both strings and might be some duplcate
 * characters in both strings.
 * It's guaranteed that string key could always be spelled by rotating the
 * string ring.
 *
 *
 */
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int findRotateSteps(string ring, string key) {
        int slen = ring.length(), klen = key.length();
        int inf = 1e7;
        vector<int> tmp(slen, inf);
        vector<vector<int> > f(klen + 1, tmp);
        vector<int> pos[26];

        for (int i = 0; i < slen; i++) {
            pos[ring[i] - 'a'].push_back(i);
        }

        f[0][0] = 0;
        for (int i = 0; i < pos[key[0] - 'a'].size(); i++) {
            int end_pos = pos[key[0] - 'a'][i];
            f[1][end_pos] =
                min(f[1][end_pos], min(end_pos, (slen - end_pos) % slen) + 1);
            // printf("f[%d][%d] = %d\n", 1, end_pos, f[1][end_pos]);
        }
        for (int i = 1; i < klen; i++) {
            for (int j = 0; j < pos[key[i - 1] - 'a'].size(); j++) {
                for (int k = 0; k < pos[key[i] - 'a'].size(); k++) {
                    int end_pos = pos[key[i] - 'a'][k];
                    int start_pos = pos[key[i - 1] - 'a'][j];
                    int dis = (end_pos - start_pos + slen) % slen;
                    dis = min(dis, (slen - dis) % slen);
                    // printf("%c to %c, dis %d\n", key[i - 1], key[i], dis);
                    f[i + 1][end_pos] =
                        min(f[i + 1][end_pos], f[i][start_pos] + dis + 1);
                    // printf("f[%d][%d] = %d\n", i + 1, end_pos, f[i +
                    // 1][end_pos]);
                }
            }
        }
        int ans = inf;
        for (int i = 0; i < pos[key[klen - 1] - 'a'].size(); i++) {
            ans = min(ans, f[klen][pos[key[klen - 1] - 'a'][i]]);
        }
        return ans;
    }
};
