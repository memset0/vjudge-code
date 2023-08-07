#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int R,F,G,sg[N+10],tl,tr,tmp,TIM,vis[N+10],sv;
void Upd(int x,int y,int v){
	tmp=(((x-y&1)?sg[v]:0)^((y&1)?sg[v+1]:0));
	vis[tmp]=TIM;
}
int main(){
	freopen("nimg.in","r",stdin);
	freopen("nimg.out","w",stdout);
	scanf("%d%d",&R,&F);
	for(int i=F;i<=N;++i){
		tl=1,++TIM;
		while(tl<=i){
			tr=i/(i/tl);
			Upd(tl,i%tl,i/tl);
			if(tl<tr)Upd(tl+1,i%(tl+1),i/tl);
			tl=tr+1;
		}
		for(int j=0;;++j)if(vis[j]!=TIM){
			sg[i]=j;
			break;
		}
	}
	while(R--){
		scanf("%d",&G),sv=0;
		for(int i=1;i<=G;++i)scanf("%d",&tmp),sv^=sg[tmp];
		printf("%d ",!!sv);
	}
	return 0;
}