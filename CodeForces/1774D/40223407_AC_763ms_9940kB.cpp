#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int main(){
  ios::sync_with_stdio(0);
  cin>>T;
  while(T--){
    cin>>n>>m;
    vector<int> cnt;
    vector<vector<int>> a;
    a.resize(n),cnt.resize(n);
    int sum=0;
    for(int i=0;i<n;i++){
      a[i].resize(m);
      for(int j=0;j<m;j++){
        cin>>a[i][j];
        cnt[i]+=a[i][j];
      }
      sum+=cnt[i];
    }
    if(sum%n){
      cout<<-1<<endl;
      continue;
    }
    int tar=sum/n;
    vector<tuple<int,int,int>> ans;
    
    vector<int> pos(n);
    for(int i=0;i<n;i++){
      pos[i]=i;
    }
//    sort(pos.begin(),pos.end(),[&](int x,int y){
//      return cnt[pos[i]]<cnt[pos[j]];
//    });
    for(int j=0;j<m;j++){
      vector<int> more,less;
      for(int i=0;i<n;i++){
        if(cnt[i]>tar&&a[i][j]){
          more.push_back(i);
        }
        if(cnt[i]<tar&&!a[i][j]){
          less.push_back(i);
        }
      }
      while(more.size()&&less.size()){
        int x=*--more.end();
        int y=*--less.end();
        cnt[x]--;
        cnt[y]++;
        ans.push_back(make_tuple(x+1,y+1,j+1));
        more.pop_back();
        less.pop_back();
      }
    }
    
    cout<<ans.size()<<endl;
    for(auto it:ans){
      cout<<get<0>(it)<<" "<<get<1>(it)<<" "<<get<2>(it)<<endl;
    }
  }
}