#include"fun.h"
#include<bits/stdc++.h>
int n;
namespace Task1{
  const int N=25;
  int dis[N][N],dp[1<<20][20],pre[1<<20][20];
  std::vector<int> solve(int n){
    std::vector<int> ans;
    for(int i=0;i<n;i++)
      for(int j=i+1;j<n;j++){
        dis[i][j]=dis[j][i]=hoursRequired(i,j);
      }
    for(int i=0;i<n;++i)dp[1<<i][i]=1e9;
    for(int i=1;i<n;++i)
      for(int S=1;S<1<<n;++S)if(__builtin_popcount(S)==i)
        for(int u=0;u<n;++u)if((S>>u)&1)
          for(int v=0;v<n;++v)if(!((S>>v)&1))
            if(dp[S][u]>=dis[u][v]&&dp[S|(1<<v)][v]<dis[u][v]){
              dp[S|(1<<v)][v]=dis[u][v];
              pre[S|(1<<v)][v]=u;
            }
    for(int i=0;i<n;++i)if(dp[(1<<n)-1][i]<1e9){
      int j,s=(1<<n)-1;
      while(s){
        ans.push_back(i);
        j=pre[s][i],s^=1<<i,i=j;
      }
      std::reverse(ans.begin(),ans.end());
      return ans;
    }
    assert(0);
  }
}
namespace Task0{
  inline bool cmp(const std::pair<int,int> &a,const std::pair<int,int> &b){
    return a.second<b.second;
  }
  int find(int rt){
    std::vector<int> s(n);
    for(int i=0;i<n;i++)s[i]=attractionsBehind(rt,i);
    bool fl=true;
    for(int i=0;i<n;i++)fl&=s[i]<=n/2;
    if(fl)return rt;
    int min=INT_MAX,cho=-1;
    for(int i=0;i<n;i++)if(s[i]>n/2&&s[i]<min){
      min=s[i],cho=i;
    }
    return cho;
  }
  inline void sort(std::vector<std::pair<int,int>> &a,std::vector<std::pair<int,int>> &b,std::vector<std::pair<int,int>> &c){
    if(a.size()<c.size())std::swap(a,c);
    if(a.size()<b.size())std::swap(a,b);
    if(b.size()<c.size())std::swap(b,c);
  }
  std::vector<std::pair<int,int>> build(std::vector<std::pair<int,int>> a,std::vector<std::pair<int,int>> b,std::vector<std::pair<int,int>> c,int u){
    std::vector<std::pair<int,int>> ans;
    sort(a,b,c);
    if(a.size()&&b.size()){
      if(cmp(a.back(),b.back())&&b.size()+c.size()>=a.size())std::swap(a,b);
    }
    while(a.size()||b.size()||c.size()){ //a褰撳墠,b涓婁竴娆?c鍓╀笅鐨?
#ifdef local
      printf("(%d %d) (%d %d) (%d %d)\n",
        a.size()?a.back().first:-1,a.size()?a.back().second:-1,
        b.size()?b.back().first:-1,b.size()?b.back().second:-1,
        c.size()?c.back().first:-1,c.size()?c.back().second:-1);
#endif
      if(a.size()>b.size()+c.size()&&c.size()){
#ifdef local
        printf("merge !!\n");
#endif
        b.insert(b.end(),c.begin(),c.end()),c.clear();
        std::sort(b.begin(),b.end(),cmp);
        // for(const auto &x:b)printf("> %d %d\n",x.first,x.second);
        if(b.size()&&ans.size()&&cmp(ans.back(),b.back())){
          ans.push_back(b.back()),b.pop_back();
        }
      }
      if(!c.size()){ //cross
        if(!a.size())a.push_back({u,0}),u=-1;
        ans.push_back(a.back()),a.pop_back();
        std::swap(a,b);
        continue;
      }
      if(cmp(a.back(),c.back()))std::swap(a,c);
      ans.push_back(a.back()),a.pop_back();
      std::swap(a,b);
      if(c.size()&&a.size()<c.size())std::swap(a,c);
    }
    if(~u)ans.push_back({u,0});
#ifdef local
    for(const auto &x:ans)printf("> %d %d\n",x.first,x.second);
#endif
    return ans;
  }
  std::vector<int> solve(int u){
    // printf("solve %d\n",u);
    std::vector<int> ret,du(n),dv(n),G;
    for(int i=0;i<n;i++)if(i!=u&&hoursRequired(u,i)==1)G.push_back(i);
    std::vector<std::pair<int,int>> ans,S[3];
    for(int i=0;i<n;i++)if(i!=u)du[i]=hoursRequired(G[0],i);
    for(int i=0;i<n;i++)if(i!=u)dv[i]=hoursRequired(G[1],i);
    for(int i=0;i<n;i++)if(i!=u){
      if(du[i]<dv[i])S[0].push_back({i,du[i]+1});
      if(du[i]>dv[i])S[1].push_back({i,dv[i]+1});
      if(du[i]==dv[i])S[2].push_back({i,du[i]-1});
    }
    for(int fl=0;fl<G.size();fl++){
      std::sort(S[fl].begin(),S[fl].end(),cmp);
    }
#ifdef local
    for(int fl=0;fl<G.size();fl++){
      printf("[%d] => ",fl);
      for(auto x:S[fl])printf("(%d,%d) ",x.first,x.second);
      puts("");
    }
#endif
    ans=build(S[0],S[1],S[2],u);
    for(const auto &it:ans)ret.push_back(it.first);
    return ret;
  }
  std::vector<int> solve(){
    return solve(find(rand()%n));
  }
}
std::vector<int> createFunTour(int N,int Q){
  n=N;
  if(n<=17)return Task1::solve(n);
  return Task0::solve();
}






























#ifdef memset0
static void wrongAnswer(std::string message) {
  printf("WA: %s\n", message.c_str());
  exit(0);
}

namespace tree_helper {

static int N;
static int logN;
static std::vector<std::vector<int>> parent;
static std::vector<int> depth;
static std::vector<int> subtree_size;

static void dfs(
    const std::vector<std::vector<int>>& adj_list,
    int current_node, int parent_node) {
  parent[0][current_node] = parent_node;
  subtree_size[current_node] = 1;
  for (int i = 0; i < static_cast<int>(adj_list[current_node].size()); ++i) {
    const int next_node = adj_list[current_node][i];
    if (next_node != parent_node) {
      depth[next_node] = depth[current_node] + 1;
      dfs(adj_list, next_node, current_node);
      subtree_size[current_node] += subtree_size[next_node];
    }
  }
}

static void initializeTree(const std::vector<std::vector<int>>& adj_list) {
  N = static_cast<int>(adj_list.size());

  depth = std::vector<int>(N, 0);
  subtree_size = std::vector<int>(N, 0);
  for (logN = 0; (1 << logN) < N; ++logN) {}
  parent = std::vector<std::vector<int>>(logN, std::vector<int>(N, 0));

  dfs(adj_list, 0, 0);
  for (int i = 1; i < logN; ++i) {
    for (int j = 0; j < N; ++j) {
      parent[i][j] = parent[i - 1][parent[i - 1][j]];
    }
  }
}

static int getLowestCommonAncestor(int X, int Y) {
  if (depth[X] < depth[Y]) {
    std::swap(X, Y);
  }
  for (int i = logN - 1; i >= 0; --i) {
    if (depth[parent[i][X]] >= depth[Y]) {
      X = parent[i][X];
    }
  }
  if (X == Y) {
    return X;
  }
  for (int i = logN - 1; i >= 0; --i) {
    if (parent[i][X] != parent[i][Y]) {
      X = parent[i][X];
      Y = parent[i][Y];
    }
  }
  return parent[0][X];
}

static int getDistance(int X, int Y) {
  return depth[X] + depth[Y] - 2 * depth[getLowestCommonAncestor(X, Y)];
}

static int attractionsBehind(int X, int Y) {
  if (X == Y) {
    return N;
  }
  for (int i = logN - 1; i >= 0; --i) {
    if (depth[parent[i][X]] > depth[Y]) {
      X = parent[i][X];
    }
  }
  if (Y == parent[0][X]) {
    return N - subtree_size[X];
  }
  return subtree_size[Y];
}

static void checkFunTour(const std::vector<int>& fun_tour) {
  if (static_cast<int>(fun_tour.size()) != N) {
    wrongAnswer("Invalid size");
  }

  std::vector<bool> visited_attractions(N, false);
  for (int i = 0; i < N; ++i) {
    if (fun_tour[i] < 0 || fun_tour[i] >= N) {
      wrongAnswer("Invalid index");
    }
    if (visited_attractions[fun_tour[i]]) {
      wrongAnswer("Repeated index");
    }
    visited_attractions[fun_tour[i]] = true;
  }

  int last_travel_time = getDistance(fun_tour[0], fun_tour[1]);
  for (int i = 2; i < N; ++i) {
    int travel_time = getDistance(fun_tour[i - 1], fun_tour[i]);
    if (travel_time > last_travel_time) {
      wrongAnswer("Tour is not fun");
    }
    last_travel_time = travel_time;
  }
}

}  // namespace tree_helper

static int N, Q;

int hoursRequired(int X, int Y) {
  if (--Q < 0) {
    wrongAnswer("Too many queries");
  }
  if (X < 0 || X >= N || Y < 0 || Y >= N) {
    wrongAnswer("Invalid index");
  }
  return tree_helper::getDistance(X, Y);
}

int attractionsBehind(int X, int Y) {
  if (--Q < 0) {
    wrongAnswer("Too many queries");
  }
  if (X < 0 || X >= N || Y < 0 || Y >= N) {
    wrongAnswer("Invalid index");
  }
  return tree_helper::attractionsBehind(X, Y);
}

int main() {
#ifdef local
  freopen("../examples/03.in", "r", stdin);
#endif
  assert(2 == scanf("%d %d", &N, &Q));

  std::vector<std::vector<int>> adj_list(N);
  for (int i = 0; i < N - 1; ++i) {
    int A, B;
    assert(2 == scanf("%d %d", &A, &B));
    adj_list[A].push_back(B);
    adj_list[B].push_back(A);
  }
  tree_helper::initializeTree(adj_list);

  std::vector<int> fun_tour = createFunTour(N, Q);
  tree_helper::checkFunTour(fun_tour);

  for (int i = 0; i < N; ++i) {
    printf("%d%c", fun_tour[i], " \n"[i == N - 1]);
  }
  return 0;
}
#endif