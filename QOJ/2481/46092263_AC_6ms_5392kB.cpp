#include<bits/stdc++.h>
using namespace std;
const int N=1e5,B=16;
int h,t,ch,c[N+10],ar[20],n,tt[20];
int a[B+10],v[B+10];
int s[(1<<B)+10],w[(1<<B)+10],ppc[(1<<B)+10],fl[(1<<B)+10];
vector<int>ue[20],suc[20];
int main(){
	scanf("%d%d",&h,&t);
	for(int i=1;i<=h;++i)scanf("%d",&c[i]);
	for(int i=1;i<=h;++i){
		for(int j=c[i-1]+1;j<=c[i];++j){
			++n;
			if(n>t)return puts("0"),0;
			for(int k=i;k<=h&&c[k]>=j;++k,++ar[n]);
		}
	}
	for(int i=1;i<=n;++i)tt[i]=tt[i-1]+ar[i];
	for(int i=1;i<=t;++i){
		scanf("%d%d",&a[i],&v[i]);
		s[1<<i-1]=a[i],w[1<<i-1]=v[i];
	}
	for(int i=1;i<(1<<t);++i){
		fl[i]=-1;
		ppc[i]=ppc[i>>1]+(i&1);
		s[i]=s[i&(i-1)]+s[i&-i];
		//cout<<"S "<<i<<"="<<s[i]<<"\n";
		w[i]=w[i&(i-1)]+w[i&-i];
		for(int j=1;j<=n;++j)if(s[i]==tt[j])ue[j].push_back(i);
	}
	if(tt[n]>s[(1<<t)-1])return puts("0"),0;
	suc[0].push_back(0);
	for(int i=1;i<=n;++i){
		//cout<<"---------------\ni="<<i<<"\n";
		for(int j:ue[i]){
			//cout<<"j="<<j<<"\n";
			if((1<<ppc[j])<suc[i-1].size()){
				for(int k=j;;k=(j&k-1)){
					if(fl[k]==i-1){
						fl[j]=i;
						break;
					}
					if(!k)break;
				}
			}else{
				for(int k:suc[i-1])if((j&k)==k){
					fl[j]=i;
					break;
				}
			}
			if(fl[j]==i)suc[i].push_back(j);
		}
	}
	if(!suc[n].size())puts("0");
	else{
		int ans=0;
		for(int i:suc[n])ans=max(ans,w[i]);
		printf("%d",ans);
	}
	return 0;
}
/*
4 4
1 2 1 2
3 2
1 1
1 2
1 3
*/