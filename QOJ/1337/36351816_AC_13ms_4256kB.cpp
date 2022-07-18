#include<bits/stdc++.h>
using namespace std;

const int N=150009;
int n,m,t,p[N],rk[N];
string s;
vector<int> a,b,c;
vector<pair<bool,string>> ans;

void apply(bool t,const string &s){
  a.clear(),b.clear();
  for(int i=0;i<n;i++)if(s[i]=='1')(p[i]&1?b:a).push_back(p[i]);
  if(t)swap(a,b);
  c=a,c.insert(c.end(),b.begin(),b.end());
  reverse(c.begin(),c.end());
  for(int i=0;i<n;i++)if(s[i]=='1')p[i]=c.back(),c.pop_back();
  ans.push_back(make_pair(t,s));
}

void solve(){
  int s00=((n+1)/2+1)/2,s01=(n+1)/4,s10=s01,s11=n/2-s10;
  assert(s00+s01+s10+s11==n);
  for(int i=0;i<s00;i++)rk[i<<1]=i<<1;
  for(int i=0;i<s10;i++)rk[(i+s00)<<1]=i<<1|1;
  for(int i=0;i<s01;i++)rk[i<<1|1]=(i+s00)<<1;
  for(int i=0;i<s11;i++)rk[(i+s10)<<1|1]=(i+s10)<<1|1;
  for(int i=1;i<n;i+=2)rk[i]=n-1-rk[i]+(n&1);
  // for(int i=0;i<n;i++)fprintf(stderr,"%d%c",rk[i]," \n"[i+1==n]);
  for(int k=0;k<14;k++){
    apply(0,string(n,'1'));
    s=string(n,'0');
    // for(int i=0;i<n;i++)cerr<<p[i]<<" \n"[i+1==n];
    int t=0;
    for(int i=0;i<n;i++)if(p[i]%2==0&&(rk[p[i]]>>k)%2==1)s[i]='1';
    for(int i=0;i<n;i++)if(p[i]%2==1&&(rk[p[i]]>>k)%2==1)s[i]='1';
    // cerr<<s<<endl;
    // for(int i=0;i<n;i++)cerr<<rk[p[i]]<<" \n"[i+1==n];
    apply(1,s);
  }
  apply(0,string(n,'1'));
  s=string(n,'0');
  for(int i=0;i<n;i++)if(p[i]!=i)s[i]='1';
  apply(1,s);
  // for(int i=0;i<n;i++)cerr<<p[i]<<" \n"[i+1==n];
  for(int i=0;i<n;i++)assert(p[i]==i);
}

int main(){
#ifdef memset0
  // freopen("1.in","r",stdin);
  freopen("2.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int i=0;i<n;i++)cin>>p[i];
  solve();
  cout<<ans.size()<<endl;
  for(const auto &it:ans)cout<<(it.first?1:0)<<" "<<it.second<<endl;
}