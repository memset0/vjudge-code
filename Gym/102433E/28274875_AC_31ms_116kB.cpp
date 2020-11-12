#include<bits/stdc++.h>
const int N=1e5+10,mod=11092019;
int n,c[100];
char s[N];
int main(){
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;i++)++c[s[i]-'a'+1];
	long long ans=1;
	for(int i=1;i<=26;i++)(ans*=c[i]+1)%=mod;
	printf("%lld\n",ans);
}