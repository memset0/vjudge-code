#include<bits/stdc++.h>
#define all(v) (v).begin(),(v).end()
#define impossible {cout<<"IMPOSSIBLE"<<endl; goto next;}
#define four(a,i,j) a[i][j],a[i][m-j+1],a[n-i+1][j],a[n-i+1][m-j+1]
using namespace std;
const int N=110;
using atom=int;
int T,n,m,a[N][N],b[N][N];
atom trans[256][256];
vector<int> p[256];
vector<atom> atom_list;
vector<pair<char,int>> op;
inline tuple<int,int,int,int> to_tuple(atom x){return make_tuple(x>>6,x>>4&3,x>>2&3,x&3);}
inline atom to_atom(const tuple<int,int,int,int> &x){return get<0>(x)<<6|get<1>(x)<<4|get<2>(x)<<2|get<3>(x);}
inline atom operator""_s(unsigned long long x){return to_atom({x/1000,x/100%10,x/10%10,x%10});}
inline vector<int> ask(int a,int b,int c,int d,atom e){return p[trans[to_atom({a,b,c,d})][e]];}
inline atom movement(int a,int b,int c,int d,int aa,int bb,int cc,int dd){
  auto get=[&](int x){return x==aa?0:(x==bb?1:(x==cc?2:3));};
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
  p[0123_s]={0,0};
  p[0231_s]={3,1,3,1};
  p[0312_s]={1,3,1,3};
  p[1032_s]={0,2,3,0,2,3};
  p[1203_s]={0,2,0,2};
  p[1320_s]={3,0,3,0};
  p[2013_s]={2,0,2,0};
  p[2130_s]={1,2,1,2};
  p[2301_s]={0,1,2,0,1,2};
  p[3021_s]={0,3,0,3};
  p[3102_s]={2,1,2,1};
  p[3210_s]={0,2,0,1,2,1};
  for(int a=0;a<4;a++)
    for(int b=0;b<4;b++)if(a!=b)
      for(int c=0;c<4;c++)if(a!=c&&b!=c)
        for(int d=0;d<4;d++)if(a!=d&&b!=d&&c!=d)
          atom_list.push_back(to_atom({a,b,c,d}));
  for(atom x:atom_list)
    for(atom y:atom_list)
      trans[x][y]=movement(x>>6,x>>4&3,x>>2&3,x&3,y>>6,y>>4&3,y>>2&3,y&3);
  cin>>T;
  while(T-->0){
    cin>>m>>n;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++){
        cin>>a[i][j];
        b[i][j]=(i-1)*m+j;
      }
    for(int i=1;i<n-i+1;i++)
      for(int j=1;j<m-j+1;j++){
        vector<int> p{four(a,i,j)},q{four(b,i,j)};
        sort(all(p));
        // cout<<i<<" "<<j<<endl;
        // cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<" "<<p[3]<<endl;
        // cout<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<endl;
        if(p!=q)impossible;
        tie(four(a,i,j))=to_tuple(movement(four(a,i,j),four(b,i,j)));
      }
    // for(int i=1;i<=n;i++)
    //   for(int j=1;j<=m;j++)
    //     printf("%d%c",a[i][j]," \n"[j==m]);
    if(ask(four(a,1,1),0123_s).size()){
      apply(ask(four(a,1,1),0123_s),1,1);
    }else{
      apply(ask(four(a,1,1),0132_s),1,1),R(n);
    }
    for(int i=2;i<n-i+1;i++){
      if(ask(four(a,i,1),0123_s).size()){
        apply(ask(four(a,i,1),0123_s),i,1);
      }else{
        apply(ask(four(a,i,1),0132_s),i,1);
        R(n-i+1);
      }
    }
    for(int j=2;j<m-j+1;j++){
      if(ask(four(a,1,j),0123_s).size()){
        apply(ask(four(a,1,j),0123_s),1,j);
      }else{
        apply(ask(four(a,1,j),0321_s),1,j);
        C(m-j+1);
      }
    }
    for(int i=2;i<n-i+1;i++)
      for(int j=2;j<m-j+1;j++){
        const auto &sol=ask(four(a,i,j),0123_s);
        if(!sol.size())impossible;
        apply(sol,i,j);
      }
    cout<<"POSSIBLE "<<op.size();
    for(const auto &it:op)cout<<" "<<it.first<<it.second;
    cout<<endl;
  next:
    op.clear();
  }
}