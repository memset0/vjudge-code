#include<bits/stdc++.h>
#define F double
using namespace std;
const int N=50;
struct sta{
	F mx,mn;
	sta operator+(const sta&y)const{
		return(sta){mx+y.mx,mn+y.mn};
	}
	sta operator*(const F&y)const{
		return(sta){mx*y,mn*y};
	}
}f[N+5][N+5][N+5][N+5],ans;
int n,K,TIM,rm[N*N][N+5],tt,tmp;
F P,pr[N*N][N+5],vis[N+5][N+5][N+5][N+5];
sta Merge(sta x,sta y){
	return(sta){max(x.mx,y.mx),min(x.mn,y.mn)};
}
bool Check(){
	for(int i=0;i<K;++i)if(rm[tt][i]>1)return 1;
	return 0;
}
sta dfs(int p,int l,int r,int nw){
	if(vis[p][l][r][nw]||nw==K)return f[p][l][r][nw];
	//cout<<"DFS "<<p<<" "<<l<<" "<<r<<" "<<nw<<"\n";
	vis[p][l][r][nw]=1;
	if(nw<K&&l>r)return(f[p][l][r][nw].mx=f[p][l][r][nw].mn=1,f[p][l][r][nw]);
	F pp=1;
	sta tans=(sta){0,0},tv=(sta){0,0},*dp=&f[p][l][r][nw];
	if(nw==p){
		if(p==l-1){
			for(int i=l;i<=r;++i){
				tv=tv+dfs(p+1,l+1,min(r+1,K-1),i)*pp*P;
				//cout<<"i="<<i<<" tv="<<tv.mx<<"\n";
				pp*=1-P;
			}
			tv=tv+dfs(p+1,l+1,min(r+1,K-1),r+1)*pp;
			tv=tv*(1-P);
			(*dp)=tv+dfs(p,l+1,min(r+1,K-1),p)*P;
		}else(*dp)=dfs(p,l+1,min(r+1,K-1),p)*P+dfs(p+1,l,r,p+1)*(1-P);
	}else if(nw==l){
		if(p==l-1){
			for(int i=l;i<=r;++i){
				tv=tv+dfs(p+1,l+1,min(r+1,K-1),i)*pp*P;
				pp*=1-P;
			}
			tv=tv+dfs(p+1,l+1,min(r+1,K-1),r+1)*pp;
			tv=tv*P;
			pp=1;
			for(int i=l+1;i<=r;++i){
				tans=tans+dfs(p,l+1,min(r+1,K-1),i)*pp*P;
				pp*=1-P;
			}
			tans=tans+dfs(p,l+1,min(r+1,K-1),r+1)*pp;
			tans=tans*(1-P);
			(*dp)=tv+tans;
		}else{
			tv=dfs(p+1,l,r,nw)*P;
			pp=1;
			for(int i=l+1;i<=r;++i){
				tans=tans+dfs(p,l+1,min(r+1,K-1),i)*pp*P;
				pp*=1-P;
			}
			tans=tans+dfs(p,l+1,min(r+1,K-1),r+1)*pp;
			tans=tans*(1-P);
			(*dp)=tv+tans;
		}
	}else{
		for(int i=nw;i<=r;++i){
			tans=tans+dfs(p,l+1,min(r+1,K-1),i)*pp*P;
			pp*=1-P;
		}
		tans=tans+dfs(p,l+1,min(r+1,K-1),r+1)*pp;
		if(p==l-1){
			pp=1;
			for(int i=nw;i<=r;++i){
				tv=tv+dfs(p+1,l+1,min(r+1,K-1),i)*pp*P;
				pp*=1-P;
			}
			tv=tv+dfs(p,l+1,min(r+1,K-1),r+1)*pp;
		}else tv=dfs(p+1,l,r,nw);
		(*dp)=Merge(tans,tv);
	}
	//cout<<"f "<<p<<" "<<l<<" "<<r<<" "<<nw<<"={"<<(*dp).mx<<","<<(*dp).mn<<"}\n";
	return(*dp);
}
int main(){
	scanf("%d%d%lf",&n,&K,&P);
	rm[tt=1][0]=n,pr[tt][0]=1;
	while(Check()){
		for(int i=0;i<K;++i){
			tmp=rm[tt][i];
			if(tmp>1){
				rm[tt+1][i]+=(tmp+1>>1);
				rm[tt+1][i+1]+=(tmp>>1);
				if(tmp&1){
					pr[tt+1][i]+=pr[tt][i]*(1.0/tmp+(1-1.0/tmp)*P);
					pr[tt+1][i+1]+=pr[tt][i]*(1-1.0/tmp)*(1.0-P);
				}else{
					pr[tt+1][i]+=pr[tt][i]*P;
					pr[tt+1][i+1]+=pr[tt][i]*(1.0-P);
				}
			}else if(tmp){
				rm[tt+1][i]+=1;
				pr[tt+1][i]+=pr[tt][i];
			}
		}
		++tt;
		/*cout<<"STATE "<<tt<<":\n";
		for(int i=0;i<K;++i){
			cout<<"("<<rm[tt][i]<<","<<pr[tt][i]<<")\n";
		}
		puts("");*/
	}
	tmp=0;
	while(tmp+1<K&&rm[tt][tmp+1])++tmp;
	for(int i=0;i<K;++i)ans=ans+dfs(0,1,tmp,i)*pr[tt][i];
	printf("%.10lf %.10lf",ans.mn,ans.mx);
	return 0;
}
//3 1 0.5
//2 2 0.4
//3 4 0.42