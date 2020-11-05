a=int(input())
b=int(input())
s=1
mod=10**9+7
while b:
	if b&1:
		s=s*a%mod
	b>>=1
	a=a*a%mod
print(s)