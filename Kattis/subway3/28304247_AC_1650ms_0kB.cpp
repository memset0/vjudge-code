#include<bits/stdc++.h>
using namespace std;
int T,n,m,begin_pos,end_pos,f[1<<19],vis[1<<19],g[1<<19];
string begin_str,end_str;
queue<int> q,q2;
vector<int> a[1<<19];
map<string,int> mp;
vector<pair<int,int>> b[1<<19];
void read(){
  int i,j;
  mp.clear();
  string stops,s,lines;
  getline(cin,stops),getline(cin,stops),getline(cin,stops);
  for(i=0;i<(int)stops.size();i++)if(stops[i]==',')stops[i]=' ';
  n=0;
  istringstream in(stops);
  in>>s;
  while(in>>s)mp[s]=++n;
  getline(cin,lines);
  for(i=0;i<(int)lines.size();i++)if(lines[i]==',')lines[i]=' ';
  m=0;
  istringstream in2(lines);
  in2>>s;
  while(in2>>s)++m;
  for(i=0;i<n;i++) b[i].clear();
  for(i=0;i<m;i++){
    a[i].clear();
    string l;
    getline(cin,l);
    for(j=0;j<(int)l.size();j++){
      if(l[j]==',') l[j]=' ';
    }
    istringstream in(l);
    in>>s;
    in>>s;
    while(in>>s){
      b[mp[s]].push_back(make_pair(i,(int)a[i].size()));
      a[i].push_back(mp[s]);
    }
  }
  cin>>s,cin>>s,cin>>s,cin>>s;
  begin_pos=mp[s];
  begin_str=s;
  cin>>s,cin>>s,cin>>s,cin>>s;
  end_pos=mp[s];
  end_str=s;
}
void push(int x){
  for(int i=0;i<(int)b[x].size();i++){
    if(vis[b[x][i].first]==0){
      q2.push(b[x][i].first);
    }
    vis[b[x][i].first]=1;
  }
}
void solve(){
  int i,ans=0;
  while(!q.empty())q.pop();
  while(!q2.empty())q2.pop();
  memset(f,-1,sizeof(f));
  memset(g,-1,sizeof(g));
  memset(vis,0,sizeof(vis));
  f[begin_pos]=0;
  g[begin_pos]=1;
  push(begin_pos);
  while(f[end_pos]==-1){
    ans++;
    q=q2;
    while(!q2.empty())q2.pop();
    while(!q.empty()){
      int x=q.front();
      q.pop();
      int best=-1;
      for(i=0;i<(int)a[x].size();i++){
        if(g[a[x][i]]==ans&&f[a[x][i]]>best){
          best=f[a[x][i]];
        }
        if(g[a[x][i]]!=ans){
          f[a[x][i]]=max(f[a[x][i]],best);
          if(g[a[x][i]]==-1){
            g[a[x][i]]=ans+1;
            push(a[x][i]);
          }
        }
        if(best!=-1)++best;
      }
      best=-1;
      for(i=(int)a[x].size()-1;i>=0;i--){
        if(g[a[x][i]]==ans&&f[a[x][i]]>best){
          best=f[a[x][i]];
        }
        if(g[a[x][i]]!=ans){
          f[a[x][i]]=max(f[a[x][i]],best);
          if(g[a[x][i]]==-1){
            g[a[x][i]]=ans+1;
            push(a[x][i]);
          }
        }
        if(best!=-1)++best;
      }
    }
  }
  int ans2=f[end_pos];
  printf("optimal travel from %s to %s: %d line%s, %d minute%s\n",begin_str.c_str(),end_str.c_str(),ans,(ans>1)?"s":"",ans2,(ans2>1)?"s":"");
}

int main(){
  cin>>T;
  while(T--){
    read();
    solve();
  }
}