#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,cur,ans1,ans2,id[N],bel[N],idx[N],anc[N][20],l[N],r[N];
vector<int> g[N];
struct subtr{
  int sz;
  set<int> nodes;
  inline void calc(){
    ans2-=sz;
    if(!nodes.size())sz=0;
    else{
      int l=*nodes.begin(),r=*nodes.rbegin();
      int x=idx[l];
      for(int i=19;~i;i--)
        if(anc[x][i]>1&&(!(::l[anc[x][i]]<=l&&::r[anc[x][i]]>=r)))
          x=anc[x][i];
      if(!(::l[x]<=l&&::r[x]>=r))x=anc[x][0];
      sz=::r[x]-::l[x]+1-nodes.size();
    }
    ans2+=sz;
  }
  inline void ins(int x){
    if(!nodes.size())ans1++;
    nodes.insert(x);
    calc();
  }
  inline void del(int x){
    nodes.erase(x);
    calc();
    if(!nodes.size())ans1--;
  }
}p[N];
inline void dfs(int x,int pre,int last){
  anc[x][0]=last;
  for(int i=1;i<20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
  bel[x]=pre;
  if(!g[x].size()){
    id[x]=++cur;
    l[x]=r[x]=cur;
    idx[cur]=x;
    return;
  }
  l[x]=cur+1;
  for(const auto &v:g[x]){
    dfs(v,pre?pre:v,x);
  }
  r[x]=cur;
}
int main(){
  freopen("gangsters.in","r",stdin);
  freopen("gangsters.out","w",stdout);
  cin>>n>>m;
  for(int f,i=2;i<=n;i++){
    scanf("%d",&f);
    g[f].push_back(i);
  }
  dfs(1,0,0);
  for(int y,i=1;i<=m;i++){
    char s[3];scanf("%s%d",s,&y);
    if(s[0]=='+'){
      p[bel[y]].ins(id[y]);
    }else{
      p[bel[y]].del(id[y]);
    }
    printf("%d %d\n",ans1,ans2);
  }
}