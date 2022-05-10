def isPrime(n):
	if n <=1: return False
	i = 2
	while i*i <= n:
		if n%i == 0 : return False
		i += 1
	return True

s = input().split()
a = int(s[0])
b = int(s[1])

for i in range(a, b + 1):
    t = str(i)
    if t == t[::-1]:
        if isPrime(i):
            print(i)
