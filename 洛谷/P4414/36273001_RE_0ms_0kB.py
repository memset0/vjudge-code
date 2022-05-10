a = [-1, -1, -1]
a[0], a[1], a[2] = map(int, input().split())
a = sorted(a)
s = input()
print(a[s[0] - 'A'], a[s[1] - 'B'], a[s[2] - 'C'])