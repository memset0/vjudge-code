#include<bits/stdc++.h>

#define REP(i,s,n) for(int i=s;i<n;i++)
#define rep(i,n) REP(i,0,n)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const int IINF = INT_MAX;
const int MAX_K = 1000100;
const int MAX_LOG = 30;

int n,k,s[MAX_K*2],t[MAX_K*2],Next[MAX_LOG][MAX_K*2];
ii ps[MAX_K*4];

inline void compute(){

  rep(i,k){
    if( t[i] < s[i] ) t[i] += n;
    s[i+k] = s[i] + n;
    t[i+k] = t[i] + n;
    --s[i],--s[i+k];
  }
  rep(i,2*k) {
    ps[i]     = ii(s[i],i);
    ps[2*k+i] = ii(t[i],2*k+i);
  }
  sort(ps,ps+4*k);

  int last = -1;
  rep(i,4*k){
    int id = ps[i].second;
    if( id < 2*k ) {
      if( last < 0 || ( t[last] < t[id] ) ) {
        last = id;
      }
    } else {
      if( t[last] == t[id-2*k] ) last = -1;
      Next[0][id-2*k] = last;
    }
  }

  for(int i=0;i+1<MAX_LOG;i++){
    rep(j,2*k){
      if( Next[i][j] < 0 ) Next[i+1][j] = -1;
      else                 Next[i+1][j] = Next[i][Next[i][j]];
    }
  }
  int ans = IINF;
  rep(i,k){
    int tmp = 0, j = i;
    for(int lg=MAX_LOG-1;lg>=0;lg--){
      int j2 = Next[lg][j];
      if( t[j] >= s[i]+n ) break;
      if( j2 >= 0 && s[j2] < s[i]+n ){
        j = j2;
        tmp |= (1<<lg);
      }
    }
    if( t[j] >= s[i]+n )ans = min(ans,tmp+1);

  }
  if( ans == IINF ) puts("impossible");
  else              printf("%d\n",ans);
}

int main(){
  while( scanf("%d %d",&n,&k) != EOF ){
    rep(i,k) scanf("%d %d",s+i,t+i);
    compute();
  }
  return 0;
}
