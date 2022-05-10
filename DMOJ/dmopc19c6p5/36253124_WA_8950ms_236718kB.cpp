#include<bits/stdc++.h>

const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;

template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}

const int N=1e5+10,L=12,popc[]={0,1,1,2};
int n,m,h[N],w[N],l[N],r[N],a[N],t[N];
long long ans[N];

#define id(i,j) ((i)|((j)<<2))
#define upd(x,y) x=std::min(x,y)
// inline void upd(long long f[4][3],int i,int j,long long y){if(j<3&&y<f[i][j])f[i][j]=y;}

struct BinaryIndexTree{
	long long s[N],r;
	void add(int k,int x){for(;k<=n;k+=k&-k)s[k]+=x;}
	long long ask(int k){for(r=0;k;k-=k&-k)r+=s[k]; return r;}
	long long query(int l,int r){return l<=r?ask(r)-ask(l-1):0;}
};

struct PrefixArray{
	long long s[N];
	inline void init(int *a){for(register int i=1;i<=n;i++)s[i]=s[i-1]+a[i];}
	inline long long query(int l,int r){return s[r]-s[l-1];}
}s1,s2;

struct Matrix{
	long long x[L][L];
	void output(){
		for(int i=0;i<L;i++)
			for(int j=0;j<L;j++){
				printf("%lld%c",x[i][j]>=1e18?-1:x[i][j]," \n"[j+1==L]);
			}
	}

	friend inline Matrix operator*(const Matrix &a,const Matrix &b){
		static Matrix c; memset(c.x,63,sizeof(c.x));
		for(register int i=0;i<L;i++)
			for(register int j=0;j<L;j++){
				upd(c.x[i][j],a.x[i][0]+b.x[0][j]),upd(c.x[i][j],a.x[i][1]+b.x[1][j]),upd(c.x[i][j],a.x[i][2]+b.x[2][j]);
				upd(c.x[i][j],a.x[i][3]+b.x[3][j]),upd(c.x[i][j],a.x[i][4]+b.x[4][j]),upd(c.x[i][j],a.x[i][5]+b.x[5][j]);
				upd(c.x[i][j],a.x[i][6]+b.x[6][j]),upd(c.x[i][j],a.x[i][7]+b.x[7][j]),upd(c.x[i][j],a.x[i][8]+b.x[8][j]);
				upd(c.x[i][j],a.x[i][9]+b.x[9][j]),upd(c.x[i][j],a.x[i][10]+b.x[10][j]),upd(c.x[i][j],a.x[i][11]+b.x[11][j]);
			}
		return c;
	}

	void initMove(int a,int b,int c){
		// x[j][i] f[i]=>g[j]转移系数
		memset(x,63,sizeof(x));
		x[id(0,2)][id(0,0)]=x[id(0,1)][id(1,0)]=x[id(0,2)][id(1,1)]=x[id(0,1)][id(2,0)]=x[id(0,2)][id(2,1)]=x[id(0,0)][id(3,0)]=x[id(0,1)][id(3,1)]=x[id(0,2)][id(3,2)]=0;
		x[id(1,1)][id(0,0)]=x[id(1,2)][id(0,1)]=x[id(1,0)][id(2,0)]=x[id(1,1)][id(2,1)]=x[id(1,2)][id(2,2)]=a;
		x[id(2,1)][id(0,0)]=x[id(2,2)][id(0,1)]=x[id(2,0)][id(1,0)]=x[id(2,1)][id(1,1)]=x[id(2,2)][id(1,2)]=c;
		x[id(3,0)][id(0,0)]=x[id(3,1)][id(0,1)]=x[id(3,2)][id(0,2)]=a+c;
		x[id(3,2)][id(0,0)]=x[id(3,1)][id(1,0)]=x[id(3,2)][id(1,1)]=x[id(3,1)][id(2,0)]=x[id(3,2)][id(2,1)]=x[id(3,0)][id(3,0)]=x[id(3,1)][id(3,1)]=x[id(3,2)][id(3,2)]=b;
	}
};

struct Vector{
	long long x[L];
	void output(){
		for(int i=0;i<4;i++)
			for(int j=0;j<3;j++)if(x[id(i,j)]<1e18){
				printf("dp[%d][%d]=%lld\n",i,j,x[id(i,j)]);
			}
	}

	void initStart(int a){
		memset(x,63,sizeof(x));
		x[0]=0,x[3]=a;
	}

	void cross(const Matrix &a){
		static long long y[L];
		memset(y,63,sizeof(y));
		for(int i=0;i<L;i++){
			for(int j=0;j<L;j++){
				upd(y[j],a.x[j][i]+x[i]);
			}
			// upd(y[0],a.x[0][i]+x[i]),upd(y[1],a.x[1][i]+x[i]),upd(y[2],a.x[2][i]+x[i]),upd(y[3],a.x[3][i]+x[i]);
			// upd(y[4],a.x[4][i]+x[i]),upd(y[5],a.x[5][i]+x[i]),upd(y[6],a.x[6][i]+x[i]),upd(y[7],a.x[7][i]+x[i]);
			// upd(y[8],a.x[8][i]+x[i]),upd(y[9],a.x[9][i]+x[i]),upd(y[10],a.x[10][i]+x[i]),upd(y[11],a.x[11][i]+x[i]);
		}
		memcpy(x,y,L<<3);
	}

	long long calcEnd(){
		long long res=1e18;
		for(int i=0;i<4;i++)for(int j=0;j<3;j++){
			int k=2-popc[i]+j;
			if(k==0||k==2)res=std::min(res,x[id(i,j)]);
		}
		return res;
	}
}res;

struct SegmentTree{
  int cnt;
	struct Node{
		int l,r,mid,lc,rc;
		Matrix x;
	}p[N<<1];

	void build(int u,int l,int r){
		p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
		if(l==r){
			// printf("build %d => %d\n",u,l);
			p[u].x.initMove(w[l]+std::max(h[l]-h[l-1],0)+std::max(h[l]-h[l+1],0),
				std::min(h[l],h[l+1]),w[l]);
			return;
		}
		build(p[u].lc=++cnt,l,p[u].mid);
		build(p[u].rc=++cnt,p[u].mid+1,r);
		p[u].x=p[p[u].rc].x*p[p[u].lc].x;
	}

	void query(int u,int l,int r){
		// printf("query %d %d %d\n",u,l,r);
		if(l==p[u].l&&r==p[u].r){
			// res=p[u].x*res;
			// p[u].x.output();
			res.cross(p[u].x);
			return;
		}
		if(r<=p[u].mid)return query(p[u].lc,l,r);
		if(l>p[u].mid)return query(p[u].rc,l,r);
		query(p[u].lc,l,p[u].mid);
		query(p[u].rc,p[u].mid+1,r);
	}

  SegmentTree() {++cnt;}
}s;

void move(long long f[4][3],long long g[4][3],int a,int b,int c){
	const auto printv=[&](int x,int y,int i,int j,bool a,bool b,bool c){
		if(y>2)return;
		printf("x[id(%d,%d)][id(%d,%d)]=",x,y,i,j);
		if(b){
			putchar('b');
		}else{
			if(a&&c)putchar('a'),putchar('+'),putchar('c');
			else if(a)putchar('a');
			else if(c)putchar('c');
			else putchar('0');
		}
		putchar(';');
		putchar('\n');
	};
	printf("move %d %d %d\n",a,b,c);
	for(int x=0;x<4;x++)
		for(int i=0;i<4;i++)if((i&x)==0)
			for(int j=0;j<3;j++){
				// upd(g,x,2-popc[i|x]+j,f[i][j]+(x&1?a:0)+(x&2?c:0));
				printv(x,2-popc[i|x]+j,i,j,x&1,0,x&2);
			}
	for(int i=0;i<4;i++)
		for(int j=0;j<3;j++){
			// upd(g,3,2-popc[i]+j,f[i][j]+b);
			printv(3,2-popc[i]+j,i,j,0,1,0);
		}
}

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	// freopen("0.out","w",stdout);
	// move(dp[0],dp[1],0,0,0);
#else
	// freopen("huffman.in","r",stdin);
	// freopen("huffman.out","w",stdout);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(h[i]);
	for(int i=1;i<=n;i++)read(w[i]);
	for(int i=1;i<=m;i++)read(l[i]),read(r[i]);
	if(n==1){
		int ans=(h[1]+w[1])<<1;
		for(int i=1;i<=m;i++)printf("%d\n",ans);
		return 0;
	}
	for(int i=1;i<=n;i++)t[i]=(h[i]+w[i])<<1;
	s1.init(t);
	for(int i=1;i<=m;i++)ans[i]+=s1.query(l[i],r[i]);
	for(int i=1;i<n;i++)t[i]=std::min(h[i],h[i+1]);
	s2.init(t);
	for(int i=1;i<=m;i++)if(l[i]<r[i])ans[i]-=s2.query(l[i],r[i]-1);
	s.build(1,1,n);
	for(int i=1,l,r;i<=m;i++)if((l=::l[i])<(r=::r[i])){
		// printf(">> %d %d\n",l,r);
		res.initStart(std::min(h[l],h[l+1]));
		if(l+1<=r-1)s.query(1,l+1,r-1);
		// res.output();
		// printf("> %lld\n",res.calcEnd());
		ans[i]+=res.calcEnd();
	}
	for(int i=1;i<=m;i++)print(ans[i],'\n');
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}