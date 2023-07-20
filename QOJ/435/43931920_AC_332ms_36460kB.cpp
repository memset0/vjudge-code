#ifndef memset0
  #include"paint.h"
#endif
#include<bits/stdc++.h>
const int N=1e5+10;
int n,m,k,l[N],r[N],c[N],a[N],sum[N];
std::set<int> s[N];
std::vector<int> b[N];
struct node{
  int mid,l,r,min;
}p[N<<2];
void build(int u,int l,int r){
  p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].min=1e9;
  if(l==r){
    return;
  }
  build(u<<1,l,p[u].mid);
  build(u<<1|1,p[u].mid+1,r);
}
void modify(int u,int k,int w){
  if(p[u].l==p[u].r){
    p[u].min=w;
    return;
  }
  modify(k<=p[u].mid?(u<<1):(u<<1|1),k,w);
  p[u].min=std::min(p[u<<1].min,p[u<<1|1].min);
}
int query(int u,int l,int r){
  if(p[u].l==l&&p[u].r==r){
    return p[u].min;
  }
  if(r<=p[u].mid)return query(u<<1,l,r);
  if(l>p[u].mid)return query(u<<1|1,l,r);
  return std::min(query(u<<1,l,p[u].mid),query(u<<1|1,p[u].mid+1,r));
}
int minimumInstructions(int N,int M,int K,std::vector<int> C,std::vector<int> A,std::vector<std::vector<int>> B){
  n=N,m=M,k=K;
  for(int i=0;i<n;i++)c[i]=C[i];
  for(int i=0;i<m;i++){
    a[i]=A[i],b[i]=B[i];
    for(int x:b[i])s[i].insert(x);
  }
  std::vector<int> p,q;
  for(int i=0;i<n;i++)p.push_back(i);
  for(int i=0;i<m;i++){
    q=p,p.clear();
    for(int x:q)if(s[i].count(c[x+i])&&x+i<n)r[x]++,p.push_back(x);
  }
  p.clear();
  for(int i=0;i<n;i++)p.push_back(i);
  for(int i=0;i<m;i++){
    q=p,p.clear();
    for(int x:q)if(s[m-1-i].count(c[x-i])&&x-i>=0)l[x]++,p.push_back(x);
  }
  const auto upd=[&](int l,int r){
    l=std::max(l,0)+m-1;
    r=std::min(r,n-1);
    if(l<=r)sum[l]++,sum[r+1]--;
  };
  for(int i=0;i<n;i++)upd(i-l[i]+1,i);
  for(int i=0;i<n;i++)upd(i,i+r[i]-1);
  for(int i=0;i+1<n;i++)upd(i-l[i]+1,i+r[i+1]);
  for(int i=1;i<n;i++)sum[i]=sum[i-1]+sum[i];
  build(1,0,n);
  modify(1,0,0);
  for(int i=m;i<=n;i++)if(sum[i-1]){
    modify(1,i,1+query(1,i-m,i-1));
  }
  int ans=query(1,n,n);
  return ans<1e9?ans:-1;
}
#ifdef memset0
int main() {
  freopen("../examples/01.in","r",stdin);
  int N, M, K;
  assert(3 == scanf("%d %d %d", &N, &M, &K));
  
  std::vector<int> C(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &C[i]));
  }

  std::vector<int> A(M);
  std::vector<std::vector<int>> B(M);
  for (int i = 0; i < M; ++i) {
    assert(1 == scanf("%d", &A[i]));
    B[i].resize(A[i]);
    for (int j = 0; j < A[i]; ++j) {
      assert(1 == scanf("%d", &B[i][j]));
    }
  }

  int minimum_instructions = minimumInstructions(N, M, K, C, A, B);
  printf("%d\n", minimum_instructions);
  
  return 0;
}
#endif