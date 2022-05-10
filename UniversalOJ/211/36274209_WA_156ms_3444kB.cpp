#include<bits/stdc++.h>
using namespace std;
const int N=110,mod=998244353;
int n,w[4];
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(long long)a*a%mod)if(b&1)s=(long long)s*a%mod;return s;}
namespace N1{
	int tag[21][21];
	void sol(){
		memset(tag,-1,sizeof(tag));
		int s1=0,s2=0;
		for(int x=0;x<(1<<(n<<1));x++){
			int h=1,c=1,ux=0,uy=0;
			tag[10][10]=x;
			for(int i=0;i<n;i++){
				int k=x>>(i<<1)&3;
				h=(long long)h*w[k]%mod;
				if(k==0)ux++;
				if(k==1)ux--;
				if(k==2)uy++;
				if(k==3)uy--;
//				cerr<<ux<<" "<<uy<<endl;
				if(tag[ux+10][uy+10]!=x){
					tag[ux+10][uy+10]=x;
					++c;
				}
			}
			s1=(s1+(long long)c*h)%mod;
			s2=(s2+(long long)c*c*h)%mod;
//			cerr<<">> "<<x<<" "<<c<<endl;
		}
		int avg=(long long)s1*fpow(fpow(w[0]+w[1]+w[2]+w[3],n),mod-2)%mod;
//		cerr<<s1<<" "<<fpow(w[0]+w[1]+w[2]+w[3],n)<<" "<<avg<<endl;
		int ans=(s2-2ll*avg*s1+(long long)avg*avg%mod*fpow(w[0]+w[1]+w[2]+w[3],n))%mod;
		ans=(long long)ans*fpow(w[0]+w[1]+w[2]+w[3],n)%mod;
		cout<<(ans+mod)%mod<<endl;
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>w[0]>>w[1]>>w[2]>>w[3];
	if(n<=10)return N1::sol(),0;
}