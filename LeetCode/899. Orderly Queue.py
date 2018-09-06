class Solution:
    def orderlyQueue(self, S, K):
        return sorted([S[i:] + S[:i] for i in range(len(S))])[0] if K == 1 else ''.join(sorted(list(S)))
