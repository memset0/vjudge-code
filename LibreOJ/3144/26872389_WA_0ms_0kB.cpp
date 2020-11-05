#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
const int N=1e6+10;
int n;
long long A,B,ans;
std::vector<long long> tim;
std::map<long long,int> sum;
std::map<long long,std::vector<std::pair<int,int>>> opt;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(A),read(B);
	// A/=gcd(A,B+1);
	for(int i=1;i<=n;i++){
		long long L,R,xl,yl,xr,yr;
		read(L),xl=L/B,yl=L%B;
		read(R),xr=R/B,yr=R%B;
		if(xl==xr){
			opt[xl%A].push_back({yl,yr});
		}else{
			opt[(xl++)%A].push_back({yl,B-1});
			opt[(xr--)%A].push_back({0,yr});
			if(xr-xl+1>=A){
				sum[0]++;
			}else{
				if(xl<=xr){
					xl%=A,xr%=A;
					if(xl<=xr){
						sum[xl]++,sum[xr+1]--;
					}else{
						sum[0]++,sum[xr+1]--;
						sum[xl]++;
					}
				}
			}
		}
	}
	tim.push_back(A);
	for(const auto &it:opt)tim.push_back(it.first);
	for(const auto &it:sum)tim.push_back(it.first);
	std::sort(tim.begin(),tim.end());
	tim.erase(std::unique(tim.begin(),tim.end()),tim.end());
	long long fl=0,lst=0;
	for(long long t:tim){
		if(fl)ans+=B*(t-lst);
		fl+=sum[t];
		if(!fl){
			std::vector<int> tim;
			std::map<long long,int> sum;
			for(const auto &o:opt[t]){
				tim.push_back(o.first),sum[o.first]++;
				tim.push_back(o.second+1),sum[o.second+1]--;
			}
			tim.push_back(B);
			std::sort(tim.begin(),tim.end());
			tim.erase(std::unique(tim.begin(),tim.end()),tim.end());
			long long fl=0,lst=0;
			for(long long t:tim){
				if(fl)ans+=(t-lst);
				fl+=sum[t];
				lst=t;
			}
		}
		lst=t;
	}
	printf("%lld\n",ans);
}