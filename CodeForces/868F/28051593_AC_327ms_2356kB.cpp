#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e5+10;
int n,m,ul,ur,a[N],s[N];
long long res,f[N],g[N];
inline long long binom(int x){return (long long)x*(x-1)/2;}
inline void add(int x){
	res-=binom(s[x]),s[x]++,res+=binom(s[x]);
	// printf("> add %d => %lld\n",x,res);
}
inline void del(int x){
	res-=binom(s[x]),s[x]--,res+=binom(s[x]);
	// printf("> del %d => %lld\n",x,res);
}
long long calc(int l,int r){
	while(ul>l)add(a[--ul]);
	while(ur<r)add(a[++ur]);
	while(ul<l)del(a[ul++]);
	while(ur>r)del(a[ur--]);
	// printf(">> calc %d %d => %lld\n",l,r,res);
	return res;
}
void dfs(int l,int r,int sl,int sr){
	if(l>r)return;
	int mid=(l+r)>>1,s=sl;
	for(int i=sl;i<=sr&&i<=mid;i++){
		long long cur=g[i-1]+calc(i,mid);
		if(cur<f[mid])f[mid]=cur,s=i;
	}
	// printf("dfs %d %d %d | %d %d %d | %d %d %d\n",l,mid,r,sl,s,sr,g[s-1],calc(s,mid),f[mid]);
	dfs(l,mid-1,sl,s);
	dfs(mid+1,r,s,sr);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m),ul=1,ur=0;
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)f[i]=calc(1,i);
	// for(int i=1;i<=n;i++)printf("%lld%c",f[i]," \n"[i==n]);
	for(int i=1;i<m;i++){
		memcpy(g+1,f+1,n<<3),memset(f+1,0x3f,n<<3);
		dfs(1,n,1,n);
		// for(int i=1;i<=n;i++)printf("%lld%c",f[i]," \n"[i==n]);
	}
	printf("%lld\n",f[n]);
}