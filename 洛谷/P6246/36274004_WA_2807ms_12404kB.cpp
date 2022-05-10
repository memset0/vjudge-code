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
	// printf("w[%d][%d]=%lld:%d\n",l,r,s[r]-s[d]+s[l-1]-s[d-1]+((r-d)-(d-l))*a[d],d);
	return s[r]-s[d]+s[l-1]-s[d-1]-((r-d)-(d-l))*a[d];
}
inline long long tr(int i,int j){return i==j?dp[i]:dp[i]+w(i+1,j);}
long long check(int mid){
	static int l,r; static atom s[N];
	l=r=1,s[1]={1,n,0};
	// log("check %d\n",mid);
	for(int i=1;i<=n;i++){
		while(s[l].r<i)l++;
		s[l].l=i+1,dp[i]=tr(s[l].t,i)+mid,cnt[i]=cnt[s[l].t]+1;
		// printf("%d [%d %d %d] dp=%lld val=%lld cnt=%d\n",
		// 	i,s[l].l,s[l].r,s[l].t,dp[i],dp[i]-(long long)cnt[i]*mid,cnt[i]);
		// printf("%lld %lld\n",tr(i,s[r].r),tr(s[r].t,s[r].r));
		while(l<=r&&tr(i,s[r].r)<=tr(s[r].t,s[r].r))r--;
		if(l<=r){
			int ql=s[r].l,qr=s[r].r,mid,res=-1;
			while(ql<=qr){
				mid=(ql+qr)>>1;
				tr(s[r].t,s[r].r)<=tr(i,s[r].r)?(res=mid,ql=mid+1):(qr=mid-1);
			}
			s[r].r=res;
		}
		// for(int i=l;i<=r;i++)printf("[%d %d %d]%c",s[i].l,s[i].r,s[i].t," \n"[i==r]);
		if(s[r].r>=n)continue;
		++r,s[r]={s[r-1].r+1,n,i};
	}
	return cnt[n];
}
long long wqs(){
	int ql=0,qr=s[n],mid,res=-1,cnt;
	while(ql<=qr){
		mid=(ql+qr)>>1,cnt=check(mid);
		if(cnt==m){res=mid; break;}
		(cnt<m)?(res=mid,qr=mid-1):(ql=mid+1);
	}
	return dp[n]-(long long)res*m;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]),s[i]=s[i-1]+a[i];
	printf("%lld\n",wqs());
}