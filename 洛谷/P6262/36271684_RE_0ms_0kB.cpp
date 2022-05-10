// 咕咕咕


#include<bits/stdc++.h>
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

const int N=6e4+10,mod=998244353;
int n,m;

struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}D,p,q,a,b,A,B,ans,fac[N],ifac[N];
inline z C(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}

inline z cipolla(z x){
	z k,r;
	const auto merge=[&](std::pair<z,z> a,std::pair<z,z> b){
		return std::make_pair(a.first*b.first+a.second*b.second*r,
			a.second*b.first+a.first*b.second);
	};
	do k=rand()%mod,r=k*k-x;
	while(fpow(r,(mod-1)>>1).x!=mod-1);
	std::pair<z,z> s(1,0),a(k,1);
	for(int b=(mod+1)>>1;b;b>>=1,a=merge(a,a))
		if(b&1)s=merge(s,a);
	return std::min(s.first.x,s.second.x);
}

struct vet:std::vector<z>{
	using std::vector<z>::vector;
	inline void input(int l){
		resize(l);
		for(int i=0;i<size();i++)read(this->operator[](i).x);
	}
	inline void output(){
		for(int i=0;i<size();i++){
			print(this->operator[](i).x);
			if(i+1!=size())putchar(' ');
		}
		putchar('\n');
	}
};

int rev[N<<2]; z w[N<<2];
int init(int len){
	int lim=1,k=0; while(lim<len)lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1;len<lim;len<<=1){
		z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
		for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
	}
	return lim;
}

void dft(vet &a,int lim){
	a.resize(lim);
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				z x=a[i+j],y=a[i+j+len]*w[j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
			}
}
void idft(vet &a,int lim){
	dft(a,lim); z inv=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)a[i]=a[i]*inv;
}

inline vet operator+(vet a,const vet &b){
	a.resize(std::max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
}

inline vet operator-(vet a,const vet &b){
	a.resize(std::max(a.size(),b.size()));
	for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
}

inline vet operator*(vet a,vet b){
	int len=a.size()+b.size()-1,lim=init(len);
	dft(a,lim),dft(b,lim);
	for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
	idft(a,lim),a.resize(len); return a;
}

inline vet inv(const vet &a,int len=-1){
	if((len=~len?len:a.size())==1)return {fpow(a[0],mod-2)};
	vet f=inv(a,len+1>>1),g(&a[0],&a[len]);
	int lim=init((len<<1)-1);
	dft(f,lim),dft(g,lim);
	for(int i=0;i<lim;i++)f[i]=f[i]*(2-f[i]*g[i]);
	idft(f,lim),f.resize(len); return f;
}

inline vet operator%(vet a,vet b){
	int len=a.size()-(int)b.size()+1; if(len<=0)return a;
	vet f=a; std::reverse(f.begin(),f.end()),f.resize(len); 
	vet g=b; std::reverse(g.begin(),g.end()),g.resize(len);
	vet q=f*inv(g); q.resize(len),std::reverse(q.begin(),q.end());
	vet r=a-q*b; return r.resize(g.size()-1),r;
}

struct pack{vet G,C,D;};
pack solve(int u,int l,int r){
	pack S;
	if(l==r){
		S.G={1,0-fpow(a,l)*fpow(b,m-l)};
		S.C={fpow(q*A*a,l)*fpow(q*B*b,m-l)*C(m,l)};
		S.D={fpow(A*(a+q),l)*fpow(B*(b+q),m-l)*C(m,l)};
	}else{
		int mid=(l+r)>>1;
		pack L=solve(u<<1,l,mid);
		pack R=solve(u<<1|1,mid+1,r);
		S.G=L.G*R.G;
		S.C=L.C*R.G+L.G*R.C;
		S.D=L.D*R.G+L.G*R.D;
	}
	return S;
}

z BM(vet P,vet Q,int n){
	vet S={1},A={0,1};
	for(;n;n>>=1,A=A*A%Q)if(n&1)S=S*A%Q;

}

int main(){
	read(n),read(m),read(p.x),read(q.x);	D=cipolla(p*p+4*q),a=(p+D)*499122177,b=(p-D)*499122177,A=fpow(D,mod-2),B=0-A;
	fac[0]=ifac[0]=ifac[1];
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod-i];
	for(int i=1;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
	pack S=solve(1,0,m); for(int _=2;_--;)S.C.insert(S.C.begin(),0);
	print(BM(S.D,S.C+S.G,n).x,'\n');
}