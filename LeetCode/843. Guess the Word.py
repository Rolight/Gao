# """
# This is Master's API interface.
# You should not implement it, or speculate about its implementation
# """
# class Master:
#    def guess(self, word):
#        """
#        :type word: str
#        :rtype int
#        """

from collections import defaultdict


class Solution:
    def collect(self, wordlist):
        ret = [defaultdict(int) for _ in range(6)]
        for w in wordlist:
            for i in range(6):
                ret[i][w[i]] += 1
        return ret

    def calc(self, word, dt):
        ret = 0
        for i in range(6):
            ret += dt[i][word[i]]
        return ret

    def get_idx(self, wordlist, dt):
        scores = [self.calc(w, dt) for w in wordlist]
        ret = 0
        for idx in range(len(scores)):
            if scores[idx] > scores[ret]:
                ret = idx
        return ret

    def dis(self, a, b):
        ret = 0
        for i in range(6):
            if a[i] == b[i]:
                ret += 1
        return ret

    def findSecretWord(self, wordlist, master):
        """
        :type wordlist: List[Str]
        :type master: Master
        :rtype: None
        """
        step = 1
        while len(wordlist) >= 1:
            dt = self.collect(wordlist)
            cur_word = wordlist[self.get_idx(wordlist, dt)]
            res = master.guess(cur_word)
            print(step, cur_word, wordlist, res)
            step += 1
            if res == 6:
                return
            wordlist = [w for w in wordlist if self.dis(
                cur_word, w) == res and w != cur_word]
