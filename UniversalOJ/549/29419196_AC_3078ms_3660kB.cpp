#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=6e4+10;
int n,k,a[N],s[N];
struct bit{
	int a[1<<16];
	bit(){memset(a,63,sizeof(a));}
	inline void insert(int x,int w){
		int y=x>>8;
		for(int i=0;i<(1<<8);i++)
			a[(y<<8)|i]=std::min(a[(y<<8)|i],(x^((y<<8)|i))+w);
	}
	inline int query(int x)const{
		int y=x&((1<<8)-1);
		int res=INT_MAX;
		for(int i=0;i<(1<<8);i++)
			res=std::min(res,a[(i<<8)|y]+(x^((i<<8)|y)));
		return res;
	}
}f[8];
int main(){
#ifdef memset0
	freopen("ex_seq2.in","r",stdin);
	freopen("ex_seq2.out","w",stdout);
#endif
	read(n),read(k);
	for(int i=1;i<=n;i++)read(a[i]),s[i]=s[i-1]^a[i];
	f[0].insert(0,0);
	for(int i=1;i<=n;i++)
		for(int j=std::min(i,k);j>=1;j--){
			int res=f[j-1].query(s[i]);
			// printf("f[%d][%d] = %d\n",i,j,res);
			if(j<k)f[j].insert(s[i],res); else printf("%d ",res);
		}
}