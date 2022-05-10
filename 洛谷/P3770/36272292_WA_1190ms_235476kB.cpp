#include<bits/stdc++.h>
const int N=2e7+10;
int seed,n,k,l,cnt,a[N],s[N];
std::pair<int,int> p[N];
int rand(){return seed=((seed*12321)^9999)%32768;}
int query(int k){std::nth_element(p+1,p+k+1,p+cnt+1);return p[k].second;}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
#endif
	scanf("%d%d%d",&k,&seed,&l);
	int t=0,i=1;n=k<<1|1;
	for (int i=1;i<=n;i++)a[i]=(rand()>>7)&1,t+=a[i];
	while(t>k){while(a[i]==0)i++;a[i]=0,t--;}
	while(t<k){while(a[i]==1)i++;a[i]=1,t++;}
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]?1:-1);
	for(int i=1;i<=n;i++)if(!a[i])p[++cnt]=std::make_pair(s[i],i);
	printf("%d\n%d\n%d\n",query(cnt),query(cnt-l),query(l+1));
	return 0;
}