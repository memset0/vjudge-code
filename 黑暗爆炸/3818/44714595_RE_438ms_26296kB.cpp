//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#ifndef LOCAL
#define cerr if(0)cout
#endif
typedef long long ll;
const int max_nfa = 55;
const int max_len = 55;
const int max_nfanode = 65535;
int vis[max_nfanode][max_len], visT;
struct NFA
{
	int S, T;
	vector<vector<pair<pair<char,char>, unsigned short> > > go;
	NFA()
	{
		go.clear();
		S = T = 0;
		go.resize(1);
	}
	bool dfs(int x, char s[], int i, int l)
	{
		if (x==T&&i==l) return true;
		if (vis[x][i]==visT) return false;
		vis[x][i] = visT;
		for (auto e : go[x]) if (e.FF.FF==0&&dfs(e.SS, s, i, l)) return true;
		for (auto e : go[x]) if (e.FF.FF<=s[i]&&s[i]<=e.FF.SS&&dfs(e.SS, s, i+1, l)) return true;
		return false;
	}
	bool match(char s[], int l)
	{
		assert(go.size()<max_nfanode);
		visT++;
		return dfs(S, s, 0, l);
	}
	NFA opt() const
	{
		NFA ret = (*this);
		ret.go[S].PB(MP(MP(0, 0), T));
		return ret;
	}
	NFA opt_inf() const
	{
		NFA ret = (*this);
		ret.go[S].PB(MP(MP(0, 0), T));
		ret.go[T].PB(MP(MP(0, 0), S));
		return ret;
	}
}A[max_nfa];
int nfa_tot;
string nfa_name[max_nfa];
map<string, int> nfa_id;
NFA operator | (const NFA &a, const NFA &b)
{
	NFA ret;
	ret.S = 0; ret.T = a.T+b.T; ret.go.resize(ret.T+1);
	for (int i=0; i<=a.T; i++) ret.go[i] = a.go[i];
	ret.go[a.T].PB(MP(MP(0, 0), ret.T));
	for (int i=0; i<=b.T; i++)
	{
		int id = i==0?0:i+a.T;
		for (auto e : b.go[i])
		{
			ret.go[id].PB(MP(e.FF, e.SS==0?0:e.SS+a.T));
		}
	}
	return ret;
}
NFA operator + (const NFA &a, const NFA &b)
{
	NFA ret;
	ret.S = 0; ret.T = a.T+b.T; ret.go.resize(ret.T+1);
	for (int i=0; i<=a.T; i++) ret.go[i] = a.go[i];
	for (int i=0; i<=b.T; i++)
	{
		int id = i+a.T;
		for (auto e : b.go[i])
		{
			ret.go[id].PB(MP(e.FF, e.SS+a.T));
		}
	}
	return ret;
}

NFA make_nfa(char ls, char rs)
{
	NFA ret;
	ret.go.resize(2);
	ret.S = 0; ret.T = 1;
	ret.go[0].PB(MP(MP(ls, rs), 1));
	return ret;
}

int get_bracket_value(char c)
{
	if (c=='('||c=='['||c=='{') return 1;
	if (c==')'||c==']'||c=='}') return -1;
	return 0;
}
bool matchable_char(char c)
{
	if (c>='0'&&c<='9') return true;
	if (c>='a'&&c<='z') return true;
	if (c>='A'&&c<='Z') return true;
	return false;
}
pair<int,int> get_seg(char s[], int l)
{
	int r0=0, r1=0; bool f = false;
	for (int i=0; i<l; i++)
	{
		if (s[i]==',') f = true;
		else if (!f) r0 = r0*10+s[i]-'0';
		else r1 = r1*10+s[i]-'0';
	}
	if (s[l-1]==',') r1 = -1;
	return MP(r0, r1);
}
NFA parse(char s[], int l)
{
	int cnt[max_len] = {};
	for (int i=0; i<l; i++) cnt[i] = (i==0?0:cnt[i-1])+get_bracket_value(s[i]);
	for (int i=0; i<l; i++) if (cnt[i]==0&&s[i]=='|') return parse(s, i)|parse(s+i+1, l-(i+1));
	for (int i=l-1; i>0; i--)
	{
		if (cnt[i]==0&&matchable_char(s[i])) return parse(s, i)+parse(s+i, l-i);
		if (cnt[i]==1&&(s[i]=='('||s[i]=='[')) return parse(s, i)+parse(s+i, l-i);
	}
	if (s[l-1]=='}')
	{
		pair<int,int> seg = MP(-1, -1); NFA cur;
		for (int i=l-1; i>=0; i--) if (s[i]=='{')
		{
			seg = get_seg(s+i+1, l-1-(i+1));
			cur = parse(s, i);
			break;
		}
		assert(seg.FF!=-1);
		NFA ret;
		for (int i=0; i<seg.FF; i++) ret = ret+cur;
		if (seg.SS==-1) ret = ret+cur.opt_inf();
		else for (int i=seg.FF; i<seg.SS; i++) ret = ret+cur.opt();
		return ret;
	}
	if (s[0]=='(') return parse(s+1, l-2);
	if (s[0]=='[')
	{
		assert(l==5);
		return make_nfa(s[1], s[3]);
	}
	assert(l==1&&matchable_char(s[0]));
	return make_nfa(s[0], s[0]);
}

const int max_node = 200111;
int node_tot;
map<string,int> go[max_node];
map<int, int> go_nfa[max_node];
string act[max_node];
int node_add_son(int p, char s[], int l)
{
	if (s[0]==':')
	{
		string name;
		for (int i=1; i<l; i++) name.PB(s[i]);
		int &id = nfa_id[name];
		if (id==0)
		{
			id = ++nfa_tot;
			nfa_name[id] = name;
		}
		int &ret = go_nfa[p][id];
		if (ret==0) ret = ++node_tot;
		return ret;
	}
	else
	{
		string name;
		for (int i=0; i<l; i++) name.PB(s[i]);
		int &ret = go[p][name];
		if (ret==0) ret = ++node_tot;
		return ret;
	}
}
void add_path()
{
	static char s[1000111];
	scanf("%s", s);
	int l = strlen(s);
	int lst = 1;
	int p = 1;
	for (int i=1; i<=l; i++)
	{
		if (s[i]=='/'||i==l)
		{
			p = node_add_son(p, s+lst, i-lst);
			lst = i+1;
		}
	}
	scanf("%s", s);
	act[p] = string(s);
	assert(node_tot<max_node);
}
void add_nfa()
{
	char s[55];
	scanf("%s", s);
	int id = nfa_id[string(s)];
	assert(id>0);
	scanf("%s", s);
	A[id] = parse(s, strlen(s));
}
map<string, vector<string> > para;
int node_go_next(int p, char s[], int l)
{
	string cur;
	for (int i=0; i<l; i++) cur.PB(s[i]);
	if (go[p].find(cur)!=go[p].end()) return go[p][cur];
	for (auto x : go_nfa[p]) if (A[x.FF].match(s, l))
	{
		para[nfa_name[x.FF]].PB(cur);
		return x.SS;
	}
	return 0;
}
void query()
{
	static char s[1000111];
	scanf("%s", s);
	int l = strlen(s);
	int lst = 1;
	int p = 1;
	para.clear();
	for (int i=1; i<=l; i++)
	{
		if (s[i]=='/'||s[i]=='?'||i==l)
		{
			p = node_go_next(p, s+lst, i-lst);
			if (!p) break;
			lst = i+1;
			if (s[i]=='?') break;
		}
	}
	if (!p)
	{
		puts("404 Not Found");
		return;
	}
	for (int i=lst; i<=l; i++)
	{
		if (s[i]=='&'||i==l)
		{
			string s1, s2; bool f = 0;
			for (int j=lst; j<i; j++)
			{
				if (s[j]=='=') f = 1;
				else if (!f) s1.PB(s[j]);
				else s2.PB(s[j]);
			}
			para[s1].PB(s2);
			lst = i+1;
		}
	}
	
	printf("Request matches action \"%s\" with parameters {", act[p].c_str());
	bool fb = true;
	for (auto x : para)
	{
		if (fb) fb = false; else putchar(',');
		printf("\"%s\":", x.FF.c_str());
		vector<string> &v = x.SS;
		if (v.size()==1) printf("\"%s\"", v[0].c_str());
		else
		{
			printf("[");
			for (int i=0; i<v.size(); i++)
			{
				printf("\"%s\"%c", v[i].c_str(), i+1==v.size()?']':',');
			}
		}
	}
	puts("}");
}

void init()
{
	nfa_id.clear();
	for (int i=1; i<=nfa_tot; i++) A[i] = NFA();
	nfa_tot = 0;
	for (int i=1; i<=node_tot; i++)
	{
		go[i].clear();
		go_nfa[i].clear();
	}
	node_tot = 1;
}

void solve()
{
	int n;
	scanf("%d", &n);
	for (int i=1; i<=n; i++) add_path();
	for (int i=1; i<=nfa_tot; i++) add_nfa();
	int q;
	scanf("%d", &q);
	for (int i=1; i<=q; i++) query();
}
int main()
{
	int Tn;
	scanf("%d", &Tn);
	int tn = 0;
	while (Tn--)
	{
		printf("Case #%d:\n", ++tn);
		init();
		solve();
	}
	return 0;
}
