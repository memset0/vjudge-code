#include<bits/stdc++.h>
using namespace std;
const int N=10;
int n;
array<int,5> a[N];
int main(){
#ifdef memset0
    freopen("lock2.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=0;j<5;j++)cin>>a[i][j];
	}
	int ans=0;
	array<int,5> t;
	for(t[0]=0;t[0]<10;t[0]++)
		for(t[1]=0;t[1]<10;t[1]++)
			for(t[2]=0;t[2]<10;t[2]++)
				for(t[3]=0;t[3]<10;t[3]++)
					for(t[4]=0;t[4]<10;t[4]++){
						bool fl=true;
						for(int i=1;i<=n;i++){
							int x=-1,y=-1;
							for(int j=0;j<5;j++)
								if(t[j]!=a[i][j]){
									if(x==-1)x=j;
									else if(y==-1)y=j;
									else{
										fl=false;
										break;
									}
								}
							if(!fl)break;
//							cerr<<i<<" : "<<x<<" "<<y<<endl;
							if(x==-1){
								fl=false;
								break;
							}else if(y==-1){
								continue;	
							}else if(y==x+1){
								if((a[i][x]-t[x]+10)%10==(a[i][y]-t[y]+10)%10)continue;
							}
							fl=false;
							break;
						}
						if(!fl)continue;
						++ans;
//						for(int j=0;j<5;j++)cerr<<t[j]<<" \n"[j==4];
					}
	cout<<ans<<endl;
}