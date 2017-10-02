from collections import defaultdict
n, k = map(int, input().split())
buf = input()
bad = False

mp = defaultdict(int)

for ch in buf:
    mp[ch] += 1
    if mp[ch] > k:
        bad = True
        break

print("NO" if bad else "YES")

