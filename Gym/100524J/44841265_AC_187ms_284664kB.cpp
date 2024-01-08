#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int T,n,nx[N+10][30],mx[(1<<26)+10],a[N*26+10],tt,tim,pos[30],ar[30],sz,t,l,ms;
long long ans;
char s[N+10];
bool cmp(int x,int y){
	return pos[x]<pos[y];
}
int main(){
#ifdef memset0
	freopen("J.in","r",stdin);
#else
	freopen("jingles.in","r",stdin);
	freopen("jingles.out","w",stdout);
#endif
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1),n=strlen(s+1);
		++tim,tt=0;
		for(int i=0;i<26;++i)nx[n+1][i]=n+1;
		for(int i=n;i>=1;--i){
			for(int j=0;j<26;++j)nx[i][j]=nx[i+1][j];
			nx[i][s[i]-'a']=i;
		}
		for(int i=1;i<=n;++i){
			for(int j=0;j<26;++j)ar[j]=j,pos[j]=nx[i][j];
			sort(ar,ar+26,cmp),ms=0;
			for(int j=0;j<26;++j){
				t=ar[j];
				if(pos[t]>n)break;
				l=(j==25?n+1:pos[ar[j+1]])-i;
				ms|=(1<<t);
				if(!mx[ms])a[++tt]=ms;
				mx[ms]=max(mx[ms],l);
			}
		}
		printf("%d ",tt);
		ans=0;
		for(int i=1;i<=tt;++i)ans+=__builtin_popcount(a[i])*mx[a[i]],mx[a[i]]=0;
		printf("%lld\n",ans);
	}
	return 0;
}
/*
2
abacaba
abbcccdddd
*/