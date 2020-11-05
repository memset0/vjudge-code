#include<bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=8e5+10,mod=1e9+7;
int k,n,m,cnt,lim[2][N],num[N];
struct section{int l,r;}seq[2][N];
struct z{
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (ll)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
};
inline z inv(z a){return a.x<2?1:(mod-mod/a.x)*inv(mod/a.x);}
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
struct queue{
	z sum;int h,t;
	queue(){h=1;}
	struct atom{
		int l,r;z a,f,s;
		atom(int l=0,int r=0,z a=0,z f=0):l(l),r(r),a(a),f(f){
			s=f.x==1?a*(r-l+1):a*(fpow(f,r-l+1)-1)*inv(f-1);
		}
	}q[N<<1];
	inline void insert(int l,int r,z a,z f={1}){
		q[++t]=atom(l,r,a,f),sum=sum+q[t].s;
	}
	inline void pop(int lim){//i>lim合法
		while(h<=t&&q[h].r<=lim)sum=sum-q[h++].s;
		if(h<=t&&q[h].l<=lim){//[l,r]->[lim+1,r]
			q[h]=atom(lim+1,q[h].r,q[h].a*fpow(q[h].f,lim-q[h].l+1),q[h].f);
		}
	}
	inline void print(){
		for(int i=h;i<=t;i++)printf("[%d %d %d %d] ",q[i].l,q[i].r,q[i].a,q[i].f);
		puts("");
	}
}q[2];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(k),read(n),read(m),num[++cnt]=1,num[++cnt]=k;
	for(int i=1;i<=n;i++)lim[0][i]=lim[1][i]=0;
	for(int l,r,i=1;i<=n;i++)read(l),read(r),seq[0][i]={l,r},num[++cnt]=l,num[++cnt]=r;
	for(int l,r,i=1;i<=m;i++)read(l),read(r),seq[1][i]={l,r},num[++cnt]=l,num[++cnt]=r;
	std::sort(num+1,num+cnt+1),cnt=std::unique(num+1,num+cnt+1)-num-1;
	for(int c=0;c<2;c++)for(int i=c?m:n;i;i--){
		seq[c][i].r=std::lower_bound(num+1,num+cnt+1,seq[c][i].r)-num;
		lim[c][seq[c][i].r]=std::max(lim[c][seq[c][i].r],seq[c][i].l);
		seq[c][i].l=std::lower_bound(num+1,num+cnt+1,seq[c][i].l)-num;
	}
	for(int i=1;i<=cnt;i++){
		// printf("num[%d] = %d | lim = {%d %d}\n",i,num[i],lim[0][i],lim[1][i]);
		if(i==1){
			for(int c=0;c<2;c++)q[c].insert(1,1,1,1);
		}else{
			if(num[i]-num[i-1]>1){
				z sum[]={q[0].sum,q[1].sum};
				for(int c=0;c<2;c++)q[c].insert(num[i-1]+1,num[i-1]+1,sum[c^1]);
				if(num[i]-num[i-1]>2){
					for(int c=0;c<2;c++)q[c].insert(num[i-1]+2,num[i]-1,sum[0]+sum[1],2);
				}
			}
			z sum[]={q[0].sum,q[1].sum};
			for(int c=0;c<2;c++)q[c].insert(num[i],num[i],sum[c^1]);
		}
		for(int c=0;c<2;c++)q[c].pop(lim[c][i]);
		// printf("Q0 [%d] : ",q[0].sum),q[0].print();
		// printf("Q1 [%d] : ",q[1].sum),q[1].print();
	}
	printf("%d\n",(q[0].sum+q[1].sum).x);
}