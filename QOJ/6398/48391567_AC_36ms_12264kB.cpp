#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=105;
int n,m,a[N][N],id[N][N],nod;
string str;
char mp[N<<1][N<<1];
struct atom{
  int x,y;
};
void giveup(){
  cout<<"NO"<<endl;
  exit(0);
}
bool empty(){
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      if(a[i][j])return false;
  return true;
}
void setup(const atom &a,const atom &b){
  // fprintf(stderr,"setup %d %d : %d %d\n",a.x,a.y,b.x,b.y);
  // assert(a.x==b.x||a.y==b.y);
  if(a.x==b.x){
    mp[a.x<<1][min(a.y,b.y)<<1|1]='.';
  }else{
    mp[min(a.x,b.x)<<1|1][a.y<<1]='.';
  }
}
bool solve_border(vector<pair<int,atom>> &b){
  for(int i=0;i<b.size();i++)
    if(b[i].first){
      if(i+1<b.size()&&b[i+1].first){
        b[i+1].first=0;
      }else{
        return false;
      }
    }
  for(int i=0;i<b.size();i++)
    if(b[i].first){
      setup(b[i].second,b[i+1].second);
    }
  return true;
}
const int M=N*N*24;
int s,e,tot,hed[M],to[M],val[M],nxt[M],dep[M],cur[M],pos[M][2];
void add_edge(int u,int v){
  nxt[tot]=hed[u],to[tot]=v,val[tot]=1,hed[u]=tot++;
  nxt[tot]=hed[v],to[tot]=u,val[tot]=0,hed[v]=tot++;
}
bool bfs(){
  static int u,l,r,q[M];
  memset(dep,0,sizeof(dep)),l=r=dep[s]=1,q[1]=s;
  while(l<=r){
    u=q[l++];
    for(int i=hed[u];~i;i=nxt[i])if(val[i]&&!dep[to[i]])dep[to[i]]=dep[u]+1,q[++r]=to[i];
  }
  return dep[e];
}
int dfs(int u,int d){
  if(u==e)return d;
  int s=0;
  for(int &i=cur[u];~i;i=nxt[i])
    if(val[i]&&dep[to[i]]==dep[u]+1)
      if(int e=dfs(to[i],min(d-s,val[i]))){
        s+=e,val[i]-=e,val[i^1]+=e;
        if(s==d)return s;
      }
  return s?s:dep[u]=0;
}
int main(){
#ifdef memset0
  freopen("E.in","r",stdin);
#endif
  memset(hed,-1,sizeof(hed));
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(int i=0;i<n*2-1;i++){
    cin>>str;
    for(int j=0;j<m*2-1;j++)mp[i][j]=str[j]=='.'?'#':str[j];
  }
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++){
      a[i][j]=mp[i<<1][j<<1]-'0';
      a[i][j]=a[i][j]==2||a[i][j]==4||a[i][j]==7;
      cerr<<a[i][j]<<" \n"[j+1==m];
    }
  bool fl=false;
  for(int op=0;op<4;op++){
    vector<pair<int,atom>> b;
    for(int i=0;i<n;i++)b.emplace_back(a[i][0],atom{i,0});
    for(int i=1;i<m;i++)b.emplace_back(a[n-1][i],atom{n-1,i});
    for(int i=n-2;i>=0;i--)b.emplace_back(a[i][m-1],atom{i,m-1});
    for(int i=m-2;i>=1;i--)b.emplace_back(a[0][i],atom{0,i});
    if(op&2)reverse(all(b));
    if(op&1)b.insert(b.end(),b.front()),b.erase(b.begin());
    if(solve_border(b)){
      fl=true;
      break;
    }
  }
  if(!fl)giveup();
  for(int i=0;i<n;i++)a[i][0]=a[i][m-1]=0;
  for(int i=0;i<m;i++)a[0][i]=a[n-1][i]=0;
  s=++nod,e=++nod;
  int cnt=0;
  for(int i=1;i<n-1;i++)
    for(int j=1;j<m-1;j++)
      if(a[i][j]){
        ++cnt;
        id[i][j]=++nod;
        pos[nod][0]=i;
        pos[nod][1]=j;
        if((i+j)%2==0){
          add_edge(s,id[i][j]);
        }else{
          add_edge(id[i][j],e);
        }
      }
  for(int i=1;i<n-1;i++)
    for(int j=1;j<m-1;j++)
      if(a[i][j]&&(i+j)%2==0){
        if(a[i-1][j])add_edge(id[i][j],id[i-1][j]);
        if(a[i+1][j])add_edge(id[i][j],id[i+1][j]);
        if(a[i][j-1])add_edge(id[i][j],id[i][j-1]);
        if(a[i][j+1])add_edge(id[i][j],id[i][j+1]);
      }
  while(bfs()){
    memcpy(cur+1,hed+1,nod<<2);
    cnt-=dfs(s,1)*2;
  }
  if(cnt!=0){
    giveup();
  }
  for(int i=0;i<tot;i+=2)
    if(val[i]==0&&val[i^1]==1){
      int u=to[i^1],v=to[i];
      if(u!=s&&v!=e){
        setup({pos[u][0],pos[u][1]},{pos[v][0],pos[v][1]});
      }
    }
  cout<<"YES"<<endl;
  for(int i=0;i<n*2-1;i++){
    for(int j=0;j<m*2-1;j++)cout<<mp[i][j];
    cout<<endl;
  }
}