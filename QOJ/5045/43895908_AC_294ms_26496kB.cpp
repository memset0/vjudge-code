#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e5+10;
int T,n,p,res,a[N];
std::map<int,int> map;
inline int fpow(int a,int b,int p){
	int s=1;
	for(;b;b>>=1,a=(long long)a*a%p)
		if(b&1)s=(long long)s*a%p;
	return s;
}
int check(int x){
	// printf("check %d\n",x);
	std::map<int,int> nxt;
	static int f[N];
	for(int i=n;i>=1;i--){
		auto v=(long long)a[i]*x%p;
		auto it=nxt.find(v);
		f[i]=it==nxt.end()?1:f[it->second]+1;
		nxt[a[i]]=i;
	}
	// for(int i=1;i<=n;i++)print(f[i]," \n"[i==n]);
	int res=0;
	for(int i=1;i<=n;i++)res=std::max(res,f[i]);
	return res>=((n+1)>>1)?res:0;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	srand(20040725);
	for(read(T);T--;){
		read(n),read(p),res=0,map.clear();
		for(int i=1;i<=n;i++)read(a[i]);
		for(int i=1;i<=n;i++){
			int v=fpow(a[i],p-2,p);
			// printf("%d %lld %lld\n",a[i],(long long)a[i+1]*v%p,(long long)a[i+2]*v%p);
			if(i+1<=n)map[(long long)a[i+1]*v%p]++;
			if(i+2<=n)map[(long long)a[i+2]*v%p]++;
		}
		for(auto it:map)if(it.second>=(n>>2)-5)res=std::max(res,check(it.first));
		print(res?res:-1,'\n');
	}
}