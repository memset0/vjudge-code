#include<bits/stdc++.h>
#ifndef memset0
  #define endl '\n'
#endif
#define getl get<0>
#define getr get<1>
#define getid get<2>
using namespace std;
const int N=1e5+9;
int T,n,m,k,tot,cnt[N],s[N];
int ap[N],vis[N],tim;
long long sum[N];
void add(int k,int x){
  for(;k<N;k+=k&-k)s[k]+=x;
}
int ask(int k){
  int sum=0;
  for(;k;k-=k&-k)sum+=s[k];
  return sum;
}
vector<int> ins[N],del[N],used;
vector<tuple<int,int,int>> a[N],b[N];
vector<int>ad[N],dl[N];
void shrink(vector<tuple<int,int,int>> &a){
  sort(a.begin(),a.end());
  vector<tuple<int,int,int>> b;
  for(const auto &it:a){
    if(b.size()&&getr(b.back())>=getl(it)-1){
      getr(b.back())=max(getr(b.back()),getr(it));
    }else{
      b.push_back(it);
    }
  }
  a.swap(b);
  for(auto &it:a){
    getid(it)=++tot;
  }
}
void A(int x){
  if(vis[x]<tim)vis[x]=tim,ap[x]=0;
}
set<int>ele;
set<tuple<int,int,int> >st;
int tans,IND,fa[N*20];
int getf(int x){
  return fa[x]==x?x:fa[x]=getf(fa[x]);
}
void Merge(int l,int r){
  // cerr<<"MERGE "<<l<<" "<<r<<"\n";
  set<tuple<int,int,int> >::iterator ii=st.lower_bound({r,N,0});
  if(ii==st.begin())return;
  --ii;
  if(getr(*ii)<l)return;
  int tl=getl(*ii),tr=getr(*ii),ti=getid(*ii),tf;
  st.erase(ii);
  while(1){
    ii=st.lower_bound({r,N,0});
    if(ii==st.begin())break;
    --ii;
    // cerr<<"FIND "<<getl(*ii)<<" "<<getr(*ii)<<"\n";
    if(getr(*ii)<l)break;
    tl=getl(*ii);
    tf=getf(getid(*ii));
    if(tf!=getf(ti))fa[tf]=fa[ti],--tans;
    st.erase(ii);
  }
  // cerr<<"TL="<<tl<<" tr="<<tr<<"\n";
  st.insert({tl,tr,ti});
}
void Ins(int x){
  //cerr<<"INS "<<x<<"\n";
  set<tuple<int,int,int> >::iterator ii=st.lower_bound({x,N,0});
  set<int>::iterator it;
  ++tans;
  if(ii!=st.begin()){
    --ii;
    if(getl(*ii)<=x&&x<=getr(*ii)){
      it=ele.lower_bound(x);
      int tl=getl(*ii),tr=getr(*ii),ti=getid(*ii);
      st.erase(ii);
      st.insert({*it,tr,ti}),--it,st.insert({tl,*it,ti});
    }
  }
  st.insert({x,x,++IND}),fa[IND]=IND;
  it=ele.lower_bound(x);
  if(it!=ele.end()&&(*it)==x+1)Merge(x,x+1);
  if(it!=ele.begin()){
    --it;
    if((*it)==x-1)Merge(x-1,x);
  }
  ele.insert(x);
}
void Del(int x){
  // cerr<<"DEL "<<x<<"\n";
  set<tuple<int,int,int> >::iterator ii=st.lower_bound({x,N,0});
  set<int>::iterator it=ele.lower_bound(x);
  ele.erase(it);
  if(ii!=st.begin()){
    --ii;
    int tl=getl(*ii),tr=getr(*ii),ti=getid(*ii);
    if(getl(*ii)==x&&getr(*ii)==x)return(void)(st.erase(ii));
    else if(getl(*ii)==x){
      st.erase(ii);
      it=ele.upper_bound(x),st.insert({*it,tr,ti});
    }else if(getr(*ii)==x){
      st.erase(ii);
      it=ele.upper_bound(x),--it;
      st.insert({tl,*it,ti});
    }
  }
  // cerr<<"SEGS:\n";
  // for(ii=st.begin();ii!=st.end();++ii)cerr<<getl(*ii)<<" "<<getr(*ii)<<" "<<getf(getid(*ii))<<"\n";
}
int main(){
#ifdef memset0
  freopen("D.in","r",stdin);
  // freopen("D.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    ++tim;
    cin>>n>>m>>k;
    fill_n(sum+1,n,0);
    fill_n(cnt+1,n,0);
    for(int i=1;i<=n;i++){
      a[i].clear();
      ins[i].clear();
      del[i].clear();
    }
    for(int x1,x2,y1,y2,i=1;i<=k;i++){
      cin>>x1>>y1>>x2>>y2;
      if(x1==x2){
        a[x1].emplace_back(y1,y2,-1);
        // b[y1].emplace_back(x1,x2,-1);
        // b[y2].emplace_back(x1,x2,-1);
      }else{
        b[y1].emplace_back(x1,x2,-1);
        // a[x1].emplace_back(y1,y2,-1);
        // a[x2].emplace_back(y1,y2,-1);
        used.push_back(y1);
      }
    }
    tot=0;
    for(int i=1;i<=n;i++)shrink(a[i]);
    sort(used.begin(),used.end());
    used.erase(unique(used.begin(),used.end()),used.end());
    for(int i:used)
      for(auto &[l,r,id]:b[i]){
        if(l>1){
          auto it=upper_bound(a[l-1].begin(),a[l-1].end(),make_tuple(i,m+1,-1));
          if(it!=a[l-1].begin()){
            // cerr<<"! "<<getl(*it)<<" "<<getr(*it)<<" "<<getid(*it)<<endl;
            if(getr(*--it)>=i){
              --l;
            }
          }
        }
        if(r<n){
          auto it=upper_bound(a[r+1].begin(),a[r+1].end(),make_tuple(i,m+1,-1));
          if(it!=a[r+1].begin()){
            if(getr(*--it)>=i){
              ++r;
            }
          }
        }
      }
    for(int i=1;i<=n;i++)
      for(const auto &[l,r,id]:a[i]){
        b[l].emplace_back(i,i,-1);
        b[r].emplace_back(i,i,-1);
        used.push_back(l);
        used.push_back(r);
      }
    sort(used.begin(),used.end());
    used.erase(unique(used.begin(),used.end()),used.end());
    for(int k=1;k<n;k++){
      auto &x=a[k],&y=a[k+1];
      if(x.empty()||y.empty())continue;
      auto check=[&k](const tuple<int,int,int> &x,const tuple<int,int,int> &y){
        // fprintf(stderr,"check (%d %d %d) (%d %d %d)\n",getl(x),getr(x),getid(x),getl(y),getr(y),getid(y));
        if(getl(x)<getl(y)){
          if(getl(y)<=getr(x)){
            b[getl(y)].emplace_back(k,k+1,-1);
          }
        }else{
          if(getl(x)<=getr(y)){
            b[getl(x)].emplace_back(k,k+1,-1);
          }
        }
      };
      int i=0,j=0;
      check(x[i],y[j]);
      // cerr<<"! "<<k<<" "<<x.size()<<" "<<y.size()<<endl;
      while(i+1<x.size()||j+1<y.size()){
        // cerr<<"! "<<i<<" "<<j<<" "<<x.size()<<" "<<y.size()<<endl;
        if(i+1<x.size()&&j+1<y.size()){
          if(getl(x[i])<getl(y[j])){
            ++i;
          }else{
            ++j;
          }
        }else if(i+1<x.size()){
          ++i;
        }else{
          ++j;
        }
        check(x[i],y[j]);
      }
    }
    // cerr<<"!!"<<endl;
    for(int i:used)shrink(b[i]);
    // for(int i=1;i<=n;i++)for(auto it:a[i])cerr<<"a::"<<i<<" "<<getl(it)<<" "<<getr(it)<<endl;
    // for(int i=1;i<=m;i++)for(auto it:b[i])cerr<<"b::"<<i<<" "<<getl(it)<<" "<<getr(it)<<endl;

    for(int i:used)
      for(const auto &[l,r,id]:b[i]){
        ins[l].push_back(i);
        del[r].push_back(i);
      }
    for(int cur=0,i=1;i<=n;i++){
      for(int x:ins[i])add(x,1),++cur;
      sum[i]=sum[i-1]+cur;
      for(const auto &[l,r,id]:a[i]){
        sum[i]+=r-l+1;
        sum[i]-=ask(r)-ask(l-1);
      }
      for(int x:del[i])add(x,-1),--cur;
    }

    // cerr<<"!!! "<<n<<" "<<m<<" "<<k<<" :: xry"<<endl;
    IND=0;
    for(int i=1;i<=n;++i)vector<int>().swap(ad[i]),vector<int>().swap(dl[i]);
    for(int i:used)for(int j=0;j<b[i].size();++j)ad[getl(b[i][j])].push_back(i),dl[getr(b[i][j])+1].push_back(i);
    tans=0;
    st.clear(),ele.clear();
    for(int i=1;i<=n;++i){
      //cerr<<"---------------------------------i="<<i<<"\n";
      for(int j=0;j<dl[i].size();++j)A(dl[i][j]),--ap[dl[i][j]];
      for(int j=0;j<ad[i].size();++j)A(ad[i][j]),++ap[ad[i][j]];
      // for(int i=1;i<=m;++i)cerr<<"AP "<<i<<"="<<(A(i),ap[i])<<"\n";
      //cerr<<ap[1]<<"\n";
      for(int j=0;j<dl[i].size();++j)if(!ap[dl[i][j]]){
        set<int>::iterator it=ele.lower_bound(dl[i][j]);
        if(it!=ele.end()&&(*it)==dl[i][j])Del(dl[i][j]);
      }
      for(int j=0;j<ad[i].size();++j){
        set<int>::iterator it=ele.lower_bound(ad[i][j]);
        //assert(ap[ad[i][j]]);
        if(it==ele.end()||(*it)!=ad[i][j])Ins(ad[i][j]);
      }
      for(int j=0;j<a[i].size();++j)Merge(getl(a[i][j])-1,getr(a[i][j])+1);
      cnt[i]=tans;
      // cerr<<"SEGS:\n";
      // for(set<tuple<int,int,int> >::iterator ii=st.begin();ii!=st.end();++ii)cerr<<getl(*ii)<<" "<<getr(*ii)<<" "<<getf(getid(*ii))<<"\n";
      // cerr<<"TANS="<<tans<<"\n";
    }

    // cerr<<"!!! "<<n<<" "<<m<<" "<<k<<" :: output"<<endl;
    for(int i=1;i<=n;i++)cout<<sum[i]<<" "<<cnt[i]<<endl;
    for(int i:used)b[i].clear();
    used.clear();
  }
}