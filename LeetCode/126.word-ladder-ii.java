import static java.lang.Math.*;
import static java.util.Arrays.*;

/*
 * [126] Word Ladder II
 *
 * https://leetcode.com/problems/word-ladder-ii/description/
 *
 * algorithms
 * Hard (14.83%)
 * Total Accepted:    81.3K
 * Total Submissions: 547.7K
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 *
 * Given two words (beginWord and endWord), and a dictionary's word list, find
 * all shortest transformation sequence(s) from beginWord to endWord, such
 * that:
 *
 *
 * Only one letter can be changed at a time
 * Each transformed word must exist in the word list. Note that beginWord is
 * not a transformed word.
 *
 *
 *
 * For example,
 *
 *
 * Given:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log","cog"]
 *
 *
 * Return
 *
 * ⁠ [
 * ⁠   ["hit","hot","dot","dog","cog"],
 * ⁠   ["hit","hot","lot","log","cog"]
 * ⁠ ]
 *
 *
 *
 *
 * Note:
 *
 * Return an empty list if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 * You may assume no duplicates in the word list.
 * You may assume beginWord and endWord are non-empty and are not the same.
 *
 *
 *
 *
 * UPDATE (2017/1/20):
 * The wordList parameter had been changed to a list of strings (instead of a
 * set of strings). Please reload the code definition to get the latest
 * changes.
 *
 */
import java.util.*;

class Solution {
    static int INF = 1000000000;

    List<List<Integer> > link;

    public int getDis(String word1, String word2) {
        if (word1.length() != word2.length())
            return -1;
        int ret = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1.charAt(i) != word2.charAt(i)) {
                ret++;
            }
        }
        return ret;
    }

    public void getPath(int now, List<String> cur_path, List<List<String> > all_path,
        List<String> wordList, int end_id, int[] min_dis) {
        if (now == end_id) {
            all_path.add(new ArrayList<>(cur_path));
            return;
        }
        for (int i = 0; i < link.get(now).size(); i++) {
            int nxt = link.get(now).get(i);
            if (min_dis[nxt] == min_dis[now] + 1) {
                cur_path.add(wordList.get(nxt));
                getPath(nxt, cur_path, all_path, wordList, end_id, min_dis);
                cur_path.remove(cur_path.size() - 1);
            }
        }
    }

    public List<List<String> > findLadders(
        String beginWord, String endWord, List<String> wordList) {
        int str_id = wordList.size(), end_id = wordList.indexOf(endWord);

        link = new ArrayList<List<Integer> >();

        for (int i = 0; i < wordList.size() + 1; i++) {
            link.add(new ArrayList<Integer>());
        }

        for (int i = 0; i < wordList.size(); i++) {
            for (int j = i + 1; j < wordList.size(); j++) {
                if (getDis(wordList.get(i), wordList.get(j)) == 1) {
                    link.get(i).add(j);
                    link.get(j).add(i);
                }
            }
            if (getDis(wordList.get(i), beginWord) == 1) {
                link.get(str_id).add(i);
            }
        }

        int[] min_dis = new int[wordList.size() + 1];
        for (int i = 0; i < wordList.size(); i++) {
            min_dis[i] = INF;
        }
        min_dis[str_id] = 0;

        Queue<Integer> q = new LinkedList<Integer>();
        q.add(str_id);

        while (q.isEmpty() == false) {
            int now = q.remove();

            for (int i = 0; i < link.get(now).size(); i++) {
                int nxt = link.get(now).get(i);
                if (min_dis[now] + 1 > min_dis[nxt]) {
                    continue;
                }

                min_dis[nxt] = min_dis[now] + 1;
                q.add(nxt);
            }
        }

        List<List<String> > ans = new ArrayList<List<String> >();
        List<String> tmp = new ArrayList<String>();
        tmp.add(beginWord);
        getPath(str_id, tmp, ans, wordList, end_id, min_dis);
        return ans;
    }
}