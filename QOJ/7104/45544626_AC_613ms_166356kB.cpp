#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=1e4+9,M=N<<8;
int T,n,nod,q[M],l,r,id[N][256];
bool tag[M];
vector<int> G[M];
struct atom{
	string op;
	int x,y;
}a[N];
inline int newnode(){
	++nod;
	G[nod].clear();
	G[nod].shrink_to_fit();
	return nod;
}
inline void addedge(int u,int v){
	G[u].push_back(v);
}
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i].op>>a[i].x;
			// cerr<<"! "<<a[i].op<<endl;
			if(a[i].op!="add"){
				cin>>a[i].y;
			}
		}
		nod=0;
		for(int i=1;i<=n+1;i++){
			for(int j=0;j<256;j++){
				id[i][j]=newnode();
			}
		}
		for(int i=1;i<=n;i++)
			if(a[i].op=="add"){
				for(int j=0;j<256;j++){
					addedge(id[i][j],id[i+1][(j+a[i].x)%256]);
				}
			}else if(a[i].op=="beq"){
				for(int j=0;j<256;j++){
					if(j==a[i].x){
						addedge(id[i][j],id[a[i].y][j]);	
					}else{
						addedge(id[i][j],id[i+1][j]);	
					}
				}
			}else if(a[i].op=="bne"){
				for(int j=0;j<256;j++){
					if(j!=a[i].x){
						addedge(id[i][j],id[a[i].y][j]);	
					}else{
						addedge(id[i][j],id[i+1][j]);	
					}
				}
			}else if(a[i].op=="blt"){
				for(int j=0;j<256;j++){
					if(j<a[i].x){
						addedge(id[i][j],id[a[i].y][j]);	
					}else{
						addedge(id[i][j],id[i+1][j]);	
					}
				}
			}else if(a[i].op=="bgt"){
				for(int j=0;j<256;j++){
					if(j>a[i].x){
						addedge(id[i][j],id[a[i].y][j]);	
					}else{
						addedge(id[i][j],id[i+1][j]);	
					}
				}
			}
		fill(tag,tag+nod+1,0);
		tag[id[1][0]]=true;
		q[l=r=1]=id[1][0];
		while(l<=r){
			int u=q[l++];
			for(int v:G[u])
				if(!tag[v]){
					tag[v]=true;
					q[++r]=v;
				}
		}
		bool flag=false;
		for(int i=0;i<256;i++)
			if(tag[id[n+1][i]]){
				flag=true;
				break;
			}
		// cerr<<"! "<<nod<<" "<<M<<endl;
		cout<<(flag?"Yes":"No")<<endl;
	}
}