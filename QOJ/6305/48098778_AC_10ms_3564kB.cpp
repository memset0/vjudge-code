#include<bits/stdc++.h>
#define x first
#define y second
#define all(x) begin(x),end(x)
using namespace std;
using pii=pair<int,int>;
const int M=40;
const int mov[6][2]={
  {0,2},{0,-2},
  {1,1},{1,-1},
  {-1,1},{-1,-1},
};
int T,n;
int __a[M<<1][M<<1],*_a[M<<1],**a;
int __b[M<<1][M<<1],*_b[M<<1],**b;
int __c[M<<1][M<<1],*_c[M<<1],**c;
int main(){
#ifndef ONLINE_JUDGE
  freopen("H.in","r",stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  for(int i=0;i<(M<<1);i++){
    _a[i]=__a[i]+M;
    _b[i]=__b[i]+M;
    _c[i]=__c[i]+M;
  }
  a=_a+M;
  b=_b+M;
  c=_c+M;
  for(int i=0;i<=4;i++)
    for(int j=-8-i;j<=i+8;j+=2){
      c[i][j]=1;
      c[-i][j]=1;
    }
  for(int i=5;i<=8;i++)
    for(int j=i-8;j<=8-i;j+=2){
      c[i][j]=1;
      c[-i][j]=1;
    }
  // for(int i=-8;i<=8;i++){
  //   for(int j=-20;j<=20;j++)
  //     if(c[i][j]){
  //       cout<<i<<","<<j<<"  ";
  //     }
  //   cout<<endl;
  // }
  cin>>T;
  while(T--){
    cin>>n;
    vector<pii> nod;
    for(int x,y,i=1;i<=n;i++){
      cin>>x>>y;
      x-=9;
      for(int i=-12;i<=12;i++)
        if(c[x][i]&&!--y){
          y=i;
          break;
        }
      nod.emplace_back(x,y);
    }
    // for(auto [x,y]:nod)cerr<<"! "<<x<<' '<<y<<endl;
    int ans=0;
    for(int i=0;i<nod.size();i++){
      memset(__a,0,sizeof(__a));
      memset(__b,0,sizeof(__b));
      for(int j=0;j<nod.size();j++)
        if(i!=j){
          a[nod[j].x][nod[j].y]=1;
        }
      queue<pii> q;
      b[nod[i].x][nod[i].y]=1;
      q.push(make_pair(nod[i].x,nod[i].y));
      // fprintf(stderr,"i=%d x=%d y=%d\n",i,nod[i].x,nod[i].y);
      while(q.size()){
        pii u=q.front(),v;
        q.pop();
        for(int i=0;i<6;i++){
          for(int k=1;;k++){
            v.x=u.x+2*k*mov[i][0];
            v.y=u.y+2*k*mov[i][1];
            if(!c[v.x][v.y])break;
            if(a[u.x+k*mov[i][0]][u.y+k*mov[i][1]]){
              bool fl=true;
              for(int t=k+1;t<=k*2;t++)
                if(a[u.x+t*mov[i][0]][u.y+t*mov[i][1]]){
                  fl=false;
                  break;
                }
              if(fl){
                if(!b[v.x][v.y]){
                  // printf("(%d,%d) -> (%d,%d)\n",u.x,u.y,v.x,v.y);
                  ++ans;
                  b[v.x][v.y]=1;
                  q.push(v);
                }
              }
              break;
            }
          }
        }
      }
    }
    cout<<ans<<endl;
  }
}