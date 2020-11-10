#include<bits/stdc++.h>

const int N=1e5+10;
int c[5],d[5],q,s;
long long ans,f[N];

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	std::cin>>c[1]>>c[2]>>c[3]>>c[4]>>q;
	f[0]=1;
	for(int i=1;i<=4;i++)
		for(int j=c[i];j<N;j++)
			f[j]+=f[j-c[i]];
	for(int i=1;i<=q;i++){
		std::cin>>d[1]>>d[2]>>d[3]>>d[4]>>s;
		ans=0;
		for(int S=0;S<16;S++){
			int t=s,cnt=0;
			for(int j=1;j<=4;j++)if((S>>(j-1))&1){
				t-=c[j]*(d[j]+1);
				++cnt;
			}
			if(t>=0)ans+=(cnt&1?-1:1)*f[t];
		}
		std::cout<<ans<<std::endl;
	}
}