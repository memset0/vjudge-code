#include <bits/stdc++.h>
using namespace std;

const int CASE = 20;
using T = vector<string>;

vector<int> handle_input(ifstream &cin) {
  std::mt19937 rng;
  vector<int> a(10);
  int x;
  for (int i = 0; i < 10; i++) {
    for (int i = 0; i < a.size(); i++) {
      cin >> x;
      a[i] ^= x;
    }
  }
  return a;
} // function handle_input

T handle_output(ifstream &fin, ifstream &fout) {
  string s;
  vector<string> a;
  while (getline(fout, s)) {
    if (s[0] == '1') {
      a.push_back("");
    } else {
      while (s[s.length() - 1] == s[s.length() - 2]) s.pop_back();
      a.push_back(string(s.begin() + 2, s.end()));
    }
  }
  return a;
} // function handle_output

void generate_output(int task, T ans) {
  for (string s : ans) {
    if (s.length()) {
      while (s.length() < 12) {
        s.push_back(s.back());
      }
      cout << "0." + s << endl;
    } else {
      cout << "1.000000000000" << endl;
    }
  }
} // function generate_output

// ==============================================================

vector<string> code;

string to_string(const string &s);
template <class K, class V> string to_string(const pair<K, V> &it);
template <class T> string to_string(const vector<T> &vec);

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

void custom_assert(bool expression, string message) {
  if (!expression) {
    cerr << "Assert failed: " << message << endl;
    exit(-1);
  }
}

string slice_source(const string &l_str, const string &r_str) {
  for (size_t i = 0; i < code.size(); i++) {
    // cerr<<"[" << code[i] <<  "]" << endl;
    // cerr<<"[" << l_str <<  "]" << endl;
    if (code[i] == l_str) {
      for (size_t j = i + 1; j < code.size(); j++)
        if (code[j] == r_str) {
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
    fin.open(to_string(i) + ".in");
    fout.open(to_string(i) + ".out");
    T ans = handle_output(fin, fout);
    fin.close();
    fout.close();

    cout << to_string(ans) << "," << endl;
  }
  cout << "};" << endl;

  cout << "vector<int>H(){" << endl;
  cout << slice_source("vector<int> handle_input(ifstream &cin) {", "} // function handle_input");
  cout << "}" << endl;

  cout << "void O(int task,T ans){" << endl;
  cout << slice_source("void generate_output(int task, T ans) {", "} // function generate_output");
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