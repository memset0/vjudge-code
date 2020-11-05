#include <bits/stdc++.h>

#define llu unsigned long long
#define ll long long int
#define M (L+R)/2

using namespace std;
typedef pair<int, int> pi;

int const PRIME = 998244353;
int const SIZE = 1000010;
// array<vector<int>, SIZE> mat, A, B;
// int freq[SIZE];

int bit[SIZE], last[SIZE], out[SIZE], arr[SIZE], mx[SIZE], n;
vector<int> v[SIZE];
vector<pair<int, int>> S[SIZE];

void update(int i, int val) {
	while (i <= n) {
		bit[i] = max(bit[i], val);
		i = i + (i &(-i));
	}
}

int solve(int i) {
	int res = 0;
	while (i > 0) {
		res = max(res, bit[i]);
		i = i - (i&(-i));
	}
	return res;
}
	
void update_DAG(int cur, int val) {
	if (val > mx[cur]) {
		for (auto x: v[cur]) 
			update_DAG(x, val+1);
		mx[cur] = val;
		update(cur, val);
	}
}

void get_gold(int n, int g[], int chef[], 
	          int chefu[]) {
	double cf=0, cfu=0;
	for (int i = 0; i < n; ++i) {
		cf += ((double)g[i]/(chefu[i]+chef[i]))*chefu[i];
		cfu += ((double)g[i]/(chefu[i]+chef[i]))*chef[i];
	}
	printf("%6f %6f\n", cf, cfu);
}

int main(int argc, char const *argv[])
{
	int t;
	t=1;
	cin>> t; 
	while (t--) {
		int K, l, x, R, m, N, r, res, prev, type, X, Y, p, e, u;
		cin>> n>> m;
//		int g[n], chef[n], chefu[n];
		for (int i = 0; i <= n; ++i) {
			mx[i] = last[i] = bit[i] = 0;
			v[i].clear();
			S[i].clear();
		}
		for (int i = 1; i <= n; ++i) {
			cin>> arr[i];
			last[arr[i]] = i;
			prev = 0;
			for (int j = arr[i]-1; j >= 1; --j) {
				if (last[j] > prev) {
					prev = last[j];
					v[last[j]].push_back(i);
				} 
			}
		}
		for (int i = 0; i < m; ++i) {
			cin>> l>> r;
			S[l].push_back({r, i});
		}
		for (int i = n; i >= 1; --i) {
			update_DAG(i, 1);
			for (int j = 0; j < S[i].size(); ++j) 
				out[S[i][j].second] = solve(S[i][j].first);
		}
		for (int i = 0; i < m; ++i)
			printf("%d\n", out[i]);
		//cout<<endl;
	}
	return 0;
}

