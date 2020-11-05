#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e5+10,mod=998244353;
int n,m,R[N<<2];
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}W[N<<2];
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
struct poly:std::vector<z>{
	using std::vector<z>::vector;
	inline void in(){for(size_t i=0;i<size();i++)read((int&)this->operator[](i));}
	inline void out()const{for(size_t i=0;i<size();i++)print(this->operator[](i).x," \n"[i+1==size()]);}
};
int initdft(int len){
	int lim=1,k=0;while(lim<=len)lim<<=1,++k;
	for(int i=0;i<lim;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(k-1));
	static int slen=1;for(int len=slen;len<lim;len<<=1){
		z w=fpow(3,(mod-1)/(len<<1)); W[len]=1;
		for(int i=1;i<len;i++)W[i+len]=W[i+len-1]*w;
	}return lim;
}
void dft(poly &a,int lim){
	a.resize(lim);
	for(int i=0;i<lim;i++)if(i<R[i])std::swap(a[i],a[R[i]]);
	for(int len=1;len<lim;len<<=1)for(int i=0;i<lim;i+=(len<<1))for(int j=0;j<len;j++)
		{z x=a[i+j],y=a[i+j+len]*W[j+len];a[i+j]=x+y,a[i+j+len]=x-y;}
}
void idft(poly &a,int lim){
	std::reverse(&a[1],&a[lim]),dft(a,lim);z inv=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)a[i]=a[i]*inv;
}
poly operator+(poly f,const poly &g){
	if(g.size()>f.size())f.resize(g.size());
	for(int i=0;i<g.size();i++)f[i]=f[i]+g[i];
	return f;
}
poly operator-(poly f,const poly &g){
	if(g.size()>f.size())f.resize(g.size());
	for(int i=0;i<g.size();i++)f[i]=f[i]-g[i];
	return f;
}
poly operator*(poly f,z x){
	for(int i=0;i<f.size();i++)f[i]=f[i]*x;
	return f;
}
poly operator*(poly f,poly g){
	int l=f.size()+g.size()-1,lim=initdft(l);
	dft(f,lim),dft(g,lim);
	for(int i=0;i<lim;i++)f[i]=f[i]*g[i];
	idft(f,lim);return f.resize(l),f;
}
poly inv(const poly &f,int len=-1){
	if((len=~len?len:f.size())==1)return poly{fpow(f[0],mod-2)};
	poly a=inv(f,(len+1)>>1),b(&f[0],&f[len]);int lim=initdft((len<<1)-1);
	dft(a,lim),dft(b,lim);
	for(int i=0;i<lim;i++)a[i]=a[i]*(2-a[i]*b[i]);
	idft(a,lim);
	return a.resize(len),a;
}
poly move(poly f){return f.insert(f.begin(),0),f;}
poly solve(int n){
	if(n==1){return poly(1,1);}
	poly A=solve((n+1)>>1);
	poly AA=A*A; AA.resize(n);
	poly AAA=AA*A; AAA.resize(n);
	poly A2(n),A3(n);
	// printf(">>> %d\n",n);
	for(int i=0;i<n;i+=2)A2[i]=A[i/2];
	for(int i=0;i<n;i+=3)A3[i]=A[i/3];
	poly F=move(A3)*fpow(3,mod-2)+move(AAA)*fpow(6,mod-2)+move(A*A2)*fpow(2,mod-2)+poly(1,1)-A; F.resize(n);
	poly G=move(AA)*fpow(2,mod-2)+move(A2)*fpow(2,mod-2)-poly(1,1); G.resize(n);
	poly H=F*inv(G); H.resize(n),H=A-H;
	// F.out(),G.out(),H.out();
	return H;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	poly s=solve(n+1);
	print(s[n].x,'\n');
}