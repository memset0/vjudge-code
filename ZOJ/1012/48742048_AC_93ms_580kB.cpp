#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAXN 10000 + 10

struct Job {
  int a, b;
  int t, u;
  int v, w, x;
  bool operator<(const Job &x) const {
    if (t != x.t) return t < x.t;
    else
      return v > x.v;
  }
};
Job jobs[MAXN];
bool finish[MAXN];

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  int F, M, N, L;
  int kase = 0;
  while (scanf("%d", &F) != EOF && F) {
    scanf("%d%d%d", &M, &N, &L);
    for (int i = 0; i < L; i++) scanf("%d%d%d%d%d%d%d", &jobs[i].a, &jobs[i].b, &jobs[i].t, &jobs[i].u, &jobs[i].v, &jobs[i].w, &jobs[i].x);
    sort(jobs, jobs + L);
    memset(finish, 0, sizeof(finish));
    int income = 0;
    for (int i = 0; i < F; i++) {
      int cpu = M, mem = N;
      for (int j = 0; j < L; j++) {
        if (jobs[j].t > i) break;
        if (!finish[j] && cpu >= jobs[j].a && mem >= jobs[j].b) {
          cpu -= jobs[j].a;
          mem -= jobs[j].b;
          finish[j] = true;
          income += jobs[j].v;
          int t = i + 1; // the finished time
          if (t < jobs[j].u) income += jobs[j].w * (jobs[j].u - t);
          if (t > jobs[j].u) income -= jobs[j].x * (t - jobs[j].u);
        }
      }
    }
    for (int i = 0; i < L; i++)
      if (!finish[i] && jobs[i].u <= F) income -= jobs[i].x * (F - jobs[i].u);
    printf("Case %d: %d\n\n", ++kase, income);
  }
  return 0;
}