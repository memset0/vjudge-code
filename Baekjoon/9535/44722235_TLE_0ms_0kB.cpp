#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native") 
#include<bits/stdc++.h>
#define mp make_pair
#define all(v) (v).begin(),(v).end()
#define impossible {cout<<"IMPOSSIBLE"<<endl; goto next;}
#define four(a,i,j) a[i][j],a[i][m-j+1],a[n-i+1][j],a[n-i+1][m-j+1]
using namespace std;
const int N=110;
using atom=int;
int T,n,m,a[N][N],b[N][N];
atom tr[256][256];
vector<int> p[256];
vector<atom> atom_list;
vector<pair<char,int>> op;
inline tuple<int,int,int,int> to_tuple(atom x){return make_tuple(x>>6,x>>4&3,x>>2&3,x&3);}
inline string to_str(atom x){return to_string(x>>6)+to_string(x>>4&3)+to_string(x>>2&3)+to_string(x&3);}
inline atom to_atom(const tuple<int,int,int,int> &x){return get<0>(x)<<6|get<1>(x)<<4|get<2>(x)<<2|get<3>(x);}
inline atom ask(int i,int j){return a[i][j]<<6|a[i][m-j+1]<<4|a[n-i+1][j]<<2|a[n-i+1][m-j+1];}
inline atom operator""_s(unsigned long long x){return to_atom({x/1000,x/100%10,x/10%10,x%10});}
inline atom movement(int a,int b,int c,int d,int aa,int bb,int cc,int dd){
  auto get=[&](int x){return x==aa?0:(x==bb?1:(x==cc?2:(x==dd?3:-1)));};
  return get(a)<<6|get(b)<<4|get(c)<<2|get(d);
}
inline void R(int x){op.push_back({'R',x});for(int i=1;i<m-i+1;i++)swap(a[x][i],a[x][m-i+1]);}
inline void C(int x){op.push_back({'C',x});for(int i=1;i<n-i+1;i++)swap(a[i][x],a[n-i+1][x]);}
inline void apply(const vector<int> &v,int i,int j){
  for(int x:v)switch(x){
    case 0:R(i);break;case 1:R(n-i+1);break;
    case 2:C(j);break;case 3:C(m-j+1);break;
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  p[123_s]={0,0},p[231_s]={3,1,3,1},p[312_s]={1,3,1,3};
  p[1032_s]={0,2,3,0,2,3},p[1203_s]={0,2,0,2},p[1320_s]={3,0,3,0};
  p[2013_s]={2,0,2,0},p[2130_s]={1,2,1,2},p[2301_s]={0,1,2,0,1,2};
  p[3021_s]={0,3,0,3},p[3102_s]={2,1,2,1},p[3210_s]={0,2,0,1,2,1};
  for(int a=0;a<4;a++)
    for(int b=0;b<4;b++)if(a!=b)
      for(int c=0;c<4;c++)if(a!=c&&b!=c)
        for(int d=0;d<4;d++)if(a!=d&&b!=d&&c!=d)
          atom_list.push_back(to_atom({a,b,c,d}));
  for(atom x:atom_list)
    for(atom y:atom_list)
      tr[x][y]=movement(y>>6,y>>4&3,y>>2&3,y&3,x>>6,x>>4&3,x>>2&3,x&3);
  cin>>T;
  while(T-->0){
    cin>>m>>n;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++){
        cin>>a[i][j];
        b[i][j]=(i-1)*m+j;
      }
    if(n==1&&m==1)goto output;
    if(n==1){
      if(a[1][1]!=b[1][1])R(1);
      for(int j=1;j<=m;j++)if(a[1][j]!=b[1][j])impossible;
      goto output;
    }
    if(m==1){
      if(a[1][1]!=b[1][1])C(1);
      for(int i=1;i<=n;i++)if(a[i][1]!=b[i][1])impossible;
      goto output;
    }
    for(int i=1;i<n-i+1;i++)
      for(int j=1;j<m-j+1;j++){
        vector<int> p{four(a,i,j)},q{four(b,i,j)};
        sort(all(p));
        if(p!=q)impossible;
        tie(four(a,i,j))=to_tuple(movement(four(a,i,j),four(b,i,j)));
      }
    if(n&1){
      int i=(n+1)>>1;
      for(int j=1;j<m-j+1;j++){
        if((a[i][j]!=b[i][j]&&a[i][j]!=b[i][m-j+1])||(a[i][m-j+1]!=b[i][j]&&a[i][m-j+1]!=b[i][m-j+1]))impossible;
        tie(a[i][j],a[i][m-j+1])=a[i][j]<a[i][m-j+1]?mp(0,1):mp(1,0);
      }
      if(a[i][1])R(i);
      for(int j=1;j<m-j+1;j++)if(a[i][j])impossible;
    }
    if(m&1){
      int j=(m+1)>>1;
      for(int i=1;i<n-i+1;i++){
        if((a[i][j]!=b[i][j]&&a[i][j]!=b[n-i+1][j])||(a[n-i+1][j]!=b[i][j]&&a[n-i+1][j]!=b[n-i+1][j]))impossible;
        tie(a[i][j],a[n-i+1][j])=a[i][j]<a[n-i+1][j]?mp(0,1):mp(1,0);
      }
      if(a[1][j])C(j);
      for(int i=1;i<n-i+1;i++)if(a[i][j])impossible;
    }
    if((n&1)&&(m&1))a[(n+1)>>1][(m+1)>>1]=0;
    p[tr[ask(1,1)][123_s]].size()?apply(p[tr[ask(1,1)][123_s]],1,1):(apply(p[tr[ask(1,1)][132_s]],1,1),R(n));
    for(int i=2;i<n-i+1;i++){
      p[tr[ask(i,1)][123_s]].size()?apply(p[tr[ask(i,1)][123_s]],i,1):(apply(p[tr[ask(i,1)][132_s]],i,1),R(n-i+1));
    }
    for(int j=2;j<m-j+1;j++){
      p[tr[ask(1,j)][123_s]].size()?apply(p[tr[ask(1,j)][123_s]],1,j):(apply(p[tr[ask(1,j)][321_s]],1,j),C(m-j+1));
    }
    for(int i=2;i<n-i+1;i++)
      for(int j=2;j<m-j+1;j++){
        if(!p[tr[ask(i,j)][123_s]].size())impossible;
        apply(p[tr[ask(i,j)][123_s]],i,j);
      }
  output:
    cout<<"POSSIBLE "<<op.size();
    for(const auto &it:op)cout<<" "<<it.first<<it.second;
    cout<<endl;
  next:
    op.clear();
  }
}//dfasdfsadfasdfasdfasdf