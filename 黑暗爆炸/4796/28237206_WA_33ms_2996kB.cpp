#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 5e5+5;
const ll INF = 912345678999999;
const ll MOD = 1e9 + 7;
ll read()
{ ll res=0,f=1;
  char ch=getchar();
  for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
  for(;ch>='0'&&ch<='9';ch=getchar())res=res*10+ch-'0';
  return res*f;
}
int n,m,cnt;
int a[N],ans[N];
string s;
void solve()
{   cin>>s;
    for(int i=1;i<s.size();i++)if(s[i]!=s[i-1])cnt++;
    if(cnt>=s.size()/3*2)
    {  cout<<0;
       return;  
    }
    cnt=0;
    for(int i=0;i<s.size();i+=3)
    {   string tmp=s.substr(i,3);
        //cout<<tmp<<endl;
        if(tmp=="001")ans[++cnt]=i+2,s[i+1]='1',s[i+2]='0'; 
        if(tmp=="011")ans[++cnt]=i+1,s[i]='1',s[i+1]='0'; 
        if(tmp=="100")ans[++cnt]=i+1,s[i]='0',s[i+1]='1';
        if(tmp=="110")ans[++cnt]=i+2,s[i+1]='0',s[i+2]='1';
        if(tmp=="111")
        {   if(i==0||s[i-1]=='0')ans[++cnt]=i+2,s[i+1]=s[i+2]='0';
            else ans[++cnt]=i+1,s[i]=s[i+1]='0';
        } 
        if(tmp=="000") 
        {   if(i==0||s[i-1]=='0')ans[++cnt]=i+1,s[i]=s[i+1]='1';
            else ans[++cnt]=i+2,s[i+1]=s[i+2]='1';
        }
    }
    //cout<<s<<endl;
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)printf("%d ",ans[i]);

}
int main()
{   int t=1;
    while(t--)
    {
        solve();
    }
    return 0;
}