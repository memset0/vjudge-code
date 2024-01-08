#include<bits/stdc++.h>
using namespace std;
const int N=4e5,L=17;
int n,m;
char s[N+10],t[N+10];
void Solve(int x,int len,int sh,int fl){
	if(!x){
		for(int i=n-len;i<n;++i)putchar((s[i]-'a'+sh)%26+'a');
		return;
	}
	long long tl=1ll*n*(1<<x);
	if(len<=(tl>>2))Solve(x-1,len,sh+1,fl);
	else if(len<=(3*(tl>>2))){
		Solve(x-1,len-(tl>>2),sh,1);
		for(int i=(tl>>2);i<(tl>>1);++i)putchar((s[i]-'a'+sh+1)%26+'a');
	}else{
		Solve(x-1,len-(tl>>1)-(tl>>2),sh,1);
		for(int i=0;i<(tl>>1);++i)putchar((s[i]-'a'+sh)%26+'a');
		for(int i=(tl>>2);i<(tl>>1);++i)putchar((s[i]-'a'+sh+1)%26+'a');
	}
	if(fl){
		for(int i=0;i<(tl>>1);++i)t[i]=s[i];
		for(int i=(tl>>2);i<(tl>>2)+(tl>>1);++i)s[i]=t[i-(tl>>2)];
		for(int i=(tl>>2)+(tl>>1);i<tl;++i)s[i]=(t[i-(tl>>1)]-'a'+1)%26+'a';
		//printf("S %d=%s\n",x,s);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	Solve(L,m,25,0);
	return 0;
}