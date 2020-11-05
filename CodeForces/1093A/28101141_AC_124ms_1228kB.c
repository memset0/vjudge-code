T = int(input())
for t in range(0, T):
	n = int(input())
	ans = 0
	while n > 7:
		n -= 2
		ans += 1
	if n != 0:
		ans += 1
	print(ans)