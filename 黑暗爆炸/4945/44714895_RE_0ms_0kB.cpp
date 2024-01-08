#include <bits/stdc++.h>
using namespace std;

const int CASE = 10;
using T = vector<pair<int, pair<size_t, string>>>;

namespace lib {
const char BASE[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
pair<size_t, string> encode_base64(vector<bool> a) {
  size_t n = a.size();
  a.resize((a.size() + 5) / 6 * 6);
  string s;
  for (size_t i = 0; i < a.size(); i += 6) {
    s.push_back(BASE[a[i] | a[i + 1] << 1 | a[i + 2] << 2 | a[i + 3] << 3 | a[i + 4] << 4 | a[i + 5] << 5]);
  }
  return {n, s};
}
vector<bool> decode_base64(pair<size_t, string> it) {
  string &s = it.second;
  vector<bool> a(s.length() * 6);
  for (size_t i = 0; i < s.length(); i++) {
    size_t x = find(BASE, BASE + 64, s[i]) - BASE;
    for (int j = 0; j < 6; j++) {
      a[i * 6 + j] = x & 1;
      x >>= 1;
    }
  }
  a.resize(it.first);
  return a;
}
} // namespace lib

vector<int> handle_input(ifstream &cin) {
  int n, m, a, b;
  string s;
  cin >> n >> m >> s >> a >> b;
  return {n, m, (int)s.length(), a, b, (int)s[0], (int)s[1]};
} // function handle_input

T handle_output(ifstream &fin, ifstream &fout) {
  string s;
  fout >> s;
  if (s == "-1") {
    return {{0, {0, ""}}};
  }
  vector<int> a(s.length());
  for (int i = 0; i < a.size(); i++) {
    a[i] = s[i] - 'A';
    assert(0 <= a[i] && a[i] <= 2);
  }
  vector<bool> b(a.size() << 1);
  for (int i = 0; i < b.size(); i += 2) {
    b[i] = a[i >> 1] & 1;
    b[i + 1] = (a[i >> 1] >> 1) & 1;
  }
  return {{1, lib::encode_base64(b)}};
} // function handle_output

void generate_output(int task, T ans) {
  if (ans.size() == 1 && ans[0].second.first == 0) {
    cout << "-1" << endl;
    return;
  }
  for (auto it : ans) {
    vector<bool> b = lib::decode_base64(it.second);
    vector<int> a(b.size() >> 1);
    for (int i = 0; i < a.size(); i++) {
      a[i] = b[i << 1] | (b[i << 1 | 1] << 1);
    }
    string s;
    for (int i = 0; i < a.size(); i++) {
      s += 'A' + a[i];
    }
    while (it.first--) {
      cout << s;
    }
  }
  cout << endl;
} // function generate_output

// ==============================================================

vector<string> code;

string to_string(const string &);
template <class K, class V> string to_string(const pair<K, V> &);
template <class... Args> string to_string(const tuple<Args...> &);
template <class T> string to_string(const vector<T> &);

string to_string(const string &s) { return '"' + s + '"'; }
template <class K, class V> string to_string(const pair<K, V> &it) { return "{" + to_string(it.first) + "," + to_string(it.second) + "}"; }
template <class T> string to_string(const vector<T> &vec) {
  string res = "{";
  for (size_t i = 0; i < vec.size(); i++) {
    if (i) res += ",";
    res += to_string(vec[i]);
  }
  res += "}";
  return res;
}

template <typename T, T...> struct integer_seq {};
template <size_t N, size_t... I> struct gen_indices : gen_indices<(N - 1), (N - 1), I...> {};
template <size_t... I> struct gen_indices<0, I...> : integer_seq<size_t, I...> {};
template <typename H> string &to_string_impl(string &s, H &&h) {
  s += to_string(forward<H>(h));
  return s;
}
template <typename H, typename... T> string &to_string_impl(string &s, H &&h, T &&...t) {
  s += to_string(forward<H>(h)) + ",";
  return to_string_impl(s, forward<T>(t)...);
}
template <typename... T, size_t... I> string to_string(const tuple<T...> &tup, integer_seq<size_t, I...>) {
  string result;
  int ctx[] = {(to_string_impl(result, get<I>(tup)...), 0), 0};
  return (void)ctx, result;
}
template <typename... T> string to_string(const tuple<T...> &tup) { return "{" + to_string(tup, gen_indices<sizeof...(T)>{}) + "}"; }

void custom_assert(bool expression, string message) {
  if (!expression) {
    cerr << "Assert failed: " << message << endl;
    exit(-1);
  }
}

string slice_source(const pair<string, string> &str) {
  for (size_t i = 0; i < code.size(); i++) {
    // cerr<<"[" << code[i] <<  "]" << endl;
    // cerr<<"[" << l_str <<  "]" << endl;
    if (code[i] == str.first) {
      for (size_t j = i + 1; j < code.size(); j++)
        if (code[j] == str.second) {
          string res;
          for (size_t k = i + 1; k < j; k++) {
            res += code[k] + '\n';
          }
          return res;
        }
    }
  }
  return "// NOT FOUND\n";
}

int main() {
  custom_assert(CASE != -1, "CASE not set.");

  ifstream fin, fout;
  stringstream cout;

  string buffer;
  fin.open("gen.cpp");
  while (getline(fin, buffer)) {
    code.push_back(buffer);
  }
  fin.close();

  cout << "// https://vjudge.net/user/memset0" << endl;
  cout << "#include<bits/stdc++.h>" << endl;
  cout << "using namespace std;" << endl;
  for (const auto &line : code) {
    if (string(line.begin(), line.begin() + 10) == "using T = ") {
      cout << line << endl;
      break;
    }
  }

  cout << "T M[]={" << endl;
  for (int i = 1; i <= CASE; i++) {
    cerr << "handle output: #" << i << endl;
    fin.open(to_string(i) + ".in");
    fout.open(to_string(i) + ".out");
    T ans = handle_output(fin, fout);
    fin.close();
    fout.close();

    cout << to_string(ans) << "," << endl;
  }
  cout << "};" << endl;

  cout << "namespace lib {" << endl;
  cout << slice_source({
      "namespace lib {",
      "} // namespace lib",
  });
  cout << "} // namespace lib" << endl;

  cout << "vector<int>H(){" << endl;
  cout << slice_source({
      "vector<int> handle_input(ifstream &cin) {",
      "} // function handle_input",
  });
  cout << "}" << endl;

  cout << "void O(int task,T ans){" << endl;
  cout << slice_source({
      "void generate_output(int task, T ans) {",
      "} // function generate_output",
  });
  cout << "}" << endl;

  cout << "int main(){" << endl;
  cout << "ios::sync_with_stdio(0),cin.tie(0);" << endl;
  cout << "auto V=H();" << endl;
  set<vector<int>> keys;
  size_t key_len = -1;
  for (int i = 1; i <= CASE; i++) {
    fin.open(to_string(i) + ".in");
    auto key = handle_input(fin);
    fin.close();

    if (key_len == (size_t)-1) {
      key_len = key.size();
      cout << "#define I(";
      for (size_t i = 0; i <= key_len; i++) {
        cout << (char)('A' + i);
        if (i != key_len) cout << ",";
      }
      cout << ") if(";
      for (size_t i = 0; i < key_len; i++) {
        if (i) cout << "&&";
        cout << "V[" << to_string(i) << "]==" << (char)('A' + i);
      }
      cout << ")O(" << (char)('A' + key_len) << ",M[" << (char)('A' + key_len) << "-1]"
           << ");";
      cout << endl;
    } else {
      custom_assert(key_len == key.size(), "key size should be equal");
    }
    custom_assert(!keys.count(key), "key of #" + to_string(i) + " is crashed");
    keys.insert(key);
    cout << "I(";
    for (int x : key) {
      cout << x << ",";
    }
    cout << i << ");" << endl;
  }
  cout << "}" << endl;

  string sol = cout.str();
  freopen("sol.cpp", "w", stdout);
  ::cout << sol << endl;
  cerr << "code size: " << sol.length() << endl;
}