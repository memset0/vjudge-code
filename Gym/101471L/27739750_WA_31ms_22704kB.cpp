#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,ans[N];
set<pair<int,int>> q;
vector<int> tx,ty,qa[N],qb[N];
vector<pair<int,int>> cx[N],cy[N];
struct node{
  int x,y;
  inline void init0(){tx.push_back(x),ty.push_back(y);}
  inline void init1(){x=lower_bound(tx.begin(),tx.end(),x)-tx.begin()+1,y=lower_bound(ty.begin(),ty.end(),y)-ty.begin()+1;}
  inline bool operator<(const node &rhs)const{return x==rhs.x?y<rhs.y:x<rhs.x;}
}a[N],b[N];
void check(vector<pair<int,int>> &v){
  sort(v.begin(),v.end());
  // for(int i=0;i<v.size();i++)printf("(%d,%d) ",v[i].first,v[i].second);if(v.size())putchar('\n');
  for(int i=0;i+1<v.size();i++)if(v[i].second>=v[i+1].first)puts("syntax error"),exit(0);
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y,a[i].init0();
  for(int i=1;i<=n;i++)cin>>b[i].x>>b[i].y,b[i].init0();
  sort(tx.begin(),tx.end()),tx.erase(unique(tx.begin(),tx.end()),tx.end());
  sort(ty.begin(),ty.end()),ty.erase(unique(ty.begin(),ty.end()),ty.end());
  for(int i=1;i<=n;i++)a[i].init1(),b[i].init1(),qa[a[i].x].push_back(i),qb[b[i].x].push_back(i);
  for(int i=1;i<=tx.size();i++){
    for(int u:qa[i])q.insert({a[u].y,u});
    for(int u:qb[i]){
      auto it=q.upper_bound({b[u].y,114514});
      if(it==q.begin())return puts("syntax error"),0;
      --it,ans[it->second]=u,q.erase(it);
    }
  }
  // for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
  for(int i=1;i<=n;i++){
    cx[a[i].x].push_back({a[i].y,b[ans[i]].y});
    cx[b[ans[i]].x].push_back({a[i].y,b[ans[i]].y});
    cy[a[i].y].push_back({a[i].x,b[ans[i]].x});
    cy[b[ans[i]].y].push_back({a[i].x,b[ans[i]].x});
  }
  for(int i=1;i<=tx.size();i++)check(cx[i]);
  for(int i=1;i<=ty.size();i++)check(cy[i]);
  for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
}