def inv(a,b):
	t=a
	a%=b
	k=b-2
	s=1
	while k>0:
		if k%2==1:
			s=s*a%b
		k//=2
		a=a*a%b
	# print('inv',t%b,b,s)
	return s

def solve(n):
	if n<=15:
		return -1
	a=[]
	pri=[]
	vis=[False]*n
	ban=[False]*n
	vis[0]=vis[1]=True
	for i in range(2,n):
		if vis[i]==False:
			if i>3:
				pri.append(i)
		for j in range(i+i,n,i):
			vis[j]=True
	for i in range(n-1,-1,-2):
		ban[i]=True
	a.append((n-1,2))
	for i in range(n-1,-1,-3):
		ban[i]=True
	a.append((n-1,3))
	at=0
	for u in range(n-1,-1,-1):
		if ban[u]==False:
			p=pri[at]
			a.append((u,p))
			at+=1
			if u<p and u+p>=n:
				return -1
			for i in range(u,-1,-p):
				ban[i]=True
	M=1
	b=[]
	for it in a:
		M*=it[1]
	S=0
	for it in a:
		t=((-it[0]%it[1])+it[1])%it[1]
		# print('req',t,it[1],it[0])
		m=M//it[1]
		S+=t*m*inv(m,it[1])
	return S-1

T=int(input())
for cas in range(1,T+1):
	print('Case '+str(cas)+':',solve(int(input())))