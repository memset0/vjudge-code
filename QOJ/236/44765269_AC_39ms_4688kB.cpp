#include<bits/stdc++.h>
#define pi pair<int,int>
#define f first
#define s second
using namespace std;
const int N=1e5;
int T,n,len,nn,ans,tmp;
pi ar[N+10];
char s[N+10];
bool cmp(pi x,pi y){
	if((x.f-x.s>=0)!=(y.f-y.s>=0))return x.f-x.s<0;
	if(x.f-x.s>=0)return x.s>y.s;
	return x.f<y.f;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n),ans=0;
		for(int i=1;i<=n;++i){
			scanf("%s",s+1),len=strlen(s+1);
			ar[i]=(pi){0,0},nn=0;
			for(int j=1;j<=len;++j){
				if(s[j]=='(')++nn;
				else if(nn)--nn,++ans;
				else ++ar[i].f;
			}
			ar[i].s=nn;
		}
		sort(ar+1,ar+n+1,cmp);
		nn=0;
		for(int i=1;i<=n;++i){
			ans+=(tmp=min(nn,ar[i].f));
			nn+=ar[i].s-tmp;
		}
		printf("%d\n",ans<<1);
	}
	return 0;
}