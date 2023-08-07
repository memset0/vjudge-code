#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int n, m, ans, cnt[N];
bool tag[N], used[N];
vector<int> ins[N],del[N];

int chosen[N],cc[N];
int main() {
#ifdef memset0
  freopen("A0.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  vector<int> a;
  cin >> n, a.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> tmp = a;
  sort(tmp.begin(), tmp.end());
  tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
  m = tmp.size();
  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
    ++cnt[a[i]];
  }
  // for (int i = 0; i < n; i++) cerr << a[i] << " \n"[i + 1 == n];
  vector<int> b;
  for (int l = 0, r; l < n; l = r + 1) {
    r = l;
    while (r + 1 < n && a[r] == a[r + 1]) ++r;
    if (cnt[a[l]] == r - l + 1) {
      tag[a[l]] = true;
    }
    b.push_back(a[l]);
  }
  n = b.size(), swap(a, b);
  // vector<int> t = a;
  // sort(t.begin(), t.end());
  // for (int i = 0; i < n; i++) cerr << t[i] << " \n"[i + 1 == n];
  for (int x = 0; x < n; x++)
    if (!used[x] && tag[a[x]]) {
      int l = x, r = x;
      if (l && !used[l - 1] && !tag[a[l - 1]] && a[l - 1] == a[l] - 1) --l;
      while (r + 1 < n && !used[r + 1] && tag[a[r + 1]] && a[r + 1] == a[r] + 1) ++r;
      if (r + 1 < n && !used[r + 1] && !tag[a[r + 1]] && a[r + 1] == a[r] + 1) ++r;
      for (int i = l; i <= r; i++) used[i] = true;
      // cerr << "find " << l << " " << r << " :: " << a[l] << " " << a[r] << endl;
      ++ans;
    }
  // for (int i = 0; i < n; i++) cerr << a[i] << " \n"[i + 1 == n];
  // for (int i = 0; i < n; i++) cerr << used[i] << " \n"[i + 1 == n];
  // for (int i = 0; i < n; i++) cerr << tag[a[i]] << " \n"[i + 1 == n];
  // cerr << "ans = " << ans << endl;
  int wh=0;
  for (int l = 0, r; l < n; l = r + 1) {
    r = l;
    if (used[l]) continue;
    while (r + 1 < n && !used[r + 1] && a[r + 1] == a[r] + 1) ++r;
    ans += r - l + 1;
    if (l < r) {
      // cerr << "find " << l << " " << r << " :: " << a[l] << " " << a[r] << endl;
      ++wh;
      ins[a[l]].push_back(wh);
      del[a[r]].push_back(wh);
      //printf("Add [%d,%d]\n",a[l],a[r]);
    }
  }
  cerr << "ans = " << ans << endl;
  set<int> st;
  for (int i = 1; i <= m; i++) {
    //printf("i=%d\n",i);
    for(auto x:del[i])st.erase(x);//,printf("del %d\n",x);
    for(auto x:ins[i])st.insert(x);//,printf("ins %d\n",x);
    cc[i]=st.size();
    if(st.size()>=1)
    {
        //printf("begin=%d\n",*st.begin());
        if(!(st.size()==1&&cc[i-1]==1&&chosen[i-1]==*st.begin()))
            --ans,chosen[i]=*st.begin();
    }
  }
  cerr << "ans = " << ans << endl;
  cout << (ans - 1) << endl;
}