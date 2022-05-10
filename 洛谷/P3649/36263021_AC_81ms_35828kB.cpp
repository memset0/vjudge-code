#include<bits/stdc++.h>
const int N=3e5+10;
struct pam{
	int cur,lst,nod,end,s[N],len[N],siz[N],fail[N],ch[N][26];
	pam(){nod=2,fail[2]=1,len[1]=-1,s[0]=-1,lst=1;}
	int find(int x){while(s[end]!=s[end-len[x]-1])x=fail[x];return x;}
	void append(int c){
		s[++end]=c,cur=find(lst);
		if(!ch[cur][c]){
			ch[cur][c]=++nod,len[nod]=len[cur]+2;
			fail[nod]=cur==1?2:ch[find(fail[cur])][c];
		}
		siz[lst=ch[cur][c]]++;
	}
	long long solve(){
		long long ans=0;
		for(int i=nod;i>=2;i--)siz[fail[i]]+=siz[i];
		for(int i=1;i<=nod;i++)ans=std::max(ans,(long long)siz[i]*len[i]);
		return ans;
	}
}p;
int main(){
	for(char c=getchar();c!='\n';c=getchar())p.append(c-'a');
	printf("%lld\n",p.solve());
}