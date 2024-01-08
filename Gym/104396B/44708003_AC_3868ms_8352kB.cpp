#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=1e3+9,M=1e4+9;
const long long inf=2242545357980376863>>1;
const long long lim=-1e11;
int n,m;
bool ban[N],bancol[N];
long long f[N][N],ans[N];
struct edge{
	int u,v,w;
}e[M];
inline void chkmin(long long &a,long long b){
	if(b<a)a=b;
}
void floyd(){
	for(int k=0;k<n;k++){
		long long *fk=f[k];
		for(int i=0;i<n;i++){
			long long *fi=f[i];
			static long long x[8];
			for(int j=0;j<n;j+=8){
				*x=*(fi+k)+*(fk+j);
				*(x+1)=*(fi+k)+*(fk+j+1);
				*(x+2)=*(fi+k)+*(fk+j+2);
				*(x+3)=*(fi+k)+*(fk+j+3);
				*(x+4)=*(fi+k)+*(fk+j+4);
				*(x+5)=*(fi+k)+*(fk+j+5);
				*(x+6)=*(fi+k)+*(fk+j+6);
				*(x+7)=*(fi+k)+*(fk+j+7);
				if(*x<*(fi+j))*(fi+j)=*x;
				if(*(x+1)<*(fi+j+1))*(fi+j+1)=*(x+1);
				if(*(x+2)<*(fi+j+2))*(fi+j+2)=*(x+2);
				if(*(x+3)<*(fi+j+3))*(fi+j+3)=*(x+3);
				if(*(x+4)<*(fi+j+4))*(fi+j+4)=*(x+4);
				if(*(x+5)<*(fi+j+5))*(fi+j+5)=*(x+5);
				if(*(x+6)<*(fi+j+6))*(fi+j+6)=*(x+6);
				if(*(x+7)<*(fi+j+7))*(fi+j+7)=*(x+7);
			}
		}
		if(k%16==0){
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++){
					if(f[i][j]<lim)f[i][j]=lim;
				}
		}
	}
}
int main(){
#ifdef memset0
	freopen("B36.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	memset(f,31,sizeof(f));
	for(int i=0;i<n;i++){
		f[i][i]=0;
	}
	for(int i=0;i<m;i++)
		if(e[i].w%2==0){
			chkmin(f[e[i].u][e[i].v],e[i].w);
		}
	cerr<<clock()/(double)CLOCKS_PER_SEC<<endl;
	floyd();
	cerr<<clock()/(double)CLOCKS_PER_SEC<<endl;
	for(int i=0;i<m;i++)
		if(e[i].w%2!=0)
			for(int j=0;j<m;j++)
				if(e[j].w%2!=0){
					chkmin(f[e[i].u][e[j].v],e[i].w+f[e[i].v][e[j].u]+e[j].w);
				}
	cerr<<clock()/(double)CLOCKS_PER_SEC<<endl;
	floyd();
	cerr<<clock()/(double)CLOCKS_PER_SEC<<endl;
	memset(ans,31,sizeof(ans));
	// for(int i=0;i<n;i++)
	// 	for(int j=0;j<n;j++)
	// 		if(f[i][j]>inf){
	// 			cerr<<"inf"<<" \n"[j+1==n];
	// 		}else{
	// 			cerr<<f[i][j]<<" \n"[j+1==n];
	// 		}
	for(int j=0;j<n;j++){
		for(int i=0;i<m;i++)
			if(e[i].w%2!=0){
				// fprintf(stderr,"> %d %d %d\n",e[i].u,e[i].v,e[i].w);
				// fprintf(stderr,"  %d : %lld %d %lld\n",j,f[j][e[i].u],e[i].w,f[e[i].v][j]);
				if(f[j][e[i].u]<inf&&f[e[i].v][j]<inf){
					long long cur=f[j][e[i].u]+e[i].w+f[e[i].v][j];
					if(cur<0||e[i].w+f[e[i].v][e[i].u]<0){
						ban[j]=true;
						break;
					}else{
						ans[j]=min(ans[j],cur);
					}
				}
			}
	}
	for(int i=0;i<n;i++){
		if(ban[i]){
			cout<<"Haha, stupid Honkai"<<endl;
		}else if(ans[i]>=inf){
			cout<<"Battle with the crazy Honkai"<<endl;
		}else{
			cout<<ans[i]<<endl;
		}
	}
}