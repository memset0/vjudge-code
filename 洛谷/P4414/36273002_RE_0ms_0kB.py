a = range(3)
a[0], a[1], a[2] = map(int, input().split())
a = sorted(a)
b = {}
b['A'], b['B'], b['C'] = a[0], a[1], a[2]
s = input()
print(b[s[0]], b[s[1]], b[s[2]])