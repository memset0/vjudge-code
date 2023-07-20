#include<bits/stdc++.h>
using namespace std;
const int N=362880;
int n,l,r,a[9],x[9],y[9],G[N][2],pre[N],q[N+5];
inline int order(int *x){
  int s=0;
  for(int i=0;i<9;i++){
    int t=x[i];
    for(int j=0;j<i;j++)if(x[j]<x[i])t--;
    s=s*(10-i)+t;
  }
  return s;
}
inline void draw(int x){
  static int a[9],use[9];
  for(int i=8;i>=0;i--){
    a[i]=x%(10-i);
    x/=10-i;
  }
  for(int i=0;i<9;i++)use[i]=false;
  for(int i=0;i<9;i++){
    int t=a[i];a[i]=0;
    for(int i=0;i<t;i++){
      ++a[i];
      while(use[a[i]])++a[i];
    }
    use[a[i]]=true;
  }
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      cout<<a[i*3+j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}
int main(){
  ios::sync_with_stdio(false);
  for(int i=0;i<9;i++){
    cin>>a[i];
    x[i]=i;
  }
  int cnt=0;
  do{
    for(int i=0;i<9;i++)y[i]=x[i];
    int t=y[5];y[5]=y[4];y[4]=y[3];y[3]=t;
    G[cnt][0]=order(y);
    for(int i=0;i<9;i++)y[i]=x[i];
    t=y[0];y[0]=y[3];y[3]=y[6];y[6]=y[7];y[7]=y[8];y[8]=y[5];y[5]=y[2];y[2]=y[1];y[1]=t;
    G[cnt][1]=order(y);
    ++cnt;
  }while(next_permutation(x,x+9));
  memset(pre,-1,sizeof(pre));
  l=r=1,q[1]=0;
  while(l<=r){
    int u=q[l++];
    for(int i=0;i<2;i++)
      if(!~pre[G[u][i]]){
        pre[G[u][i]]=u;
        q[++r]=G[u][i];
      }
  }
  vector<int> ans;
  int u=order(a);
  if(u==-1){
    cout<<"UNSOLVABLE"<<endl;
  }
  while(u){
    ans.push_back(u);
    u=pre[u];
  }
  cout<<ans.size()<<endl;
  ans.push_back(0);
  for(int i=0;i<ans.size();i++){
    draw(ans[i]);
  }
} 