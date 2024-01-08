#include<bits/stdc++.h>
using namespace std;
const int N=2e3;
int n,m,cnt;
vector<tuple<int,int,int,int>> ans;
char mp[N+20][N+20];
void Get(int x,int l,int r){
	int y=x;
	while(mp[y+1][l]=='X'){
		++y;
		if(mp[y][l+1]=='X'&&mp[y-1][l+1]!='X'){
			if(mp[y+1][l]=='X'&&mp[y+1][l+1]=='X'&&mp[y+1][l+2]!='X'&&mp[y+2][l]=='X'&&mp[y+2][l+1]=='X'&&mp[y][l+2]=='X')continue;
			break;
		}
		//if(x+1<y&&y+2<=n&&mp[y][l+1]=='X'&&mp[y+1][l+1]=='X'&&mp[y-1][l+1]!='X'&&mp[y+2][l+1]!='X')break;
	}
	ans.emplace_back(x,l,y,r);
	for(int i=l;i<=r;++i)mp[x][i]=mp[y][i]='.';
	for(int i=x;i<=y;++i)mp[i][l]=mp[i][r]='.';
}
int main(){
#ifdef memset0
	freopen("G.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	scanf("%d%d",&n,&m);
	n=m=max(n,m)+5;
	// cerr<<"! "<<n<<" "<<m<<endl;
	for(int i=1;i<=n;++i)scanf("%s",mp[i]+1);
	for(int i=1;i<=n;++i){
		// cerr<<"I="<<i<<"\n";
		for(int j=1,k=1;j<=m;j=k+1,k=j)if(mp[i][j]=='X'){
			while(k+1<=m&&mp[i][k+1]=='X')++k;
			// cerr<<"I="<<i<<" j="<<j<<" k="<<k<<"\n";
			int t,ls=j;
			for(t=j+1;t+3<k;++t)if(mp[i+1][t]!='X'&&mp[i+1][t+3]!='X'&&mp[i+1][t+1]=='X'&&mp[i+1][t+2]=='X'){
				Get(i,ls,t+1);
				ls=t+2,t+=2;
			}
			Get(i,ls,k);
		}
	}
	cout<<ans.size()<<endl;
	for(auto [a,b,c,d]:ans){
		cout<<a<<" "<<b<<" "<<c<<" "<<d<<'\n';
	}
	return 0;
}
/*
3 3
XXX
X.X
XXX
*/
/*
6 7
XXXXXXX
X.XX..X
XXXXXXX
XXXXXXX
X.XX..X
XXXXXXX
*/
/*
10 10
..........
XXXXXXXXXX
X..XXXX..X
X..X..X..X
X..XXXX..X
X...XXXX.X
X...X..X.X
X...X..X.X
X...XXXX.X
XXXXXXXXXX
*/
/*
10 10
..........
..xxxx....
..x..xxxxx
..x..xx..x
..xxxxx..x
...xxxx..x
...x.xx..x
xxxx.xxxxx
x.xx.x....
xxxxxx....
*/