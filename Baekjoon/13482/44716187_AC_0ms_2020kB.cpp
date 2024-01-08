#include<bits/stdc++.h>
using namespace std;
int main(){
  int s;
  cin>>s;
  if(!s){
    puts("?/?/?");
    return 0;
  }
  puts("i=? max ?");
  string S="x=x max x";
  for(char s='j';s<='z';s++)S[0]=s,S[2]=S[8]=s-1,cout<<S<<endl;
  puts("a=z/z");
  for(char i='b';i<'i';i++){
    string s1,s2;
    s1+=i,s2+=i-1;
    string s=s1+"="+s2+"+"+s2;
    cout<<s<<endl;
  }
  int pr=0;
  for(int i=0;i<8;i++)
    if(1&(s>>i)){
      if(pr)putchar('+');
      pr=1;
      putchar('a'+i);
    }
  puts("");
}//dafadsfadfadfa