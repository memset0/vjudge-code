#include<bits/stdc++.h>
using namespace std;
const int L[10]={3,0,2,0,1,1,3,0,3,1};
const int M[10]={5,0,7,7,2,7,7,1,7,7};
const int R[10]={3,3,1,3,3,2,2,3,3,3};
const int S=110;
int n,A[S],B[S],f[S][2][16],g[S][2][16];
int main(){
  freopen("digital.in","r",stdin);
  freopen("digital.out","w",stdout);
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int j=0;j<4;j++){
    for(int i=n,x;i;--i)cin>>x,A[i]|=x<<j;
    for(int i=n+1,x;i;--i)cin>>x,B[i]|=x<<j;
  }
  for(int i=n,x;i;--i)cin>>x,A[i]|=x<<4;
  memset(f,-1,sizeof(f));
  f[0][0][0]=1;
  for(int i=0;i<n;i++)
    for(int w=0;w<2;w++){
      for(int s=0;s<1<<4;s++)
        if(f[i][w][s]!=-1){
          for(int a=0;a<10;a++)
            for(int b=0;b<10;b++){
              int c=a+b+w,nx=0;
              if(c>=10)c-=10,nx++;
              int s1=R[a]|(R[b]<<1)|(R[c]<<2)|s;
              int s2=M[a]|(M[b]<<1)|(M[c]<<2);
              int s3=L[a]|(L[b]<<1)|(L[c]<<2);
              if(s1==B[i+1]&&s2==A[i+1]){
                if(f[i+1][nx][s3]==-1){
                  f[i+1][nx][s3]=w*16+s;
                  g[i+1][nx][s3]=a*100+b*10+c;
                }
              }
            }
        }
    }
  int S=B[n+1];
  if(f[n][0][S]==-1)cout<<"NO"<<endl;
  else{
    vector<int> sta;
    for(int i=n;i;S=f[i--][S>>4][S&15]){
      sta.push_back(g[i][S>>4][S&15]);
    }
    for(auto v:sta)cout<<v/100;
    cout<<endl;
    for(auto v:sta)cout<<v/10%10;
    cout<<endl;
    for(auto v:sta)cout<<v%10;
    cout<<endl;
  }
}
//dafsasdfsaf