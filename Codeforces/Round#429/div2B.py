n = int(input())
arr = map(int, input().split())

if sum(map(lambda x: x % 2, arr)) == 0:
    print("Second")
else:
    print("First")
