#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,w,h;
queue<int> q;
map<int,pair<bool,int>> p;
inline int locate(int x,int y){
  if(!x)return y;
  if(y==h)return h+x;
  if(x==w)return w+h+h-y;
  return w+w+h+h-x;
}
inline pair<double,double> locate(double k){
  if(0<k&&k<h)return {0,k};
  if(h<k&&k<h+w)return {k-h,h};
  if(h+w<k&&k<h+h+w)return {w,w+h+h-k};
  return {w+w+h+h-k,0};
}
struct line{
  int id,l,r,x1,y1,x2,y2;
  inline void init(){
    l=locate(x1,y1);
    r=locate(x2,y2);
    if(l>r)swap(l,r);
    p[l]=make_pair(0,id);
    p[r]=make_pair(1,id);
  }
}a[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>w>>h;
  for(int i=1;i<=n;i++){
    cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2;
    a[i].id=i,a[i].init();
  }
  for(const auto &it:p){
    if(it.second.first){
      while(q.front()<=a[it.second.second].l)q.pop();
    }
    q.push(it.first);
    if(q.size()==n){
      auto l=locate(q.front()-0.3),r=locate(q.back()+0.3);
      if((l.first==0&&r.first==0)||(l.first==w&&r.first==w)){
        l={0.5,0},r={0.5,h};
      }
      if((l.second==0&&r.second==0)||(l.second==h&&r.second==h)){
        l={0,0.5},r={w,0.5};
      }
      printf("1\n%.1lf %.1lf %.1lf %.1lf\n",l.first,l.second,r.first,r.second);
      return 0;
    }
  }
  printf("2\n0 0.5 %d %.1lf\n0.5 %d %.1lf 0\n",w,h-.5,h,w-.5);
}