#include<bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-48,c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+48);
}
const int N=30,M=5e5,mod=998244353;
int n,m,q,min=M,max=0;
char a[N],b[N];
ll k,base,f[N][N],g[N][N];
struct z{
	int x;
	inline z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (ll)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}res,ans[M];
struct atom{
	int cnt,lft; ll sta; z res; // cnt 已经放的小球数 sta 状压的向量 res 方案数
	inline int hash()const{return ((sta%200425007)+cnt*131131+lft*113311)%19260817;}
	inline bool operator==(const atom &other)const{return cnt==other.cnt&&lft==other.lft&&sta==other.sta;}
	inline int get(int k)const{return (sta>>(6*k))&63;}
	inline ll set(int k,ll x)const{return (sta&(LLONG_MAX^(63ll<<(6*k))))|(x<<(6*k));}
};
struct hash_map{
	int lst,tot,top,hed[19260817],nxt[M],stk[M];
	atom val[M];
	inline void insert(const atom &data){
		int key=data.hash();
		// printf("insert %d %d %lld %d : %d\n",data.cnt,data.lft,data.sta,data.res.x,key);
		for(int i=hed[key];~i;i=nxt[i])if(val[i]==data){
			val[i].res=val[i].res+data.res;
			return;
		}
		if(!~hed[key])stk[top++]=key;
		nxt[tot]=hed[key],val[tot]=data,hed[key]=tot++;
	}
	inline void clear(){while(top--)hed[stk[top]]=-1; tot=top=0;}
	inline int next(int cur){
		if(~nxt[cur])return nxt[cur];
		for(lst++;lst<top;lst++)if(~hed[stk[lst]])return hed[stk[lst]];
		return -1;
	}
	inline int start(){
		for(lst=0;lst<top;lst++)if(~hed[stk[lst]])return hed[stk[lst]];
		return -1;
	}
	inline hash_map(){memset(hed,-1,sizeof(hed)),this->clear();}
}hash[2],*cur(&hash[0]),*nxt(&hash[1]);
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m),read(k),scanf("%s%s",a,b),read(q),g[0][0]=k;
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)g[i][j+1]+=g[i][j]>>1,g[i+1][j]+=g[i][j]>>1,f[i][j]=g[i][j]&1;
	for(int i=0;i<n;i++)base+=(a[i]=='1')*g[i][m];
	for(int i=0;i<m;i++)base+=(b[i]=='1')*g[n][i];
	// printf("%d %d %lld %lld\n",n,m,k,base);
	cur->insert((atom){0,0,0,1});
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			// printf("=== %d %d ===\n",i,j);
			for(int x=cur->start();~x;x=cur->next(x)){
				atom *data=&cur->val[x];
				int tot=data->lft+data->get(j)+f[i][j];
				// printf("%d %d %lld %d : %d\n",data->cnt,data->lft,data->sta,data->res.x,tot);
				nxt->insert((atom){data->cnt,tot>>1,data->set(j,(tot+1)>>1),data->res});
				nxt->insert((atom){data->cnt,(tot+1)>>1,data->set(j,tot>>1),data->res});
			}
			cur->clear(),std::swap(cur,nxt);
		}
		// printf("=== %d ===\n",i);
		for(int x=cur->start();~x;x=cur->next(x)){
			atom *data=&cur->val[x];
			// printf("%d %d %lld %d\n",data->cnt,data->lft,data->sta,data->res.x);
			nxt->insert((atom){data->cnt+(a[i]=='1')*data->lft,0,data->sta,data->res});
		}
		cur->clear(),std::swap(cur,nxt);
	}
	for(int x=cur->start();~x;x=cur->next(x)){
		atom *data=&cur->val[x];
		int tot=data->cnt;
		for(int i=0;i<m;i++)tot+=(b[i]=='1')*data->get(i);
		// printf("update ans %d %d\n",tot,data->res.x);
		ans[tot]=ans[tot]+data->res,min=std::min(min,tot),max=std::max(max,tot);
	}
	// exit(0);
	for(ll l,r;q--;){
		read(l),read(r),res=0;
		if(r<base+min||l>base+max){puts("0");continue;}
		for(int i=std::max(l-base,(ll)min),e=std::min(r-base,(ll)max);i<=e;i++)res=res+ans[i];
		// printf("%lld %lld => %lld %lld\n",l,r,std::max(l-base,(ll)min),std::min(r-base,(ll)max));
		print(res.x),putchar('\n');
	}
}