#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int T,n;
long long tot,ans;
char s[N+10];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1),n=strlen(s+1);
		tot=ans=0;
		for(int i=n;i>=1;--i){
			if(i<n&&s[i]==s[i+1])tot+=n-i;
			ans+=tot+(s[i]=='0')*(n-i+1)+(1ll*i*(i+1)>>1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
/*
3
101
011
11010
*/