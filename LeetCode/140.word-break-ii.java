/*
 * [140] Word Break II
 *
 * https://leetcode.com/problems/word-break-ii/description/
 *
 * algorithms
 * Hard (24.47%)
 * Total Accepted:    111.9K
 * Total Submissions: 456.7K
 * Testcase Example:  '"catsanddog"\n["cat","cats","and","sand","dog"]'
 *
 *
 * Given a non-empty string s and a dictionary wordDict containing a list of
 * non-empty words, add spaces in s to construct a sentence where each word is
 * a valid dictionary word. You may assume the dictionary does not contain
 * duplicate words.
 *
 *
 *
 * Return all such possible sentences.
 *
 *
 *
 * For example, given
 * s = "catsanddog",
 * dict = ["cat", "cats", "and", "sand", "dog"].
 *
 *
 *
 * A solution is ["cats and dog", "cat sand dog"].
 *
 *
 *
 * UPDATE (2017/1/4):
 * The wordDict parameter had been changed to a list of strings (instead of a
 * set of strings). Please reload the code definition to get the latest
 * changes.
 *
 */
import java.util.*;

class Solution {
    static long hash_seed = 131313131L;
    HashMap<Long, Integer> dictHash;
    long[] strHash;
    long[] seedPow;

    public void initHash(String s, List<String> wordDict) {
        for (int i = 0; i < s.length(); i++) {
            if (i == 0) {
                seedPow[i] = 1;
                strHash[i] = (long) s.charAt(i);
            } else {
                seedPow[i] = seedPow[i - 1] * hash_seed;
                strHash[i] = strHash[i - 1] * hash_seed + (long) s.charAt(i);
            }
        }
        for (int i = 0; i < wordDict.size(); i++) {
            long curHash = 0;
            for (int j = 0; j < wordDict.get(i).length(); j++) {
                curHash = curHash * hash_seed + (long) wordDict.get(i).charAt(j);
            }
            dictHash.put(curHash, i);
        }
    }

    public long getStringHash(int l, int r) {
        /*
            a     1
            ab    12
            abc   123
            abcd  1234
            abcde 12345

            bcd = abcd - a * 10^(len(bcd))
         */
        long ret = strHash[r];
        if (l > 0) {
            ret -= strHash[l - 1] * seedPow[r - l + 1];
        }
        return ret;
    }

    public List<String> listAdd(String a, List<String> b) {
        List<String> ret = new ArrayList<String>();
        for (int i = 0; i < b.size(); i++) {
            ret.add(a + " " + b.get(i));
        }
        return ret;
    }

    public List<String> gao(
        String s, int l, int r, List<String> wordDict, List<List<List<String> > > memory) {
        if (memory.get(l).get(r) != null) {
            return memory.get(l).get(r);
        }
        List<String> ret = new ArrayList<String>();
        long curHash = getStringHash(l, r);
        Integer curDictId = dictHash.get(curHash);
        if (curDictId != null) {
            ret.add(wordDict.get(curDictId));
        }
        for (int mid = l; mid < r; mid++) {
            curHash = getStringHash(l, mid);
            curDictId = dictHash.get(curHash);
            if (curDictId == null) {
                continue;
            }
            List<String> right = gao(s, mid + 1, r, wordDict, memory);
            if (right.size() != 0) {
                ret.addAll(listAdd(wordDict.get(curDictId), right));
            }
        }
        memory.get(l).set(r, ret);
        return ret;
    }

    public List<String> wordBreak(String s, List<String> wordDict) {
        if (s.length() == 0 || wordDict.size() == 0) {
            return new ArrayList<String>();
        }
        dictHash = new HashMap<Long, Integer>();
        strHash = new long[s.length()];
        seedPow = new long[s.length()];

        initHash(s, wordDict);
        List<List<List<String> > > memory = new ArrayList<List<List<String> > >();
        for (int i = 0; i < s.length(); i++) {
            memory.add(new ArrayList<List<String> >());
            for (int j = 0; j < s.length(); j++) {
                memory.get(i).add(null);
            }
        }
        return gao(s, 0, s.length() - 1, wordDict, memory);
    }
}
