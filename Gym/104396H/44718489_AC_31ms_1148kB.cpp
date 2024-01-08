#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
int n,del[N+10],ans;
char s[N+10],t[N+10];
int main(){
	scanf("%d",&n);
	scanf("%s",s+1),scanf("%s",t+1);
	for(int i=1;i<=n;++i){
		del[i]=((int)s[i]-(int)t[i]+26)%26;
		ans+=(del[i]!=del[i-1]);
	}
	printf("%d",ans);
	return 0;
}