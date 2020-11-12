#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5,inf=1e9+5;
int n,m,q,ux,uy,tim,vis[N],lst[N],nxt[N],a[N][N];
inline int r(int x){return (x%n+n)%n;}
inline int c(int y){return (y%m+m)%m;}
struct section{
  int l,r;
  inline bool includes(int p)const{
    return l<=p&&p<=r;
  }
};
inline int findNext(int x,int y){
  int max=-1,res=-1;
  for(int i=x-1;i<=x+1;i++)
    if(max<a[r(i)][c(y+1)]){
      res=i,max=a[r(i)][c(y+1)];
    }
  return res;
}
inline int moveToFirst(int x,int y){
  while(y<m){
    x=r(findNext(x,y));
    y++;
  }
  return x;
}
void modify(int x,int y){
  section cur{x,x},tmp;
  int pos=moveToFirst(x,y);
  while(y--){
    tmp={inf,-inf};
    for(int i=cur.l+1;i>=cur.l-1;i--){
      int p=findNext(i,y);
      if(cur.includes(p))tmp.l=i;
    }
    for(int i=cur.r-1;i<=cur.r+1;i++){
      int p=findNext(i,y);
      if(cur.includes(p))tmp.r=i;
    }
    if(tmp.l>tmp.r)return;
    cur=tmp;
  }
  if(cur.r-cur.l>=n){
    for(int i=0;i<n;i++)nxt[i]=pos;
  }else{
    for(int i=cur.l;i<=cur.r;i++)nxt[r(i)]=pos;
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++){
      cin>>a[i][j];
    }
  for(int i=0;i<n;i++){
    nxt[i]=moveToFirst(i,0);
  }
  cin>>q;
  while(q-->0){
    int x,y,t;
    string op;
    cin>>op;
    if(op[0]=='m'){
      cin>>t;
      if(t>=m-uy){
        while(uy){
          ux=r(findNext(ux,uy));
          uy=c(uy+1);
          t--;
        }
      }
      tim++;
      while(t>=m){
        t-=m;
        ux=nxt[ux];
        if(vis[ux]==tim){
          t%=(lst[ux]-t);
        }else{
          vis[ux]=tim;
          lst[ux]=t;
        }
      }
      while(t--){
        ux=r(findNext(ux,uy));
        uy=c(uy+1);
      }
      cout<<ux+1<<" "<<uy+1<<endl;
    }else{
      cin>>x>>y,x--,y--;
      cin>>a[x][y];
      modify(r(x-1),c(y-1));
      modify(r(x),c(y-1));
      modify(r(x+1),c(y-1));
    }
  }
}