#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,ans[N];
set<pair<int,int>> q;
multiset<pair<int,int>> s;
vector<int> tx,ty,qa[N],qb[N];
vector<pair<int,int>> insx[N],insy[N],delx[N],dely[N];
struct node{
  int x,y;
  inline void init0(){tx.push_back(x),ty.push_back(y);}
  inline void init1(){x=lower_bound(tx.begin(),tx.end(),x)-tx.begin()+1,y=lower_bound(ty.begin(),ty.end(),y)-ty.begin()+1;}
  inline bool operator<(const node &rhs)const{return x==rhs.x?y<rhs.y:x<rhs.x;}
}a[N],b[N];
bool check(vector<pair<int,int>> *ins,vector<pair<int,int>> *del,int m){
  multiset<pair<int,int>>::iterator p;
  for(int i=1;i<=m+1;i++){
    for(const auto &it:del[i])s.erase(it);
    for(const auto &it:ins[i]){
      if(s.count(it))return false;
      s.insert(it);
      p=s.upper_bound(it);
      if(p!=s.end()&&it.second>=p->first)return false;
      p=s.lower_bound(it);
      if(p!=s.begin()&&prev(p)->second>=it.first)return false;
    }
  }
  return true;
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
    insx[a[i].x].push_back({a[i].y,b[ans[i]].y});
    delx[b[ans[i]].x+1].push_back({a[i].y,b[ans[i]].y});
    insy[a[i].y].push_back({a[i].x,b[ans[i]].x});
    dely[b[ans[i]].y+1].push_back({a[i].x,b[ans[i]].x});
  }
  if(!check(insx,delx,tx.size()))return puts("syntax error"),0;
  if(!check(insy,dely,ty.size()))return puts("syntax error"),0;
  for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
}