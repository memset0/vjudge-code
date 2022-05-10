#include<bits/stdc++.h>
using namespace std;
const int N=2e6+9;
int n,m,nod=1,lst=1,fa[N],len[N],siz[N],ch[N][26];
char s[N];
long long ans;
vector<int> G[N];
inline void append(char c){
  int u=++nod,f=lst; lst=u,len[u]=len[f]+1,siz[u]=1;
  while(f&&!ch[f][c])ch[f][c]=u,f=fa[f];
  if(!f){fa[u]=1; return;} int s=ch[f][c];
  if(len[u]==len[s]+1){fa[u]=s; return;}
  int p=++nod; fa[u]=p,len[p]=len[f]+1;
  for(int i=0;i<26;i++)ch[p][c]=ch[s][c];
  while(f&&ch[f][c]==s)ch[f][c]=p,f=fa[f];
}
void dfs(int u){
  for(int v:G[u])dfs(v),siz[u]+=siz[v];
  if(len[u]>1)ans=max(ans,1ll*len[u]*siz[u]);
}
int main(){
  scanf("%s",s),n=strlen(s);
  for(int i=0;i<n;i++)append(s[i]);
  for(int i=2;i<=nod;i++)G[fa[i]].push_back(i);
  dfs(1);
  cout<<ans<<endl;
}