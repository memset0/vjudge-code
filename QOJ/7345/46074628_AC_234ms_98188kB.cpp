#include<bits/stdc++.h>
using namespace std;
const int N=3e5;
int n;
char S[N+10];
int M=26,sz,rk[N+10],ar[N+10],sa[N+10],nw,ba[N+10];
int he[20][N+10];
void Getsa(){
	for(int i=1;i<=M;++i)ba[i]=0;
	for(int i=1;i<=n;++i)++ba[rk[i]];
	for(int i=2;i<=M;++i)ba[i]+=ba[i-1];
	for(int i=n;i>=1;--i)sa[ba[rk[ar[i]]]--]=ar[i];
}
void SA(){
	M=27;
	for(int i=1;i<=n;++i)rk[i]=S[i]-'a'+1,ar[i]=i;
	Getsa();
	for(int i=1;i<=n;i<<=1){
		sz=0;
		for(int j=n-i+1;j<=n;++j)ar[++sz]=j;
		for(int j=1;j<=n;++j)if(sa[j]>i)ar[++sz]=sa[j]-i;
		Getsa();
		for(int j=1;j<=n;++j)ar[j]=rk[j];
		rk[sa[1]]=nw=1;
		for(int j=2;j<=n;++j)rk[sa[j]]=(sa[j]+i<=n&&sa[j-1]+i<=n&&ar[sa[j]]==ar[sa[j-1]]&&ar[sa[j]+i]==ar[sa[j-1]+i]?nw:++nw);
		M=nw;
	}
}
void Getheight(){
	int ls=0;
	for(int i=1;i<=n;++i){
		ls?--ls:0;
		if(rk[i]==1)continue;
		while(i+ls<=n&&sa[rk[i]-1]+ls<=n&&S[i+ls]==S[sa[rk[i]-1]+ls])++ls;
		he[0][rk[i]]=ls;
	}
}
int num[30][N+10],ls[30],nx[30][N+10],li,ri,lg[N+10];
long long ans;
int LCP(int l,int r){
	if(!l||!r)return 0;
	if(l==r)return n;
	int k=lg[r-l];
	return min(he[k][l+1],he[k][r-(1<<k)+1]);
}
int main(){
	scanf("%s",S+1),n=strlen(S+1);
	SA(),Getheight();
	for(int i=1;(1<<i)<=n;++i)for(int j=2;j+(1<<i)-1<=n;++j)he[i][j]=min(he[i-1][j],he[i-1][j+(1<<i-1)]);
	//for(int i=1;i<=n;++i)printf("%s\n",S+sa[i]);
	for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int i=n;i>=1;--i){
		for(int j=0;j<26;++j)num[j][i]=num[j][i+1];
		++num[S[i]-'a'][i];
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<26;++j)nx[j][i]=nx[j][i-1];
		if(sa[i]>1)nx[S[sa[i]-1]-'a'][i]=i;
	}
	for(int i=n;i>=1;--i){
		//cout<<"---------------\nI="<<i<<"\n";
		if(sa[i]>1)ls[S[sa[i]-1]-'a']=i;
		for(int j=0;j<26;++j)if(ls[j]||nx[j][i]){
			//cout<<"CHAR="<<(char)(j+'a')<<"\n";
			li=max(2,he[0][i]+1),ri=min(n-sa[i]+1,max(LCP(nx[j][i],i),LCP(i,ls[j]))+1);
			//cout<<"li="<<li<<" ri="<<ri<<"\n";
			if(li<=ri)ans+=num[j][sa[i]+li-1]-num[j][sa[i]+ri];
			//cout<<"ANS="<<ans<<"\n";
		}
	}
	for(int i=0;i<26;++i)ans+=!!num[i][1];
	printf("%lld",ans);
	return 0;
}
//abcda
//abaac