#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=5e4+10,L=20;
int n,m;
std::vector<int> G[N];
inline int set(int s,int k){
	for(int i=0;i<k;i++)
		if((s>>i)&1){
			s^=1<<i;
		}
	return s^(1<<k);
}
int DP(int u,int fa){
	if(u!=1&&G[u].size()==1){
		return 1;
	}
	std::vector<int> a;
	for(int v:G[u])
		if(v!=fa){
			a.push_back(DP(v,u));
			// printf("%d(<%d) : %d\n",v,u,a.back());
		}
	int sum=0,crash=0;
	for(int x:a){
		crash|=x&sum;
		sum|=x;
	}
	for(int i=L-1;i>=0;i--)
		if((crash>>i)&1){
			for(int j=i+1;j<L;j++)
				if(!((sum>>j)&1)){
					return set(sum,j);
				}
		}
	for(int j=0;j<L;j++)
		if(!((sum>>j)&1)){
			return set(sum,j);
		}
	assert(0);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	if(n==1){puts("0"); return 0;}
	for(int u,v,i=1;i<n;i++){
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int ans=DP(1,0);
	for(int i=L-1;i>=0;i--)
		if((ans>>i)&1){
			printf("%d\n",i);
			return 0;
		}
}