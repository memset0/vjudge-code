#include<bits/stdc++.h>
using namespace std;
const int N = 2e6+5;
int ch[N][2],cnt,ncnt;
int fa[N];
int nd1[N], nd2[N];//nd1 : up to down, nd2 : down to up
vector<int> Occ[N];
vector<int> g[N*2+1000010];
inline int ins(string &s){
	int cur=0;
	for(int i=0;i<(int)s.length();i++){
		if(!ch[cur][s[i]-'0']){
			ch[cur][s[i]-'0']=++cnt;
			fa[cnt] = cur;
			nd1[cnt]=++ncnt,nd2[cnt]=++ncnt;
			if(cur){
				g[nd1[cur]].push_back(nd1[cnt]), g[nd2[cnt]].push_back(nd2[cur]);
			}
		}
		cur=ch[cur][s[i]-'0'];
	}
	// cout << s << "::" << cur << endl;
	return cur;
}

string s[500010];
int id[500010];
int nd[500010][2];
int n;
int col[N*2+1000010],ccnt,dfn[N*2+1000010],low[N*2+1000010],stk[N*2+1000010],num,top;
inline void tarjan(int x){
	stk[++top]=x;dfn[x]=low[x]=++num;
	for(auto v:g[x]){
		if(!dfn[v]){
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}else if(!col[v])low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x]){
		++ccnt;
		while(stk[top]!=x)col[stk[top--]]=ccnt;
		col[stk[top--]]=ccnt;
	}
}

int main()
{
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> s[i];
		for(size_t j=0;j<s[i].length();j++){
			if(s[i][j]=='?')id[i] = j;
		}
		nd[i][0] = ++ncnt, nd[i][1] = ++ncnt;
		if(s[i][id[i]]!='?'){
			int ch=s[i][id[i]]-'0';
			g[nd[i][ch^1]].push_back(nd[i][ch]);
		}
		
		s[i][id[i]]='0';
		int X = ins(s[i]);
		g[nd[i][0]].push_back(nd1[X]);
		if(fa[X])g[nd[i][0]].push_back(nd2[fa[X]]);
		if(fa[X])g[nd1[fa[X]]].push_back(nd[i][1]);
		g[nd2[X]].push_back(nd[i][1]);
		Occ[X].push_back(-i);

		s[i][id[i]]='1';
		int Y = ins(s[i]);
		g[nd[i][1]].push_back(nd1[Y]);
		if(fa[Y])g[nd[i][1]].push_back(nd2[fa[Y]]);
		if(fa[Y])g[nd1[fa[Y]]].push_back(nd[i][0]);
		g[nd2[Y]].push_back(nd[i][0]);
		Occ[Y].push_back(i);
	}
  for(int i=0;i<N;i++){
    Occ[i].shrink_to_fit();
  }
	for(int i=1;i<=cnt;i++){
		int sz=Occ[i].size();
		int last=0;
		for(int j=0;j<sz;j++){
			int cur = Occ[i][j]<0?nd[-Occ[i][j]][0]:nd[Occ[i][j]][1];
			if(last)g[cur].push_back(last);
			++ncnt;
			if(last)g[ncnt].push_back(last);
			last=ncnt;
			int con = Occ[i][j]<0?nd[-Occ[i][j]][1]:nd[Occ[i][j]][0];
			g[last].push_back(con);
		}
		last=0;
		for(int j=sz-1;j>=0;j--){
			int cur = Occ[i][j]<0?nd[-Occ[i][j]][0]:nd[Occ[i][j]][1];
			if(last)g[cur].push_back(last);
			++ncnt;
			if(last)g[ncnt].push_back(last);
			last=ncnt;
			int con = Occ[i][j]<0?nd[-Occ[i][j]][1]:nd[Occ[i][j]][0];
			g[last].push_back(con);
		}
	}
	for(int i=1;i<=ncnt;i++){
		if(!dfn[i])tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(col[nd[i][0]]==col[nd[i][1]]){
			puts("NO");
			return 0;
		}else{
			if(col[nd[i][0]]<col[nd[i][1]])s[i][id[i]]='0';
			else s[i][id[i]]='1';
		}
	}
	cout << "YES" << endl;
	for(int i=1;i<=n;i++)cout << s[i] << endl;
}
