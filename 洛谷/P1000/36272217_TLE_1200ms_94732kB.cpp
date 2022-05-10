#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=4e6+10,L=21;
ll f[N];
char s[N];
std::vector<int> S,T,F[N];
int n,k,x,a[N],b[N],v_fa[N],dep[N];
std::vector<std::pair<int,int>> P,Q;
// === BIT ===
ll sum[N];
inline void add(int i,int v){
	for(i=std::min(i,k);i<=k;i+=i&-i)sum[i]+=v;
}
inline ll ask(int i){
	ll res=0;
	for(i=std::min(i,k);i;i-=i&-i)res+=s[i];
	return res;
}
// === SAM ===
int nod=1,lst=1,fa[N],ch[N][26],len[N];
void append(int c){
	int u=++nod,f=lst;lst=u,len[u]=len[f]+1;
	while(f&&!ch[f][c])ch[f][c]=u,f=fa[f]; if(!f){fa[u]=1;return;}
	int s=ch[f][c]; if(len[s]==len[f]+1){fa[u]=s;return;}
	int p=++nod;fa[p]=fa[s],fa[s]=fa[u]=p,len[p]=len[f]+1;
	for(register int i=0;i<26;i++)ch[p][i]=ch[s][i];
	while(f&&ch[f][c]==s)ch[f][c]=p,f=fa[f];
}
/// === LCA ===
inline int lca(int u,int v){
	if(dep[u]>dep[v])std::swap(u,v);
	for(int i=L-1;i>=0;i--)if(dep[ch[v][i]]>=dep[u])v=ch[v][i]; if(u==v)return u;
	for(int i=L-1;i>=0;i--)if(ch[u][i]!=ch[v][i])u=ch[u][i],v=ch[v][i]; return ch[u][0];
}
// === VIR-TREE ===
std::vector<int> build(const std::vector<int> &T){
	static int top,stk[N]; stk[top=1]=1;
	static std::vector<int> S; S.resize(1),S[0]=1;
	for(int i=0;i<T.size();i++){
		int u=T[i],lca=::lca(u,stk[top]);
		printf("> %d %d %d\n",u,stk[top],lca);
		if(lca!=stk[top]){
			while(top>=2&&dep[stk[top-1]]>=dep[lca])v_fa[stk[top]]=stk[top-1],top--;
			if(lca!=stk[top])v_fa[stk[top--]]=lca,stk[++top]=lca,S.push_back(lca);
		}
		stk[++top]=u,S.push_back(u);
	}
	return S;
}
// === LI-CHAO SEG ===
ll LL[N<<2],RR[N<<2],MM[N<<2];
struct line{
	int k; ll b;
	inline ll operator()(int x)const{return (ll)k*x+b;}
}p[N<<2];
void modify(int u,line x,int l,int r){
	int mid=(l+r)>>1,L=x(l),R=x(r),M=x(mid);
	if(L<=LL[u]&&R<=RR[u])return;
	if(L>=LL[u]&&R>=RR[u]){p[u]=x;return;}
	if(M>MM[u])std::swap(x,p[u]),LL[u]=L,RR[u]=R,MM[u]=M;
	if(l!=r){
		if(L>LL[u])modify(u<<1,x,l,mid);
		else modify(u<<1|1,x,mid+1,r);
	}
}
ll query(int u,int k,int l,int r){
	if(l==r)return p[u](k);
	int mid=(l+r)>>1;
	if(k<=mid)return std::max(query(u<<1,k,l,mid),p[u](k));
	return std::max(query(u<<1|1,k,mid+1,r),p[u](k));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(k),read(x);
	std::cerr<<n<<" "<<k<<" "<<x<<std::endl;
	for(int i=1;i<=k;i++)read(a[i]);
	for(int i=1;i<=k;i++)read(b[i]);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1),F[i].resize(k+1);
		for(int j=1;j<=k;j++)append(s[j]),F[i][j]=nod;
		append('#');
		for(int i=1;i<=nod;i++)print(fa[i]," \n"[i==nod]);
	}
	for(int i=1;i<=nod;i++)dep[i]=dep[fa[i]]+1,ch[i][0]=fa[i];
	for(int i=1;i<L;i++)for(int j=1;j<=nod;j++)ch[j][i]=ch[ch[j][i-1]][i-1];
	for(int i=1;i<=nod;i++)print(fa[i]," \n"[i==nod]);
	for(int i=1;i<=nod;i++)print(ch[i][0]," \n"[i==nod]);
	for(int i=1;i<=nod;i++)print(ch[i][1]," \n"[i==nod]);
	for(int i=1;i<=(n<<2);i++)p[i].b=-1e18;
	for(int c=1;c<=k;c++){
		printf("=== %d ===\n",c);
		S.clear(),P.clear(),Q.clear();
		for(int i=1;i<=n;i++)S.push_back(F[i][c]);
		printf("S => ");for(int x:S)print(x,' ');puts("");
		S=build(S); 
		printf("S => ");for(int x:S)print(x,' ');puts("");
		for(int i=1;i<=n;i++)add(len[v_fa[S[i]]]+1,1),add(len[S[i]]+1,-1);
		for(int i=0;i<c;i++)modify(1,(line){a[i+1],f[i]+(ll)x*ask(c-i)+b[i+1]-(ll)a[i+1]*i},1,k);
		f[c]=query(1,c,1,n);
		printf(">> %lld\n",f[c]);
		for(int i=1;i<=n;i++)add(len[v_fa[S[i]]]+1,-1),add(len[S[i]]+1,1);
	}
	print(f[n],'\n');
}