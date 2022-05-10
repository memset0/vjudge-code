#include<bits/stdc++.h>
const int N=2e6+10;
int n,lst=1,nod=1,fa[N],siz[N],len[N],ch[N][26];
char s[N];
long long ans;
std::vector<int> son[N];
void append(int c){
	int u=++nod,f=lst; lst=nod,len[u]=len[f]+1;
	while(f&&!ch[f][c])ch[f][c]=u,f=fa[f];
	if(!f){fa[u]=1; return;} int s=ch[f][c];
	if(len[s]==len[f]+1){fa[u]=s; return;} int p=++nod;
	fa[p]=fa[s],fa[s]=fa[u]=p,len[p]=len[f]+1;
	std::copy(ch[s],ch[s]+26,ch[p]);
	while(f&&ch[f][c]==s)ch[f][c]=p,f=fa[f];
}
void dfs(int u){
	siz[u]=1;
	for(int v:son[u])dfs(v),siz[u]+=siz[v];
	if(siz[u]>1)ans=std::max(ans,(long long)siz[u]*len[u]);
}
int main(){
	freopen("1.in","r",stdin);
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;i++)append(s[i]-'a');
	for(int i=2;i<=nod;i++)son[fa[i]].push_back(i);
	dfs(1);
	printf("%lld\n",ans);
}