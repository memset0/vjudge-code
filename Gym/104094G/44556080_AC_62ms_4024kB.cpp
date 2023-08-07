#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int N=1e3+9,nxt[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
int n,m,a[N][N];
string s;
bool update(){
	bool found=false;
	for(int i=2;i<n;i++){
		for(int l=1,r;l<=m;l=r+1){
			r=l;
			if(a[i][l]!=1)continue;
			while(r+1<=m&&a[i][r+1]==1)++r;
			if(l-1>=1&&r+1<=m&&a[i][l-1]==0&&a[i][r+1]==0){
				bool fl=true;
				for(int j=l;j<=r;j++)fl&=a[i-1][j]==0;
				for(int j=l;j<=r;j++)fl&=a[i+1][j]==1;
				if(fl){
					for(int j=l;j<=r;j++)a[i][j]=0;
					found=true;
				}
			}
		}
	}
	for(int i=n-1;i>1;i--){
		for(int l=1,r;l<=m;l=r+1){
			r=l;
			if(a[i][l]!=1)continue;
			while(r+1<=m&&a[i][r+1]==1)++r;
			if(l-1>=1&&r+1<=m&&a[i][l-1]==0&&a[i][r+1]==0){
				bool fl=true;
				for(int j=l;j<=r;j++)fl&=a[i+1][j]==0;
				for(int j=l;j<=r;j++)fl&=a[i-1][j]==1;
				if(fl){
					for(int j=l;j<=r;j++)a[i][j]=0;
					found=true;
				}
			}
		}
	}
	for(int i=2;i<m;i++){
		for(int l=1,r;l<=n;l=r+1){
			r=l;
			if(a[l][i]!=1)continue;
			while(r+1<=n&&a[r+1][i]==1)++r;
			if(l-1>=1&&r+1<=n&&a[l-1][i]==0&&a[r+1][i]==0){
				bool fl=true;
				for(int j=l;j<=r;j++)fl&=a[j][i-1]==0;
				for(int j=l;j<=r;j++)fl&=a[j][i+1]==1;
				if(fl){
					for(int j=l;j<=r;j++)a[j][i]=0;
					found=true;
				}
			}
		}
	}
	for(int i=m-1;i>1;i--){
		for(int l=1,r;l<=n;l=r+1){
			r=l;
			if(a[l][i]!=1)continue;
			while(r+1<=n&&a[r+1][i]==1)++r;
			if(l-1>=1&&r+1<=n&&a[l-1][i]==0&&a[r+1][i]==0){
				bool fl=true;
				for(int j=l;j<=r;j++)fl&=a[j][i+1]==0;
				for(int j=l;j<=r;j++)fl&=a[j][i-1]==1;
				if(fl){
					for(int j=l;j<=r;j++)a[j][i]=0;
					found=true;
				}
			}
		}
	}
	return found;
}
int main(){
#ifdef memset0
	freopen("G.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=m;j++)a[i][j]=s[j-1]=='#';
	}
	queue<pii> q;
	for(int i=1;i<=n;i++){
		if(a[i][1]==0)a[i][1]=2,q.push({i,1});
		if(a[i][m]==0)a[i][m]=2,q.push({i,m});
	}
	for(int i=1;i<=m;i++){
		if(a[1][i]==0)a[1][i]=2,q.push({1,i});
		if(a[n][i]==0)a[n][i]=2,q.push({n,i});
	}
	while(q.size()){
		auto [x,y]=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int xx=x+nxt[i][0];
			int yy=y+nxt[i][1];
			if(xx<1||xx>n||yy<1||yy>m)continue;
			if(a[xx][yy]!=0)continue;
			a[xx][yy]=2;
			q.push({xx,yy});
		}
	}
	while(update());
	for(int x=1;x<=n;x++)
		for(int y=1;y<=m;y++)
			if(a[x][y]==0){
				for(int i=0;i<8;i++){
					int xx=x+nxt[i][0];
					int yy=y+nxt[i][1];
					if(xx<1||xx>n||yy<1||yy>m)continue;
					if(a[xx][yy]==1){
						a[xx][yy]=3;
					}
				}
			}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cout<<(a[i][j]==3?'#':'.');
		cout<<'\n';
	}
}