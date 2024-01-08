n=int(input())
a=list(map(int,input().split()))
a.sort()
for i in range(0,n):
	print(a[i],end=" ")