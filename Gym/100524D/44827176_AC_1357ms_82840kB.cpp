#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 141072 + 9, M = 531446, H = 17;
const int mod = 258280327, g = 11;
int k, m, n, q[N], ans[N];
vector<int> r[H], b[H], s[H];
constexpr int sub(int x, int y) { return x -= y, x < 0 ? x + mod : x; }
constexpr int add(int x, int y) { return x += y, x >= mod ? x - mod : x; }
constexpr int power(int a, int b) {
  int s = 1;
  for (; b; b >>= 1, a = (ll)a * a % mod)
    if (b & 1) s = (ll)s * a % mod;
  return s;
}
const int w3 = power(g, (mod - 1) / 2 / 3);
const int iw3 = power(w3, mod - 2);
int rev[M], len = 1, bit = 0, w[2][M], inv[M];
void init(int n) {
  while (len <= n) len *= 3, ++bit;
  for (int i = 1; i < len; i *= 3) {
    int uni[2];
    uni[0] = power(g, (mod - 1) / 2 / (i * 3));
    uni[1] = power(uni[0], mod - 2);
    for (int k = 0; k < 2; k++) {
      w[k][i] = 1;
      for (int j = 1; j < i; ++j) {
        w[k][i + j] = (ll)w[k][i + j - 1] * uni[k] % mod;
      }
    }
  }
  // for (int i = 1; i < len; i++) assert((ll)w[0][i] * w[1][i] % mod == 1);
  for (int i = 0; i < len; ++i) {
    vector<int> b;
    for (int x = i; x; x /= 3) {
      b.push_back(x % 3);
    }
    b.resize(bit);
    // reverse(b.begin(), b.end());
    for (int j = 0; j < bit; j++) {
      rev[i] = rev[i] * 3 + b[j];
    }
  }
}
void DFT(vector<int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++)
    if (i < rev[i]) {
      swap(a[i], a[rev[i]]);
    }
  for (int len = 1; len < n; len *= 3)
    for (int i = 0; i < n; i += len * 3)
      for (int j = 0; j < len; j++) {
        int omega = w[0][len + j];
        int x = a[i + j];
        int y = (ll)omega * a[len + i + j] % mod;
        int z = (ll)omega * omega % mod * a[len * 2 + i + j] % mod;
        a[i + j] = add(add(x, y), z);
        a[i + j + len] = (x + (ll)y * w3 + (ll)z * iw3) % mod;
        a[i + j + len * 2] = (x + (ll)y * iw3 + (ll)z * w3) % mod;
      }
}
void IDFT(vector<int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++)
    if (i < rev[i]) {
      swap(a[i], a[rev[i]]);
    }
  for (int len = 1; len < n; len *= 3)
    for (int i = 0; i < n; i += len * 3)
      for (int j = 0; j < len; j++) {
        int omega = w[1][len + j];
        int x = a[i + j];
        int y = (ll)omega * a[len + i + j] % mod;
        int z = (ll)omega * omega % mod * a[len * 2 + i + j] % mod;
        a[i + j] = add(add(x, y), z);
        a[i + j + len] = (x + (ll)y * iw3 + (ll)z * w3) % mod;
        a[i + j + len * 2] = (x + (ll)y * w3 + (ll)z * iw3) % mod;
      }
}
vector<int> square(vector<int> a) {
  a.resize(len);
  DFT(a);
  for (int i = 0; i < len; i++) a[i] = (ll)a[i] * a[i] % mod;
  IDFT(a);
  int inv_len = power(len, mod - 2);
  a.resize(n);
  for (int &x : a) x = (ll)x * inv_len % mod;
  a.insert(a.begin(), 0);
  return a;
}
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#else
  freopen("dichromatic.in", "r", stdin);
  freopen("dichromatic.out", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> k >> m;
  for (int i = 1; i <= k; i++) {
    cin >> q[i];
    n = max(n, q[i]);
  }
  init(2 * n + 3);
  for (int h = 0; h <= m; h++) {
    if (h == 0 || h == 1) {
      r[h].resize(n + 1);
      b[h].resize(n + 1);
      if (h == 0) {
        r[h][1] = 1;
        b[h][0] = 1;
      } else if (h == 1) {
        b[h][1] = 1;
        b[h][2] = 2;
        b[h][3] = 1;
        r[h][3] = 1;
        r[h][4] = 4;
        r[h][5] = 6;
        r[h][6] = 4;
        r[h][7] = 1;
      }
    } else {
      b[h] = square(s[h - 1]);
      r[h] = square(b[h]);
    }
    s[h].resize(n + 1);
    for (int i = 0; i <= n; i++) s[h][i] = add(r[h][i], b[h][i]);
    for (int i = 0; i <= n; i++) ans[i] = add(ans[i], s[h][i]);
    // fprintf(stderr, "r[%d] = ", h);
    // for (int i = 0; i <= n; i++) cerr << r[h][i] << " \n"[i == n];
    // fprintf(stderr, "b[%d] = ", h);
    // for (int i = 0; i <= n; i++) cerr << b[h][i] << " \n"[i == n];
    // fprintf(stderr, "s[%d] = ", h);
    // for (int i = 0; i <= n; i++) cerr << s[h][i] << " \n"[i == n];
  }
  for (int i = 1; i <= k; i++) cout << ans[q[i]] << " \n"[i == k];
}

// vector<int> operator*(const vector<int> &a, const vector<int> &b) {
//   vector<int> c(a.size() + b.size() - 1);
//   for (int i = 0; i < a.size(); i++)
//     for (int j = 0; j < b.size(); j++) {
//       c[i + j] = (c[i + j] + (long long)a[i] * b[j]) % mod;
//     }
//   c.resize(n + 1);
//   return c;
// }

// void DFT_bf(vector<int> &a, bool fl) {
//   int uni = power(g, (mod - 1) / 2 / a.size());
//   vector<int> b(a.size());
//   if (fl) {
//     uni = power(uni, mod - 2);
//   }
//   // cerr << "! " << uni << endl;
//   // assert(power(uni, len) == 1);
//   for (int i = 0; i < len; i++) {
//     for (int j = 0; j < len; j++) {
//       b[j] = (b[j] + (ll)power(uni, (i * j) % (mod - 1)) * a[i]) % mod;
//       // cerr << "! " << i << " " << j << " " << a[i] << " " << power(uni, j) << " " << b[j] << endl;
//     }
//   }
//   for (int i = 0; i < len; i++) {
//     a[i] = b[i];
//   }
//   if (fl) {
//     int inv_len = power(len, mod - 2);
//     for (int &x : a) x = (ll)x * inv_len % mod;
//   }
// }//