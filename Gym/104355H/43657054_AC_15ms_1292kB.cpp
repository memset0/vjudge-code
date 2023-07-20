#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int n,cnt[N];
set<int> st;
string s[N];
bool solve(char c){
  memset(cnt,0,sizeof(cnt));
  st.clear();
  for(int i=1;i<=n;i++){
    assert(i<=n);
    for(int j=0;j<s[i].length();j++){
      if(s[i][j]==c){
        cnt[i]++;
      }
    }
    // fprintf(stderr,"%c %d %d %d %d\n",c,i,n,i<=n,cnt[i]);
    if(st.find(cnt[i])!=st.end()){
      return false;
    }
    st.insert(cnt[i]);
  }
  return true;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>s[i];
  }
  for(int c='a';c<='z';c++){
    if(solve(c)){
      puts("yes");
      for(int a='a';a<='z';a++)
        if(a!=c){
          putchar(a);
        }
      putchar(c);
      putchar('\n');
      return 0;
    }
  }
  cout<<"no"<<endl;
} 