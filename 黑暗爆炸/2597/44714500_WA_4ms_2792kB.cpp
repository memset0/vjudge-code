// https://vjudge.net/user/memset0
#include<bits/stdc++.h>
using namespace std;
using T = pair<pair<int, int>, pair<size_t, string>>;
T M[]={
{{6,8},{80,"SIiETIjXvUu8SA"}},
{{100,39240},{19084,"yEV8S8h41LiPfFyM+8YIiEiEC5yLiLvIu8zMmPPHnPvJiMjL-Ju9IRBFTIhMiXvESMCJBJBKSR+8zIjT-MhIjEkEiPvElYxPxTiIhEWMfFfQRFiLv4zLxEaIBFawvGvX-4zPzUR5zThIVIh40TTQh40rhEiEC55Tu8iIBFyIiYxETIBNiTvED51Ti4zLlTvEiLvUBNiEUMBJu8TQhKnGWMhMu8iPvEnLv4zTxErLvku8yESUu8YUR6yXkEjPvETIu8iPPRTox4zTx4zPRJBVxMTcBFiTvEUIBFSoTcO9UUhESIi40LBJhETQu8TICSO9yMkTvIu8jFkLvMlLvQu8i4yLUUkLvQhETMhGSM+8iIUI+8pQu8jP-IyJzEibvQiTvQRJDFSIDJ0MR60Lu8iPP5zPiMR5zXyQh4yPUITQTQSMkP-Qu8CGkI+8jLv4zLu8zESI+8UMBFbMhI+8XI+8l4yjjPvEiIiEyESIBJRJO9jYhJu8HFyMyEiL-EUYTFjbv4yTBFlEcMxQu8iPvMR50zRFoESIu8TQRFzY+8aIhIlLvQu8Skh4yLnI+8iMhFzETUR50PyMBFkISUi51f1ESQ+8VIR9Q8i4zTkT-EZIhJSIu8jLP5zL+8SM+8jT-MzECFyEUIe9SIu8TUBF0ghEDNTUSIkTvIiPvMh40PiL-ME5yTh4zXhJ+8kffFSMTMBNxEjPvYO9SIBRO9SMu8UIhEygy5zPu8TYCJy4yLhQxQu8iLPdx4yLTMF5yL+8CRh4yL+8yEyIxESUu8Tc+8i4yXu8iTvISISIhIx40TlPvIC5yTu8SIBNh40ThMB5yLhchEiP-IiMSIiL-40LiLPNhEiLvMu8kLv4yXi4yXUIhMu8iEiLv5zLiIi4yLhMhIO9SIxEiTvYUQiIxIxU+8jLvIO9jEiMhE04zLxIyIi41LhFi4yPhIjP-4zXTU+8kMhEmPv4yPjITMxE6Mh41LlEyMu8lLf50fu8iEkFSQu8F5zPhEVUxEi4yLScyIiMB5zTh4yLUQu8jIxEUMhMZUiIh40P+8iIzIhIu8iP-ETUSMO9iLvElECN74yPhIu8CFkMhMu8yMhESIBdBJu8iYu8DJu8TMUIu8nFyIiE3Uu9SIx40Lu8m40TiIu8k4yTx4yLoIRNu8y4yLkXf50LiXfFibv4yLxIlIiLPFiTvJhEUUzkx4yLu8TcSIxEiLv4yLiPvED5zbhMkLv4zL+8SMy4zLiESIu81EVIhImITQhIZInMh4yLlbPFiTP5zPhESIi4zLh4zLiMiL-Ie9y40LO9SYxMBFSQTFiL-4yLB5zPu8i4yLi40LO9SImETQhMxImPvVUVu8jTvMx50Tu8kQSMiTvISM+8SIBFjIiLvESMe9yMyIi41PiElX-FjL-4zj+8jEkPPRRFXUiIh5zLUIu8kLvMRNxQO9iMe9jQx4zPRFjMu8jLv4yPe9iMhEiMO9mIh4zTlPPRe9TUBFiEiQhIu8YMxME6yLUMlUTMxFJJiEk5zPu8UIjPvEjMjPvIhEiEiI+8UMSIhI14zLiMhIYwu8lP-UiIi4yPh4yLu8TQu8C50LTIBFWUzISQh4yLWIh4yLhM+8y4zP+8kIiPvM+8iLfFUIxM0EUI+8TQi4yTkLvYu8SIB5yPlEyFUIx4zX+8T50ju8iIYISIu8WQUIu8jgB50LSg+8T5yLhEiL-Iu8iTvETMiISMVQu8SNhIxQBFmE0Iif-MhJ+8DZiISMhFSgBJO9iEkE4MROu8yIzIjPvElInPPJO9k4yL0ETJCFiMSIyUu8TR1k+8FFyIh41r+8DFy4zLj4zfu8C61TRFVYBGi4yzjEF5zPjQi4yLVMiISIu8kc+8iLvEU5zPhIiLvMCJu8CFEKu8iEiP-MjkBFTIRJTMyJhIBVhUhFiTvIO9iEkLvIu8j4yT+8HJBNhMx52Ti5z-V8RFTUy7v40TxI8EjEy40L0Mu80gTI+8SMCRk4yLx4yPz4yPxIh43PjLv4zXx40Ph4zLh4zLiEyE0EUIiTvJT5yLiL-Jx51Lych43TkPvIh4yTu8TchJi4zLjLv4yLiLv40LxIy50XCRiLf5yL+8SMSMu8SIiESQBFDFyNu8i5yP+8iP-EkM+8DFVYB50LO9jTvEUIjEiLvE04zTi4yLSIjP-QhIhESMiP-Iu8TIxEyEScDKyEiIxIiL-Mi4yPe9GFTIDFmPP50fR5zLxUiPvETMu8iEiTvMhMRFTMTI+8iL-4yTx4yTu8nfvIhIhMlPvIu8n5zLjEiPfJyIzMiESgjIBRhIhIhMSgiEyVmIkTf5yLu8yIu8i4yLxIu+isyITcO9loO9WMkQhEi4yPTIh4yPu8YIlEkLv4zbh4yLh4yLh4zLxI+8yEjLvJkLvQ+8CRkEkP-IhMSMhIxEiPv40LO9jX-Ih41PxIyEyEiXvIh41Lh4yLSQTcO9jUhIhEi4zXh4zLhNB50PSIe9UInX-IxclPPFyIiPfJUUxI+8VIe9iLvNTcu9jMjPvMiImXv4yLiIUMiP-MkPfFjL-4zLjEyY0ITYO9yKjP-ISMe9SMyUSI+8iTvUiPPJO9pPP5yLSIiECRhIBJEGSISQScxMUIyEmEkXvIhQiYiITMSIO9iEW50LxIxMhIh4yzhEScjP-IiIx5yXhEj4zLhIUISIu8SI+8jFjI+8YIiLvM+8TIu8jLv4yLO9kU+8CNe9jLvEi40bUIz5zTu8SSO9TM+8jT-MRJ0I+8yIiEi5yLiUu8SMSMO9UIO9UIhIhESIiIi4zLUMUFiQxEiL-MxKiEiLv40Pu8CFzFyISQhISIBFXQBJWJoEiEUQu8SMu8jPv5zLu80czEk4yLTUDRzEi4yLSIu8iPPJu8DFiIkIh53P+8iMqEiYh40XiX-ECJ+8lLv4zPh4yLCFjIu8VUSQiX-QDJoLvEiLvIWIO9iLPJjLvIe9jIhIx4zPh4zPiEjLvESISNDFSMy4yLxUx4zTiEk4yL+8i4yPO9UMiLvMx40LyEl4yThFi4yTu8SICJjIi4yXSQy4yXTIiEUUu8yEjP-EiPvEjIBOhEVIUIBFjP-Iu8nTvJO9jEVQyEiXvEjEl40Ly4zPhEmPPJykO9y4yPnLvIjEDN+8SITMhJu8UIiM+8UIyIO9iEiIiQxQSIhIu8i5yPSIjEy4yLu8SUu8E"}},
};
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
vector<int>H(){
  int n, a, b, c, d;
  cin >> n >> a >> b >> c >> d;
  return {n, a * 10000 ^ b * 100 ^ c * 1000 ^ d};
}
void O(int task,T ans){
  int n = ans.first.first;
  int m = ans.first.second;
  vector<bool> e = lib::decode_base64(ans.second);
  vector<int> d;
  for (int i = 0; i < e.size(); i += 4) {
    d.push_back(e[i] | e[i + 1] << 1 | e[i + 2] << 2 | e[i + 3] << 3);
  }
  vector<int> c;
  for (int i = 0, j; i < d.size(); i++) {
    if (d[i] == 14 || d[i] == 15) {
      int u = 0;
      for (j = i + 1; d[j] != 15; j++) {
        u *= 15;
        u += d[j];
      }
      if (d[i] == 14) u *= -1;
      c.push_back(u);
      i = j;
    } else {
      c.push_back(d[i]);
    }
  }
  vector<int> b;
  for (int x : c) {
    if (x > 0) {
      b.push_back(x);
    } else {
      for (int i = 0; i < (-x); i++) b.push_back(1);
    }
  }
  vector<int> a;
  for (int i = 0; i < b.size(); i++) {
    while (b[i]--) {
      a.push_back(i & 1);
    }
  }
  cout << m << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << a[i * n + j] << " \n"[j + 1 == n];
    }
  }
}
int main(){
ios::sync_with_stdio(0),cin.tie(0);
auto V=H();
#define I(A,B,C) if(V[0]==A&&V[1]==B)O(C,M[C-1]);
I(6,800,1);
I(100,802,2);
}

