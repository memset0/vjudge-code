#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

#define For(i, f, t) for (int i = f; i <= t; i++)

const int MaxN = 610, MaxM = 200010;
const long long INF = 1e18, INF2 = 1e9;

int N;

int N2, S, T;
int Node[MaxN], Ecnt = 1;
struct Edges {
  int t, next;
  long long f;
} e[MaxM];
void Add(int u, int v, long long f) {
  e[++Ecnt] = (Edges){v, Node[u], f}, Node[u] = Ecnt;
  e[++Ecnt] = (Edges){u, Node[v], 0}, Node[v] = Ecnt;
}

int q[MaxN], head, tail;
int Dis[MaxN];

bool bfs() {
  For(i, 1, N2) Dis[i] = INF2;
  q[head = tail = 1] = T;
  Dis[T] = 0;
  while (head <= tail) {
    int x = q[head++];
    for (int i = Node[x]; i; i = e[i].next) {
      int t = e[i].t;
      if (Dis[t] > Dis[x] + 1 && e[i ^ 1].f) {
        Dis[t] = Dis[x] + 1;
        q[++tail] = t;
      }
    }
  }
  return Dis[S] < INF2;
}

int nlast[MaxN];

long long Dinic(int x, long long f) {
  if (x == T)
    return f;
  long long now = f;
  for (int &i = nlast[x]; i; i = e[i].next) {
    int t = e[i].t;
    if (Dis[x] == Dis[t] + 1 && e[i].f) {
      int aa = Dinic(t, min(now, e[i].f));
      e[i].f -= aa;
      e[i ^ 1].f += aa;
      now -= aa;
      if (!now)
        return f;
    }
  }
  return f - now;
}

int main() {
  scanf("%d", &N);
  N2 = 2 * N + 2;
  S = N2 - 1, T = N2;
  For(i, 1, N) {
    Add(N + i, T, INF2);
    int t;
    scanf("%d", &t);
    For(j, 1, t) {
      int x;
      scanf("%d", &x);
      Add(i, x + N, INF);
    }
  }
  long long Ans = 0;
  For(i, 1, N) {
    int p;
    scanf("%d", &p);
    Ans -= INF2 - p;
    Add(S, i, INF2 - p);
  }
  while (bfs()) {
    For(i, 1, N2) nlast[i] = Node[i];
    Ans += Dinic(S, INF);
  }
  printf("%lld\n", Ans);
  return 0;
}