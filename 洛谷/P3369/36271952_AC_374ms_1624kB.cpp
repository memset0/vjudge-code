#include<bits/stdc++.h>
const int N=1e5+10;
int n,Q,o,v,x,y,z,rt,rnd[N],val[N],siz[N],ch[N][2];
inline void maintain(int u){siz[u]=siz[ch[u][0]]+siz[ch[u][1]]+1;}
int merge(int x,int y){
	if(!x||!y)return x|y;
	if(rnd[x]<rnd[y]){
		return ch[y][0]=merge(x,ch[y][0]),maintain(y),y;
	}else{
		return ch[x][1]=merge(ch[x][1],y),maintain(x),x;
	}
}
void split(int u,int k,int &x,int &y){
	if(!u){x=y=0; return;}
	if(k<val[u]){
		y=u,split(ch[y][0],k,x,ch[y][0]);
	}else{
		x=u,split(ch[x][1],k,ch[x][1],y);
	}
	maintain(u);
}
int kth(int u,int k){
	if(k<=siz[ch[u][0]])return kth(ch[u][0],k);
	if(k==siz[ch[u][0]]+1)return val[u];
	return kth(ch[u][1],k-siz[ch[u][0]]-1);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(srand(20030417),scanf("%d",&Q);Q--;)switch(scanf("%d%d",&o,&v),o){
		case 1:rnd[++n]=rand(),val[n]=v,siz[n]=1,split(rt,v,x,y),rt=merge(x,merge(n,y));break;
		case 2:split(rt,v-1,x,y),split(y,v,y,z),y=merge(ch[y][0],ch[y][1]),rt=merge(x,merge(y,z));break;
		case 3:split(rt,v-1,x,y),printf("%d\n",siz[x]+1),rt=merge(x,y);break;
		case 4:printf("%d\n",kth(rt,v));break;
		case 5:split(rt,v-1,x,y),printf("%d\n",kth(x,siz[x])),rt=merge(x,y);break;
		case 6:split(rt,v,x,y),printf("%d\n",kth(y,1)),rt=merge(x,y);break;
	}
}