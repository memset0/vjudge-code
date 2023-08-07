#include <bits/stdc++.h>
using namespace std;

namespace mem {
const int N = 109, V = 501;
int n, k;
bool vis[V];
vector<int> pri;

#define A -1
#define B -2
#define C -3
#define D -4
#define C0 -5
#define C1 -6
#define C2 -7
#define D0 -8
#define D1 -9
#define D2 -10
enum oper {
  input,
  output,
  set,
  inc,
  dec,
  got,
  iff,
};

struct cmd {
  int id;
  oper op;
  int x, y;
  cmd *z, *z1, *z2;
  string cmp;

  void normalize() {
    if (op == inc || op == dec || op == iff) {
      if (x == C0) x = C;
      if (x == C1) x = C, y <<= 10;
      if (x == C2) x = C, y <<= 20;
      if (x == D0) x = D;
      if (x == D1) x = D, y <<= 10;
      if (x == D2) x = D, y <<= 20;
    }
  }
};
vector<cmd> ans;

inline string out(int x) {
  if (x < 0) {
    string s = " ";
    s[0] = 'A' - x - 1;
    return s;
  }
  return to_string(x);
}

inline string out(cmd *c, const cmd &u) {
  if (c == nullptr) {
    return to_string(u.id + 1);
  } else {
    return to_string(c->id);
  }
}

inline void push(const cmd &c) { ans.push_back(c); }

inline cmd get(oper op, int a = 0, int b = 0) {
  cmd new_cmd;
  new_cmd.op = op;
  if (op == input || op == output) {
    new_cmd.x = a;
  } else if (op == set || op == inc || op == dec) {
    new_cmd.x = a;
    new_cmd.y = b;
  }
  new_cmd.normalize();
  return new_cmd;
}
cmd c_end = get(output, D, 0);
cmd c_for_iff_i = get(iff);
cmd c_for_next_i = get(got);
cmd c_for_end_i = get(got);
cmd c_input = get(input, A);

void push_copy(int x, int y) {
  for (int i = 0; i < 9; i++) {
    cmd c = get(iff);
    c.x = x;
    c.y = y;
    c.z1 = 
  }
}

void solve() {
  push(get(set, C, n << 10));
  push(get(input, A));

  c_for_iff_i.x = C;
  c_for_iff_i.y = 1 << 10;
  c_for_iff_i.cmp = "<";
  c_for_iff_i.z1 = &c_for_end_i;
  c_for_iff_i.z2 = &c_input;
  push(c_for_iff_i);
  push(c_input);

  push_copy(A, C2);
  push_reset(C2);

  push(get(dec, C1, 1));
  c_for_next_i.z = &c_for_iff_i;
  push(c_for_next_i);

  c_for_end_i.z = &;
  push(c_for_end_i);

  push(c_end);
}

} // namespace mem

int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  using namespace mem;
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;

  solve();

  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) {
    ans[i].id = i + 1;
  }
  for (const auto &c : ans) {
    cout << c.id << " ";
    switch (c.op) {
    case input:
      cout << "INPUT " << out(c.x) << endl;
      break;
    case output:
      cout << "OUTPUT " << out(c.x) << endl;
      break;
    case mem::set:
      cout << "SET " << out(c.x) << " TO " << out(c.y) << endl;
      break;
    case inc:
      cout << "INCREASE " << out(c.x) << " BY " << out(c.y) << endl;
      break;
    case mem::dec:
      cout << "DECREASE " << out(c.x) << " BY " << out(c.y) << endl;
      break;
    case got:
      cout << "GOTO " << c.z->id << endl;
      break;
    case iff:
      cout << "IF " << out(c.x) << " " << c.cmp << " " << out(c.y) << " GOTO " << out(c.z1, c) << " "
           << " ELSE GOTO " << out(c.z2, c) << endl;
      break;
    }
  }
}