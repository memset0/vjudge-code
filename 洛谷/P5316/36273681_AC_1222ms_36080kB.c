def sqrt(x):
	l = 0
	r = x
	ans = -1
	while l <= r:
		mid = (l + r) // 2
		if mid * mid <= x:
			ans = mid
			l = mid + 1
		else:
			r = mid - 1;
	return ans

def curt(x):
	l = 0
	r = x
	ans = -1
	while l <= r:
		mid = (l + r) // 2
		if mid * mid * mid <= x:
			ans = mid
			l = mid + 1
		else:
			r = mid - 1;
	return ans

def gcd(a, b): 
	if b == 0:
		return a
	else: 
		return gcd(b, a % b)

def lcm(x, y):
	return x * y // gcd(x, y)

def next_permutation(nums):
	size = len(nums)
	for x in range(size - 1, -1, -1):
		if nums[x - 1] < nums[x]:
			break
	if x > 0:
		for y in range(size - 1, -1, -1):
			if nums[y] > nums[x - 1]:
				nums[x - 1], nums[y] = nums[y], nums[x - 1]
				break
	for z in range((size - x) // 2):
		nums[x + z], nums[size - z - 1] = nums[size - z - 1], nums[x + z]
	return nums

T, k = map(int, input().split())

def solve3(a, b, mul):
	xy = b[0] * a[0]
	xz = b[1] * a[1]
	yz = b[2] * a[2]
	return [mul // yz, mul // xz, mul // xy]

def check3(a, b, sol):
	a = sorted(a)
	b = sorted(b)
	c = []
	d = []
	# print('check', sol, a, b)
	for i in range(0, 3):
		for j in range(i + 1, 3):
			c.append(gcd(sol[i], sol[j]))
			d.append(lcm(sol[i], sol[j]))
	c = sorted(c)
	d = sorted(d)
	# print('check', sol, a, b, c, d)
	return a == c and b == d

def findans3(a, b):
	mul = sqrt(b[0] * b[1] * b[2] * a[0] * a[1] * a[2])
	pa = [1, 2, 3]
	pb = [1, 2, 3]
	for ia in range(0, 6):
		for ib in range(0, 6):
			# print('ia', ia, 'ib', ib, pa, pb)
			ua = [a[pa[0] - 1], a[pa[1] - 1], a[pa[2] - 1]]
			ub = [b[pb[0] - 1], b[pb[1] - 1], b[pb[2] - 1]]
			sol = solve3(ua, ub, mul)
			# print(pa, pb, ua, ub, sol)
			if (check3(ua, ub, sol)):
				return sol
			pb = next_permutation(pb)
		pa = next_permutation(pa)

def solve4(a, b, mul):
	c = [a[i] * b[i] for i in range(0, 6)]
	ans = []
	for i in range(0, 6):
		for j in range(i + 1, 6):
			for k in range(j + 1, 6):
				muls = sqrt(c[i] * c[j] * c[k])
				# print(mul, muls)
				ans.append([muls // c[i], muls // c[j], muls // c[k], mul // muls])
	return ans

def check4(a, b, sol):
	a = sorted(a)
	b = sorted(b)
	c = []
	d = []
	# print('check', sol, a, b)
	for i in range(0, 4):
		for j in range(i + 1, 4):
			c.append(gcd(sol[i], sol[j]))
			d.append(lcm(sol[i], sol[j]))
	c = sorted(c)
	d = sorted(d)
	# print('check', sol, a, b, c, d)
	return a == c and b == d

def findans4(a, b):
	mul = curt(b[0] * b[1] * b[2] * b[3] * b[4] * b[5] * a[0] * a[1] * a[2] * a[3] * a[4] * a[5])
	pa = [1, 2, 3, 4, 5, 6]
	pb = [1, 2, 3, 4, 5, 6]
	for ia in range(0, 24):
		for ib in range(0, 24):
			# print('ia', ia, 'ib', ib, pa, pb)
			ua = [a[pa[0] - 1], a[pa[1] - 1], a[pa[2] - 1], a[pa[3] - 1], a[pa[4] - 1], a[pa[5] - 1]]
			ub = [b[pb[0] - 1], b[pb[1] - 1], b[pb[2] - 1], b[pb[3] - 1], b[pb[4] - 1], b[pb[5] - 1]]
			sols = solve4(ua, ub, mul)
			# print(pa, pb, ua, ub, sol)
			for sol in sols:
				if (check4(ua, ub, sol)):
					return sol
			pb = next_permutation(pb)
		pa = next_permutation(pa)

for Case in range(0, T):
	if k == 2:
		a = int(input())
		b = int(input())
		print(a, b)
	elif k == 3:
		a = list(map(int, input().split()))
		b = list(map(int, input().split()))
		c = findans3(a, b)
		print(c[0], c[1], c[2])
	else:
		a = list(map(int, input().split()))
		b = list(map(int, input().split()))
		c = findans4(a, b)
		print(c[0], c[1], c[2], c[3])