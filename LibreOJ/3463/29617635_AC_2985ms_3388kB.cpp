#include<bits/stdc++.h>
#define NUM 0
#define OPT 1
using namespace std;
const int N=5e4+9,M=10,mod=1e9+7;
int n,m,rt,nod,a[N],at[M],cur[M],src[M][N],pre[1<<M];
string str;
vector<int> num;
vector<char> opt;
struct Node{
  int ch[2],dp[2];
  bool type;
  char val;
}e[N<<2];
void dumpUntil(){
  vector<int> curnum;
  vector<char> curopt;
  curnum.push_back(num.back()),num.pop_back();
  while(opt.back()!='('&&opt.size()){
    curopt.push_back(opt.back()),opt.pop_back();
    curnum.push_back(num.back()),num.pop_back();
  }
  int u=curnum.back();
  for(int i=(int)curopt.size()-1;i>=0;i--){
    ++nod;
    e[nod].type=OPT;
    e[nod].val=curopt[i];
    e[nod].ch[0]=u;
    e[nod].ch[1]=curnum[i];
    u=nod;
  }
  num.push_back(u);
}
int parse(const string &str){
  for(int i=0,tmp=0;i<str.length();i++){
    if(isdigit(str[i])){
      ++nod;
      e[nod].type=NUM;
      e[nod].val=str[i]-'0';
      num.push_back(nod);
    }else if(str[i]=='<'||str[i]=='>'||str[i]=='?'){
      opt.push_back(str[i]);
    }else if(str[i]=='('){
      opt.push_back(str[i]);
    }else if(str[i]==')'){
      dumpUntil();
      opt.pop_back();
    }
  }
  dumpUntil();
  assert(num.size()==1);
  assert(opt.size()==0);
  return num.back();
}
void DP(int u){
  if(e[u].type==NUM)return;
  int l=e[u].ch[0],r=e[u].ch[1];
  DP(l),DP(r);
  if(e[u].val=='<'){
    e[u].dp[0]=((long long)e[l].dp[0]*e[r].dp[0]+(long long)e[l].dp[1]*e[r].dp[0]+(long long)e[l].dp[0]*e[r].dp[1])%mod;
    e[u].dp[1]=(long long)e[l].dp[1]*e[r].dp[1]%mod;
  }else if(e[u].val=='>'){
    e[u].dp[0]=(long long)e[l].dp[0]*e[r].dp[0]%mod;
    e[u].dp[1]=((long long)e[l].dp[1]*e[r].dp[1]+(long long)e[l].dp[1]*e[r].dp[0]+(long long)e[l].dp[0]*e[r].dp[1])%mod;
  }else if(e[u].val=='?'){
    e[u].dp[0]=(2ll*e[l].dp[0]*e[r].dp[0]+(long long)e[l].dp[1]*e[r].dp[0]+(long long)e[l].dp[0]*e[r].dp[1])%mod;
    e[u].dp[1]=(2ll*e[l].dp[1]*e[r].dp[1]+(long long)e[l].dp[1]*e[r].dp[0]+(long long)e[l].dp[0]*e[r].dp[1])%mod;
  }
}
inline void output(int u){
  fprintf(stderr,"e[%d]->%d,%d | %s,%c | %d %d\n",u,e[u].ch[0],e[u].ch[1],e[u].type==NUM?"num":"opt",(char)(e[u].type==NUM?e[u].val+'0':e[u].val),e[u].dp[0],e[u].dp[1]);
  if(e[u].ch[0])output(e[u].ch[0]);
  if(e[u].ch[1])output(e[u].ch[1]);
}
int init(int x){
  for(int i=0;i<num.size();i++)
    if((x>>e[num[i]].val)&1){
      e[num[i]].dp[0]=0,e[num[i]].dp[1]=1;
    }else{
      e[num[i]].dp[0]=1,e[num[i]].dp[1]=0;
    }
  DP(rt);
//  output(rt);
  return e[rt].dp[0];
}
inline bool cmp(int x,int y){
  return cur[x]==cur[y]?x<y:cur[x]<cur[y];
}
int solve(){
  int ans=0,x=(1<<m)-1;
  sort(at,at+m,cmp);
//  for(int i=0;i<m;i++)fprintf(stderr,"%d%c",cur[i]," \n"[i+1==m]);
//  for(int i=0;i<m;i++)fprintf(stderr,"%d%c",at[i]," \n"[i+1==m]);
  for(int lst=0,i=0;i<m;i++){
    x^=1<<at[i];
//    printf("%d > %d %d\n",x,pre[x],cur[at[i]]);
    ans=(ans+(long long)(pre[x]-lst)*cur[at[i]])%mod;
    lst=pre[x];
  }
  return ans<0?ans+mod:ans;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m;
  for(int i=0;i<m;i++)
    for(int j=1;j<=n;j++){
      cin>>src[i][j];
    }
  cin>>str;
  rt=parse(str);
  num.clear(),opt.clear();
  for(int i=1;i<=nod;i++)
    if(e[i].type==NUM){
      num.push_back(i);
    }else{
      opt.push_back(i);
    }
  for(int x=0;x<(1<<m);x++){
    pre[x]=init(x);
//    fprintf(stderr,"pre[%d]=%d\n",x,pre[x]);
  }
  for(int j=0;j<m;j++)at[j]=j;
  long long ans=0;
  for(int i=1;i<=n;i++){
    for(int j=0;j<m;j++)cur[j]=src[j][i];
    int res=solve();
//    cerr<<res<<endl;
    ans+=res;
  }
  cout<<(ans%mod)<<endl;
}