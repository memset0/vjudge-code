#include<bits/stdc++.h>
using namespace std;
int main(){
  string s;
  cin>>s;
  vector<int> p(26);
  for(int i=0;i<s.length();i++){
    p[s[i]-'a']=1;
  }
  int ans=0;
  for(int i=0;i<26;i++){
    ans+=p[i];
  }
  if(ans&1){
    cout<<"IGNORE HIM!"<<endl;
  }else{
    cout<<"CHAT WITH HER!"<<endl;
  }
}