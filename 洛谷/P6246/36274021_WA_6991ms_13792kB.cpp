#include<bits/stdc++.h>
// #define log(...) (void(0))
#define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);
template<class T> inline void read(T &x){
	x=0; char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}
const int N=1e6+10;
int n,m,top,a[N],cnt[N];
long long s[N],dp[N];
struct atom{int l,r,t;};
inline long long w(int l,int r){
	int d=(l+r)>>1;
	return s[r]-s[d]+s[l-1]-s[d-1]-((r-d)-(d-l))*a[d];
}
inline long long tr(int i,int j){return i==j?dp[i]:dp[i]+w(i+1,j);}
inline bool cp(long long x,long long y,bool fl){
	return fl?x<y:x<=y;
}
long long check(long long mid,bool fl){
	static int l,r; static atom s[N];
	l=r=1,s[1]={1,n,0};
	// log("\e[33mcheck %lld\e[0m\n",mid);
	for(int i=1;i<=n;i++){
		while(s[l].r<i)l++;
		s[l].l=i+1,dp[i]=tr(s[l].t,i)+mid,cnt[i]=cnt[s[l].t]+1;
		// log("%d [%d %d %d] dp=%lld val=%lld cnt=%d\n",i,s[l].l,s[l].r,s[l].t,dp[i],dp[i]-(long long)cnt[i]*mid,cnt[i]);
		while(l<=r&&cp(tr(i,s[r].l),tr(s[r].t,s[r].l),fl))r--;
		if(l<=r){
			int ql=s[r].l,qr=s[r].r,mid,res=qr+1;
			while(ql<=qr){
				mid=(ql+qr)>>1;
				cp(tr(i,mid),tr(s[r].t,mid),fl)?(res=mid,qr=mid-1):(ql=mid+1);
			}
			s[r].r=res-1;
		}
		if(s[r].r>=n)continue;
		++r,s[r]={s[r-1].r+1,n,i};
		// for(int i=l;i<=r;i++)log("[%d %d %d]%c",s[i].l,s[i].r,s[i].t," \n"[i==r]);
	}
	return cnt[n];
}
long long wqs(){
	// long long ql=-30,qr=30,mid,res=0;
	long long ql=0,qr=(long long)n*a[n],mid,res=-1;
	while(ql<=qr){
		mid=(ql+qr)>>1; int cnt=check(mid,0);
		if(cnt==m){res=mid; break;}
		(cnt<m)?(res=mid,qr=mid-1):(ql=mid+1);
	}
	long long ans=dp[n]-(long long)res*m;
	check(res,0);
	ans=std::max(ans,dp[n]-(long long)res*m);
	check(res,1);
	ans=std::max(ans,dp[n]-(long long)res*m);
	return ans;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]),s[i]=s[i-1]+a[i];
	printf("%lld\n",wqs());
}