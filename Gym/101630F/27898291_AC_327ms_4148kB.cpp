#include<bits/stdc++.h>
using namespace std;
int T,n,a,b;
vector<tuple<int,int,int,int>> out;
inline void add(int &x,int &y,int nx,int ny,int dir){
  out.push_back(dir?make_tuple(x,ny-n+1,x+n-1,ny):make_tuple(nx,y+n-1,nx-n+1,y));
  x=nx,y=ny;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  cin>>T;
  while(T-->0){
    out.clear();
    cin>>a>>b>>n;
    int dira=1,dirb=1;
    if(a<0)dira=-1,a*=-1;
    if(b<0)dirb=-1,b*=-1;
    int x=0,y=0;
    int dir=0;
    while(a-x>=n||b-y>=n){
      add(x,y,min(a,x+n-1),min(b,y+n-1),dir);
      if(a-x<b-y)++y,dir=0;else ++x,dir=1;
    }
    dir?add(x,y,x+n-1,b,dir):add(x,y,a,y+n-1,dir);
    cout<<out.size()<<endl;
    for(const auto &v:out){
      cout<<dira*get<0>(v)<<" "<<dirb*get<1>(v)<<" "<<dira*get<2>(v)<<" "<<dirb*get<3>(v)<<endl;
    }
  }
}