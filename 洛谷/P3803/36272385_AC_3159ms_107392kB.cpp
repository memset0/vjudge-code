#include<bits/stdc++.h>
const int N=4e6+10;
const double PI=acos(-1);
int n,m,k,lim,rev[N];
std::complex<double> a[N],b[N],w[N];
void fft(std::complex<double> *a){
	for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				std::complex<double> x=a[i+j],y=a[i+j+len]*w[j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
			}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%d%d",&n,&m),++n,++m;
	for(int i=0,x;i<n;i++)scanf("%d",&x),a[i].real(x);
	for(int i=0,x;i<m;i++)scanf("%d",&x),b[i].real(x);
	lim=1; while(lim<n+m-1)lim<<=1,++k;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	for(int len=1;len<lim;len<<=1){
		std::complex<double> wn(cos(PI/len),sin(PI/len)); w[len].real(1);
		for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn; 
	}
	fft(a),fft(b);
	for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
	fft(a),std::reverse(a+1,a+lim);
	for(int i=0;i<n+m-1;i++)printf("%d ",int(a[i].real()/lim+0.5));
}