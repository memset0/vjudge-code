#include <bits/stdc++.h>
const int N = 102401;
int n, K;
int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }
typedef std::vector<int> bigint;
void print(bigint A) {
  for (int i = A.size() - 1; i >= 0; i--)
    putchar(A[i] + '0');
}
bigint int_to_bigint(int x) {
  if (!x)
    return bigint{0};
  bigint A;
  while (x)
    A.push_back(x % 10), x /= 10;
  return A;
}
bigint operator+(bigint A, bigint B) {
  if (A.size() < B.size())
    std::swap(A, B);
  for (int i = 0; i < B.size(); i++)
    A[i] += B[i];
  for (int i = 0; i < A.size(); i++) {
    if (A[i] < 10)
      continue;
    A[i] -= 10;
    if (i + 1 == A.size())
      A.push_back(1);
    else
      A[i + 1]++;
  }
  return A;
}
bigint operator-(bigint A, bigint B) {
  assert(A.size() >= B.size());
  for (int i = 0; i < B.size(); i++)
    A[i] -= B[i];
  for (int i = 0; i < A.size(); i++)
    if (A[i] < 0)
      assert(i + 1 < A.size()), A[i] += 10, A[i + 1]--;
  while (A.size() > 1 && !A.back())
    A.pop_back();
  return A;
}
bigint operator*(bigint A, int B) {
  for (int i = 0; i < A.size(); i++)
    A[i] *= B;
  for (int i = 0; i < A.size(); i++) {
    if (A[i] < 10)
      continue;
    if (i + 1 == A.size())
      A.push_back(0);
    A[i + 1] += A[i] / 10, A[i] %= 10;
  }
  return A;
}
bool operator<(bigint A, bigint B) {
  if (A.size() != B.size())
    return A.size() < B.size();
  for (int i = A.size() - 1; i >= 0; i--)
    if (A[i] != B[i])
      return A[i] < B[i];
  return false;
}
bool operator>(bigint A, bigint B) {
  if (A.size() != B.size())
    return A.size() > B.size();
  for (int i = A.size() - 1; i >= 0; i--)
    if (A[i] != B[i])
      return A[i] > B[i];
  return false;
}
std::set<bigint> Set;
struct node {
  bigint A, B, C;
  node(bigint A_ = bigint{0}, bigint B_ = bigint{0}, bigint C_ = bigint{0}) {
    A = A_, B = B_, C = C_;
    if (A > B)
      std::swap(A, B);
    if (A > C)
      std::swap(A, C);
    if (B > C)
      std::swap(B, C);
  }
  bool operator>(const node b) const { return A + B + C > b.A + b.B + b.C; }
  bool check() {
    if (Set.find(A) != Set.end())
      return false;
    if (Set.find(B) != Set.end())
      return false;
    if (Set.find(C) != Set.end())
      return false;
    if (A == bigint{0})
      return false;
    if (B == bigint{0})
      return false;
    if (C == bigint{0})
      return false;
    return true;
  }
};
std::priority_queue<node, std::vector<node>, std::greater<node>> Q;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  while (~scanf("%d%d", &K, &n)) {
    Q.push(node(bigint{0}, bigint{1}, int_to_bigint(K)));
    while (n) {
      node cur = Q.top();
      Q.pop();
      if (cur.check()) {
        print(cur.A), putchar(' ');
        print(cur.B), putchar(' ');
        print(cur.C), putchar('\n');
        Set.insert(cur.A), Set.insert(cur.B), Set.insert(cur.C), n--;
      }
      Q.push(node(cur.A, (cur.A + cur.C) * K - cur.B, cur.C));
      Q.push(node((cur.B + cur.C) * K - cur.A, cur.B, cur.C));
    }
    while (Q.size())
      Q.pop();
  }
}