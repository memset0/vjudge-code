#include <bits/stdc++.h>
#define maxn 1005
using namespace std;
int bl[maxn];
vector<int> nx[maxn];
int ns[maxn], ncnt = 0;
int main()
{
	int n, m;
	cin>>n>>m;
	for(int i = 0; i < m; i++)
	{
		int u, v;
		cin>>u>>v;
		nx[u].push_back(v), 
		nx[v].push_back(u);
	}
	int nr = 0;
	int tot = 0;
	while(1)
	{
		nr++;
		if(!(nr % 20))
			if(1.0 * clock() / CLOCKS_PER_SEC > 0.3)
				break;
		ncnt = 0;
		for(int i = 1; i <= n; i++)
			if(!bl[i] && nx[i].size()) ns[ncnt++] = i;
		if(!ncnt) break;
		int nd = rand() % ncnt;
		int nid = ns[nd];
		int nfl = 0;
		for(int j = 0; j < nx[nid].size(); j++)
		{
			int v = nx[nid][j];
			if(!bl[v])
			{
				bl[v] = nid, 
				bl[nid] = v;
				nfl = 1;
				tot++;
				break;
			}
		}	
		if(!nfl)
		{
			int v = nx[nid][rand() % nx[nid].size()];
			bl[bl[v]] = 0;
			bl[v] = nid, bl[nid] = v;
		}
	}
	cout<<tot<<endl;
	for(int i = 1; i <= n; i++)
		cout<<bl[i]<<" ";
	return 0;
} 