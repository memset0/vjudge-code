#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const unsigned long long mod=1000000009;
inline string ntos(int n){
  string ret;
  do{
    ret+=n%10+'0';
    n/=10;
  }while(n>0);
  reverse(ret.begin(),ret.end());
  return ret;
}
struct Sudoku{
  short map[9][9];
  vector<string> trans;
  void input(){
    string buf;
    trans.clear();
    for(int i=0;i<9;++i){
      cin>>buf;
      for(int j=0;j<9;++j){
        if(buf[j]=='.'){
          map[i][j]=0;
        }else{
          map[i][j]=buf[j]-'0';
        }
      }
    }
  }
  void swapDigit(int u,int v){
    for(int i=0;i<9;++i){
      for(int j=0;j<9;++j){
        if(map[i][j]==u){
          map[i][j]=v;
        }else if(map[i][j]==v){
          map[i][j]=u;
        }
      }
    }
  }
  void minimize(){
    int cnt=1;
    for(int i=0;i<9;++i){
      for(int j=0;j<9;++j){
        if(map[i][j]>=cnt){
          if(map[i][j]!=cnt){
            trans.push_back((string)"D "+ntos(map[i][j])+" "+ntos(cnt));
            swapDigit(map[i][j],cnt);
          }
          ++cnt;
        }
      }
    }
  }
  void flip(){
    trans.push_back("F");
    short tmp[9][9];
    for(int i=0;i<9;++i){
      for(int j=0;j<9;++j){
        tmp[j][i]=map[i][j];
      }
    }
    memcpy(map,tmp,sizeof(map));
  }
  void swapTriple(int i,int j){
    trans.push_back((string)"C "+ntos(i+1)+" "+ntos(j+1));
    for(int k=0;k<3;++k){
      for(int l=0;l<9;++l){
        swap(map[l][i*3+k],map[l][j*3+k]);
      }
    }
  }
  void swapColumn(int i,int j){
    trans.push_back((string)"c "+ntos(i+1)+" "+ntos(j+1));
    for(int k=0;k<9;++k){
      swap(map[k][i],map[k][j]);
    }
  }
};
unsigned long long HASH(const Sudoku &s){
  long long ret=0;
  for(int i=0;i<9;++i){
    for(int j=0;j<9;++j){
      ret=ret*mod+s.map[i][j];
    }
  }
  return ret;
}
typedef pair<unsigned long long,vector<string>> Trans;
int top;
void initColumn(int i,Sudoku s,vector<Trans> &bucket){
  if(i==3){
    Sudoku bak=s;
    s.minimize();
    bucket[top++]=(make_pair(HASH(s),s.trans));
    s=bak;
    s.flip();
    s.minimize();
    bucket[top++]=(make_pair(HASH(s),s.trans));
    return;
  }
  Sudoku bak=s;
  initColumn(i+1,s,bucket);
  s.swapColumn(0+i*3,1+i*3);
  initColumn(i+1,s,bucket);
  s=bak;
  s.swapColumn(1+i*3,2+i*3);
  initColumn(i+1,s,bucket);
  s=bak;
  s.swapColumn(0+i*3,2+i*3);
  initColumn(i+1,s,bucket);
  bak=s;
  s.swapColumn(1+i*3,2+i*3);
  initColumn(i+1,s,bucket);
  s=bak;
  s.swapColumn(0+i*3,1+i*3);
  initColumn(i+1,s,bucket);
}
void initTripleColumn(Sudoku s,vector<Trans> &bucket){
  Sudoku bak=s;
  initColumn(0,s,bucket);
  s.swapTriple(0,1);
  initColumn(0,s,bucket);
  s=bak;
  s.swapTriple(1,2);
  initColumn(0,s,bucket);
  s=bak;
  s.swapTriple(0,2);
  initColumn(0,s,bucket);
  bak=s;
  s.swapTriple(1,2);
  initColumn(0,s,bucket);
  s=bak;
  s.swapTriple(0,1);
  initColumn(0,s,bucket);
}
const int SIZE=5184;
vector<int> ord(SIZE);
vector<Trans> tmp(SIZE);
bool cmp(const int &i,const int &j){
  return tmp[i].first<tmp[j].first;
}
void init(Sudoku s,vector<Trans> &bucket){
  top=0;
  Sudoku bak=s;
  initTripleColumn(s,tmp);
  s=bak;
  s.flip();
  initTripleColumn(s,tmp);
  for(int i=0;i<SIZE;++i){
    ord[i]=i;
  }
  sort(ord.begin(),ord.end(),cmp);
  bucket.resize(SIZE);
  for(int i=0;i<SIZE;++i){
    bucket[i]=tmp[ord[i]];
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#else
  freopen("intellectual.in","r",stdin);
  freopen("intellectual.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n;
  cin>>n;
  vector<Sudoku> s(n);
  vector<vector<Trans>> bucket(n);
  for(int i=0;i<n;++i){
    s[i].input();
    init(s[i],bucket[i]);
  }
  auto solve=[&](const int &a,const int &b){
    int i=0,j=0;
    while(i<(int)bucket[a].size()&&j<(int)bucket[b].size()){
      if(bucket[a][i].first==bucket[b][j].first){
        vector<string> ans=bucket[a][i].second;
        puts("Yes");
        ans.insert(ans.end(),bucket[b][j].second.begin(),bucket[b][j].second.end());
        if(ans.size()){
          reverse(ans.begin()+(int)bucket[a][i].second.size(),ans.end());
        }
        printf("%d\n",(int)ans.size());
        for(int i=0;i<(int)ans.size();++i){
          puts(ans[i].c_str());
        }
        return;
      }else{
        (bucket[a][i].first<bucket[b][j].first)?++i:++j;
      }
    }
    puts("No");
  };
  for(int i=0;i<n;++i){
    for(int j=i+1;j<n;++j){
      solve(i,j);
    }
  }
  return 0;
}
///dfasdfasdfasdfadfasdf