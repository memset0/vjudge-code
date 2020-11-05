#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,p=10,e=5;
int n,w,h;
struct line{int x1,y1,x2,y2;}a[N];
inline bool right(int ax,int ay,int bx,int by){return (long long)ax*by<(long long)bx*ay;}
inline bool cross(const line &a,const line &b){
  return (right(a.x1,a.y1,b.x1,b.y1)^right(a.x1,a.y1,b.x2,b.y2))||(right(b.x1,b.y1,a.x1,a.y1)^right(b.x1,b.y1,a.x2,a.y2));
}
inline bool check(const line &u){
  for(int i=1;i<=n;i++)if(!cross(u,a[i]))return 0;
  return 1;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>w>>h,w*=p,h*=p;
  for(int i=1;i<=n;i++){
    cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2;
    a[i].x1*=p,a[i].x2*=p,a[i].y1*=p,a[i].y2*=p;
  }
  for(auto sol:vector<line>{{0,e,w,e},{0,h-e,w,h-e},{e,0,e,h},{w-e,0,w-e,h},{0,e,w,h-e},{e,h,w-e,0}}){
    if(check(sol))return cout<<"1\n"<<sol.x1/10.<<" "<<sol.y1/10.<<" "<<sol.x2/10.<<" "<<sol.y2/10.<<endl,0;
  }
  cout<<"2\n"<<"0 0.5 "<<w/10.<<" "<<(h-e)/10.<<"\n"<<"0.5 "<<h/10.<<" "<<(w-e)/10.<<" 0"<<endl;
}