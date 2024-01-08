#include<bits/stdc++.h>
using namespace std;
struct atom{
	int x,y,w;
	inline bool operator<(const atom &rhs)const{
		return w>rhs.w;
	}
}e={-1,-1,-1},c[16];
struct bundle{
	atom a[3];
}b[3];
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	int T,op,x,y,w,last=0,ans;
	cin>>T;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			b[i].a[j]=e;
	while(T--){
		cin>>op;
		if(op==1){
			cin>>x>>y>>w;
			x^=last,y^=last,w^=last;
			int m=0;
			c[m++]={x,y,w};
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(b[i].a[j].w!=-1){
						c[m++]=b[i].a[j];
						b[i].a[j]=e;
					}			
			sort(c,c+m);
			for(int u=0;u<m;u++){
				for(int i=0;i<3;i++){
					if(b[i].a[0].w==-1){
						b[i].a[0]=c[u];
						break;
					}else if(b[i].a[0].x==c[u].x&&b[i].a[0].y==c[u].y){
						if(c[u].w>b[i].a[0].w){
							b[i].a[0]=c[u];
						}
						break;
					}else if(b[i].a[0].x==c[u].x){
						if(c[u].w>b[i].a[1].w){
							b[i].a[1]=c[u];
						}
						break;
					}else if(b[i].a[0].y==c[u].y){
						if(c[u].w>b[i].a[2].w){
							b[i].a[2]=c[u];
						}
						break;
					}
				}
			}
			// cerr<<op<<" "<<x<<" "<<y<<" "<<w<<endl;
			// for(int i=0;i<3;i++)
			// 	for(int j=0;j<3;j++)
			// 		fprintf(stderr,"[%d,%d] %d %d %d\n",i,j,b[i].a[j].x,b[i].a[j].y,b[i].a[j].w);
		}else{
			cin>>x>>y;
			x^=last,y^=last;
			ans=0;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(b[i].a[j].x!=x&&b[i].a[j].y!=y){
						ans=max(ans,b[i].a[j].w);
						// cerr<<"! "<<i<<" "<<j<<" "<<b[i].a[j].w<<endl;
					}
			// cerr<<op<<" "<<x<<" "<<y<<endl;
			// for(int i=0;i<3;i++)
			// 	for(int j=0;j<3;j++)
			// 		fprintf(stderr,"[%d,%d] %d %d %d\n",i,j,b[i].a[j].x,b[i].a[j].y,b[i].a[j].w);
			cout<<ans<<endl;
			// last=ans;
		}
	}
}