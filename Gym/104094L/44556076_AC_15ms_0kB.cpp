#include<bits/stdc++.h>
using namespace std;
int n,fl,ar[25],sz,st[25],mp[25],len,ml,fr[210],tmp,pos[210],ld[10];
int prt[210],pf[210],pp[210],ta[210],f3[210],tp;
vector<int>es[25][10],el[25];
void dfs(int x,int nw){
	if(nw>n)return;
	if(x>21){
		if(nw!=n)return;
		fl=1;
		return;
	}
	dfs(x+1,nw);
	if(!fl){
		ar[++sz]=x,dfs(x+1,nw+x);
		if(!fl)--sz;
	}
}
int div(vector<int>&v,int x){
	int ts=0,tv=0;
	while(ts<=x)ts+=(++tv);
	for(int i=tv;i>=1;--i)if(i!=ts-x)v.push_back(i);
	return tv-1;
}
int main(){
	scanf("%d",&n);
	//assert(n!=8);
	if(n>9||n==6){
		ar[++sz]=1,ar[++sz]=2,ar[++sz]=3;
		dfs(4,6);
		printf("%d\n",sz);
		for(int i=1,nw=1;i<=sz;++i){
			st[i]=nw,mp[ar[i]]=i;
			for(int j=1;j<=ar[i];++j)fr[nw]=i,++nw,printf("%d ",i);
		}
		printf("\n"),fflush(stdout);
		for(int i=1;i<=sz;++i){
			scanf("%d",&len);
			for(int j=0;j<len;++j)scanf("%d",&tmp),fr[tmp]=mp[len];
		}


		ml=3,el[1].push_back(1),el[2].push_back(1),el[2].push_back(1),el[3].push_back(1),el[3].push_back(1),el[3].push_back(1);
		for(int i=4;i<=sz;++i)ml=max(div(el[i],ar[i]),ml);
		printf("%d\n",ml);
		for(int i=1;i<=sz;++i){
			el[i].resize(ml);
			for(int j=0;j<ml;++j){
				for(int k=1;k<=el[i][j];++k)printf("%d ",j+1);
			}
		}
		printf("\n"),fflush(stdout);
		for(int i=1;i<=ml;++i){
			int ttl=0;
			for(int j=1;j<=sz;++j)ttl+=el[j][i-1];
			mp[ttl]=i;
		}
		for(int i=1;i<=ml;++i){
			scanf("%d",&len);
			for(int j=1;j<=len;++j)scanf("%d",&tmp),pos[tmp]=mp[len],es[fr[tmp]][mp[len]].push_back(tmp);
		}


		for(int i=1;i<=n;++i){
			if(fr[i]==1)ld[1]=i;
			if(fr[i]==2)ld[1+pos[i]]=i,pf[i]=2;
			if(fr[i]==3)ld[3+pos[i]]=i;
		}
		int nw=0;
		for(int i=1;i<=3;++i)for(int j=0;j<i;++j)pf[++nw]=i,pp[nw]=j+1,f3[nw]=nw;
		printf("%d\n",6);
		for(int i=1;i<=6;++i)printf("%d ",i);
		for(int i=4;i<=sz;++i)for(int j=0;j<ml;++j){
			for(int k=1;k<=el[i][j];++k)printf("%d ",k),++nw,pf[nw]=i,pp[nw]=j+1,f3[nw]=k;
		}
		printf("\n"),fflush(stdout);
		for(int i=1;i<=6;++i){
			scanf("%d",&len);
			for(int j=1;j<=len;++j){
				scanf("%d",&ta[j]);
				if(fr[ta[j]]<=3){
					tp=0;
					for(int k=1;k<fr[ta[j]];++k)tp+=k;
					tp+=pos[ta[j]];
				}
			}
			for(int j=1;j<=len;++j){
				for(int k=1;k<=n;++k)if(fr[ta[j]]==pf[k]&&pos[ta[j]]==pp[k]&&tp==f3[k])prt[k]=ta[j];
			}
		}
	}else{
		if(n<=4){
			for(int i=1;i<=3;++i){
				printf("2\n");
				for(int j=1;j<=n;++j)printf("%d ",1+(j==i));
				printf("\n"),fflush(stdout);
				for(int j=1;j<=2;++j){
					scanf("%d",&len);
					for(int k=1;k<=len;++k)scanf("%d",&tp);
					if(len==1)prt[i]=tp,fr[tp]=i;
				}
			}
			if(n==4)for(int i=1;i<=n;++i)if(!fr[i])prt[4]=i;
		}
		int t1,t2;
		if(n==5){
			printf("2\n1 2 2 2 2\n"),fflush(stdout);
			for(int i=1;i<=2;++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[1]);
				else{
					for(int j=1;j<=len;++j)scanf("%d",&tp);
				}
			}
			printf("2\n1 1 2 2 2\n"),fflush(stdout);
			for(int i=1;i<=2;++i){
				scanf("%d",&len);
				if(len==2){
					scanf("%d %d",&t1,&t2);
					if(t1==prt[1])prt[2]=t2;
					else prt[2]=t1;
				}else{
					for(int j=1;j<=len;++j)scanf("%d",&tp);
				}
			}
			printf("3\n1 2 1 2 3\n"),fflush(stdout);
			for(int i=1;i<=3;++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[5]);
				else{
					scanf("%d %d",&t1,&t2);
					if(t1==prt[1])prt[3]=t2;
					if(t1==prt[2])prt[4]=t2;
					if(t2==prt[1])prt[3]=t1;
					if(t2==prt[2])prt[4]=t1;
				}
			}
		}
		int a2,b2,c2;
		if(n==7){
			printf("3\n1 2 2 3 3 3 3\n"),fflush(stdout);
			for(int i=1;i<=3;++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[1]);
				else if(len==2){
					scanf("%d%d",&a2,&b2);
				}
			}
			printf("3\n1 1 2 3 3 3 3\n"),fflush(stdout);
			for(int i=1;i<=3;++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[3]);
				else if(len==2){
					scanf("%d%d",&t1,&t2);
					if(t1==prt[1])prt[2]=t2;
					else prt[2]=t1;
				}
			}
			printf("4\n1 2 3 1 2 3 4\n"),fflush(stdout);
			for(int i=1;i<=4;++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[7]);
				else{
					scanf("%d %d",&t1,&t2);
					if(t1==prt[1])prt[4]=t2;
					if(t2==prt[1])prt[4]=t1;
					if(t1==prt[2])prt[5]=t2;
					if(t2==prt[2])prt[5]=t1;
					if(t1==prt[3])prt[6]=t2;
					if(t2==prt[3])prt[6]=t1;
				}
			}
		}
		if(n==8||n==9){
			printf("3\n1 2 2 2 3 3 3 3");
			if(n==9)printf(" 3");
			printf("\n"),fflush(stdout);
			for(int i=1;i<=3;++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[1]);
				else if(len==3){
					scanf("%d%d%d",&a2,&b2,&c2);
				}else{
					for(int j=1;j<=len;++j)scanf("%d",&tp);
				}
			}
			printf("3\n1 1 2 3 1 1 2 2");
			if(n==9)printf(" 1");
			printf("\n"),fflush(stdout);
			for(int i=1;i<=3;++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[4]);
				else if(len==3){
					for(int j=1;j<=len;++j){
						scanf("%d",&tp);
						if(tp==a2||tp==b2||tp==c2)prt[3]=tp;
					}
				}else{
					for(int j=1;j<=len;++j){
						scanf("%d",&tp);
						if(tp==a2||tp==b2||tp==c2)prt[2]=tp;
					}
				}
			}
			printf("%d\n1 2 3 4 1 2 3 4",4+(n==9));
			if(n==9)printf(" 5");
			printf("\n"),fflush(stdout);
			for(int i=1;i<=4+(n==9);++i){
				scanf("%d",&len);
				if(len==1)scanf("%d",&prt[9]);
				else{
					scanf("%d%d",&t1,&t2);
					if(t1==prt[1])prt[5]=t2;
					if(t2==prt[1])prt[5]=t1;
					if(t1==prt[2])prt[6]=t2;
					if(t2==prt[2])prt[6]=t1;
					if(t1==prt[3])prt[7]=t2;
					if(t2==prt[3])prt[7]=t1;
					if(t1==prt[4])prt[8]=t2;
					if(t2==prt[4])prt[8]=t1;
				}
			}
		}
	}
	for(int i=1;i<=n;++i)printf("%d ",prt[i]);
	printf("\n"),fflush(stdout);
	return 0;
}