n = int(input())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

A.sort(reverse=True)
B1 = sorted(enumerate(B), key=lambda x: x[1])
B2 = sorted(enumerate(B1), key=lambda x: x[1])

ans = [A[b[0]] for b in B2]

print(' '.join(map(str, ans)))
