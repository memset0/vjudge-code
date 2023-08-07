#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,AD=55,INF=1e9;
struct elem{
	int v,c;
	bool operator<(const elem&y)const{
		return v<y.v;
	}
}a[110],ar[55];
int n,m,ns,f[55][55][2][2][110],nw,tt[55],tl,tr,tv,tc,ans;
int C[55][55];
//int lm[55][55][2][2],rm[55][55][2][2];
char s[10];
void Upd(int l,int r,int lc,int rc,int x,int xc){
	//cout<<"UPD "<<l<<" "<<r<<" in ("<<x<<","<<xc<<")\n";
	int ls=x-l,rs=r-x,fl=(xc==1);
	for(int i=-ls;i<=ls;++i)if(f[l][x-1][lc][fl][i+AD]){
		for(int j=-rs;j<=rs;++j){
			//cout<<"I="<<i<<" J="<<j<<","<<f[l][x-1][lc][fl][i+AD]<<"*"<<f[x+1][r][fl][rc][j+AD]<<"\n";
			f[l][r][lc][rc][i+j+xc+AD]=(f[l][r][lc][rc][i+j+xc+AD]+1ll*f[l][x-1][lc][fl][i+AD]*f[x+1][r][fl][rc][j+AD]%mod*C[ls+rs][ls])%mod;
			//cout<<"?="<<f[l][r][lc][rc][i+j+xc+AD]<<"\n";
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	C[0][0]=1;
	for(int i=1;i<=m;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)(C[i][j]=C[i-1][j]+C[i-1][j-1])>=mod?C[i][j]-=mod:0;
	}
	for(int i=1;i<=n;++i)scanf("%d %s",&a[i].v,s),a[i].c=(s[0]=='R'?1:-1);
	for(int i=1;i<=m;++i)scanf("%d",&a[n+i].v),a[n+i].c=0;
	sort(a+1,a+n+m+1);
	for(int i=1;i<=n+m;++i){
		ns+=a[i].c;
		if(a[i].c)continue;
		ar[++nw]=a[i];
		tl=tr=0;
		for(int j=i-1;j>=1&&!tl;--j)if(a[j].c)tl=j;
		for(int j=i+1;j<=n+m&&!tr;++j)if(a[j].c)tr=j;
		if(!tr||(tl&&a[i].v-a[tl].v<=a[tr].v-a[i].v))tt[nw]=tl;
		else tt[nw]=tr;
	}
	for(int i=1;i<=m+1;++i)f[i][i-1][0][0][AD]=f[i][i-1][0][1][AD]=f[i][i-1][1][0][AD]=f[i][i-1][1][1][AD]=1;
	for(int len=1;len<=m;++len){
		for(int l=1,r=len;r<=m;++l,++r){
			//cout<<"----------------------\nl="<<l<<" r="<<r<<"\n";
			for(int k=l;k<=r;++k){
				//cout<<"K="<<k<<"\n";
				tv=a[tt[k]].v,tc=a[tt[k]].c;
				if(l>1&&ar[k].v-ar[l-1].v<=min(abs(tv-ar[k].v),(r<m?ar[r+1].v-ar[k].v:INF))){
					Upd(l,r,0,0,k,-1),Upd(l,r,0,1,k,-1),Upd(l,r,1,0,k,1),Upd(l,r,1,1,k,1);
				}else if(r<m&&ar[r+1].v-ar[k].v<min(abs(tv-ar[k].v),(l>1?ar[k].v-ar[l-1].v:INF))){
					//cout<<"FR\n";
					Upd(l,r,0,0,k,-1),Upd(l,r,0,1,k,1),Upd(l,r,1,0,k,-1),Upd(l,r,1,1,k,1);
				}else{
					//cout<<"FN\n";
					Upd(l,r,0,0,k,tc),Upd(l,r,0,1,k,tc),Upd(l,r,1,0,k,tc),Upd(l,r,1,1,k,tc);
				}
				/*for(int tk=-(r-l+1);tk<=r-l+1;++tk)if(f[l][r][0][0][tk+AD]||f[l][r][0][1][tk+AD]||f[l][r][1][0][tk+AD]||f[l][r][1][1][tk+AD]){
				cout<<"F "<<l<<" "<<r<<" "<<tk<<"=["<<f[l][r][0][0][tk+AD]<<f[l][r][0][1][tk+AD]<<f[l][r][1][0][tk+AD]<<f[l][r][1][1][tk+AD]<<"\n";
			}*/
			}
			
		}
	}
	for(int i=(-ns)+1;i<=m;++i)(ans+=f[1][m][0][0][i+AD])>=mod?ans-=mod:0;
	printf("%d",ans);
	return 0;
}
/*
2 3
1 BLACK
10 RED
2 5 7

2 3
1 RED
10 BLACK
2 4 7
*/