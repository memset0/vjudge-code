#include<bits/stdc++.h>
#define u64 unsigned long long
#define ic8 __int128
using namespace std;
const int N=65,M=22;
int n,lg[1<<M];
u64 s,a[N],b[N],w[1<<M];
unordered_map<u64,int> p;
void exgcd(ic8 a,ic8 b,ic8 &x,ic8 &y){
	if(!b)return x=1,y=0,void();
	exgcd(b,a%b,x,y);
	tie(x,y)=make_pair(y,x-y*(a/b));
}
ic8 inv(ic8 a,ic8 b){ic8 x,y;return exgcd(a,b,x,y),(x%b+b)%b;}
inline void out(u64 ans){
	for(int i=0;i<n;i++)putchar(48+((ans>>i)&1));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(int i=0;i<M;i++)lg[1<<i]=i;
	cin>>n;
	for(int i=0;i<n;i++)cin>>b[i];
	cin>>s;
	if(n<=44){
		int m=n>>1;
		p[0]=w[0]=0;
		for(int x=1;x<(1<<m);x++){
			w[x]=w[x^(x&-x)]+b[lg[x&-x]];
			p[w[x]]=x;
		}
		if(p.count(s))return out(p[s]),0;
		w[0]=0;
		for(int x=1;x<(1<<(n-m));x++){
			w[x]=w[x^(x&-x)]+b[lg[x&-x]+m];
			if(p.count(s-w[x])){
				u64 ans=(u64)(p[s-w[x]])|((u64)(x)<<m);
				return out(ans),0;
			}
		}
	}else{
		u64 r;
		auto calc=[](u64 source,u64 inverse,int offset){
			if(offset){
				return (((source>>offset)*inverse)&((1ull<<(64-offset))-1))<<1;
			}else{
				return source*inverse;
			}
		};
		auto calcR=[](u64 a,u64 b){
			int q=0;
			while(a&1^1){
				if(b&1)return make_pair(0ull,false);
				a>>=1,b>>=1,q++;
			}
			u64 c=b*inv(a,(ic8)(1)<<(64-q));
			if(q)c%=1ull<<(64-q);
			return make_pair(c,true);
		};
		auto verify=[&](u64 f){
			int q=0,fl;
			tie(r,fl)=calcR(f,b[0]);
			// printf("%llu*%llu=%llu(%llu)\n",f,r,b[0],f*r);
			if(!fl)return false;
			while(r&1^1)r>>=1,r++;
			for(int i=0;i<n;i++)if(b[i]&((1ull<<q)-1))return false;
			u64 x=inv(r,(ic8)(1)<<(64-q));
			for(int i=0;i<n;i++)a[i]=calc(b[i],x,q);
			u64 tmp=0;
			// printf("check %llu %llu %llu :: %llu\n",f,r,x<<q,((1ull<<(64-q))-1));
			// for(int i=0;i<n;i++)printf("%llu%c",a[i]," \n"[i+1==n]);
			for(int i=0;i<n;i++){
				if(a[i]<=tmp)return false;
				if(!a[i]||tmp+a[i]<tmp)return false;
				tmp+=a[i];
			}
			s=calc(s,x,q);
			// cerr<<"win!"<<endl;
			return true;
		};
		// return verify(566),0;
		for(u64 f=1;;f++)if(verify(f)){
			// printf("> r=%llu f=%llu\n",r,f);
			u64 ans=0;
			for(int i=n-1;i>=0;i--)if(s>=a[i])s-=a[i],ans|=1ull<<i;
			return out(ans),0;
		}
	}
}