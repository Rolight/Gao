class Solution:

    def isSpecial(self, S):
        c_1, c_0 = 0, 0
        for i in range(len(S)):
            if S[i] == '0':
                c_0 += 1
            else:
                c_1 += 1
            if c_0 > c_1:
                return False
        return c_1 == c_0

    def round(self, S):
        for i in range(len(S)):
            for j in range(i, len(S)):
                if not self.isSpecial(S[i:j + 1]):
                    continue
                for l in range(j+1, len(S)):
                    if not self.isSpecial(S[j+1:l+1]):
                        continue
                    print(S[i:j+1], S[j+1:l+1])
                    newS = S[0:i] + S[j+1:l+1] + S[i:j+1] + S[l+1:]
                    if newS > S:
                        return newS
        return None

    def makeLargestSpecial(self, S):
        """
        :type S: str
        :rtype: str
        """
        while True:
            newS = self.round(S)
            print(newS)
            if newS is None:
                break
            S = newS
        return S
