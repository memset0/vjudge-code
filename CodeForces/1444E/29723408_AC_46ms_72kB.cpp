#include<bits/stdc++.h>
#define contains(x,i) (((x)>>(i))&1)
typedef __uint128_t status;
using namespace std;
const int N=109;
const status I=1;
int n,cnt;
status dp[N];
vector<int> G[N];
vector<pair<int,int>> E;
map<pair<int,int>,int> col;
map<pair<int,int>,bool> vis;
inline int highbit(const status &x){
  for(int i=n;i>=0;i--)if(contains(x,i))return i;
  return -1;
}
inline int Ask(int x,int y){
	int res;
	printf("? %d %d\n",x,y),fflush(stdout);
	return scanf("%d",&res),res;
}
inline bool check(vector<int> nod,status cur){
  if(!nod.size())return true;
  priority_queue<pair<status,int>> q;
  for(int u:nod)q.push({dp[u],u});
  for(int i=n;i>=0;i--)if(contains(cur,i)){
    status tmp=q.top().first;
    int id=q.top().second;
    q.pop();
    int h=highbit(tmp);
    if(h>i)return false;
    if(h==i)tmp^=I<<i,q.push({tmp,id});
    if(!q.size())return true;
  }
  return false;
}
void init(int u,int fa){
  for(int v:G[u])if(v!=fa)init(v,u);
  vector<int> son=G[u];
  if(find(son.begin(),son.end(),fa)!=son.end())son.erase(find(son.begin(),son.end(),fa));
  for(int i=0;i<=n;i++)dp[u]^=I<<i;
  for(int i=n;i>=0;i--){
    dp[u]^=I<<i;
    if(!check(son,dp[u]))dp[u]|=I<<i;
  }
  if(!son.size())return;
  priority_queue<pair<status,int>> q;
  for(int u:son)q.push({dp[u],u});
  for(int i=n;i>=0;i--)if(contains(dp[u],i)){
    status tmp=q.top().first;
    int id=q.top().second;
    q.pop();
    int h=highbit(tmp);
    if(h==i){
      tmp^=I<<i,q.push({tmp,id});
    }else{
      col[{u,id}]=col[{id,u}]=i;
    }
    if(!q.size())break;
  }
}
int solve(int rt){
  pair<int,int> res={-1,-1};
  function<void(int,int)> findMax=[&](int u,int fa){
    for(int v:G[u])if(v!=fa&&!vis[{u,v}]){
      if(res.first==-1||col[{u,v}]>col[res])res={u,v};
      findMax(v,u);
    }
  };
  findMax(rt,-1);
  if(res.first==-1)return rt;
  vis[res]=vis[{res.second,res.first}]=true;
  return solve(Ask(res.first,res.second));
}
int Find(int _n,vector<pair<int,int>> _E){
  n=_n,E=_E;
  for(const auto &it:E){
    G[it.first].push_back(it.second);
    G[it.second].push_back(it.first);
  }
  init(1,-1);
  return solve(1);
}
int main(){
	int n;
	vector<pair<int,int>> E;
	scanf("%d",&n);
	E.resize(n-1);
	for(auto &it:E)scanf("%d%d",&it.first,&it.second);
	printf("! %d\n",Find(n,E));
}