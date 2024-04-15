// my ac code got TLE

#include<bits/stdc++.h>
using namespace std; 
typedef long long ll;
const int INF=0x3f3f3f3f;
const int N=5e5+5;
int n,m;
int min_gap=INF,min_sort_gap=INF;
int ans[N];
char x[20];
void readstring(){
	int len=0;char u=0;while(u!='_'&&(u<'A'||u>'Z'))u=getchar();
	while(u=='_'||(u>='A'&&u<='Z')){x[++len]=u;u=getchar();}
	return;
}
struct que{
	int opt,sum;
	int id;
}oper[N];int cnt;
int l[N],r[N];

priority_queue<int,vector<int>,greater<int> >Q,del;
int tot;
typedef pair<int,int> pii;
pii sum[N*2];
int toid[N*2];
int lxx[N*2],rxx[N*2];
priority_queue<int,vector<int>,greater<int> >Q2,del2;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)ans[i]=-1;
	for(int i=1;i<=n;i++){
		scanf("%d",&l[i]);r[i]=l[i];
		if(i>1)Q.push(abs(r[i-1]-l[i]));
		//if(i-1)min_gap=min(min_gap,abs(r[i-1]-l[i]));
		sum[++tot]=pii(l[i],0);
	}
	for(int i=1;i<=m;i++){
		readstring();
		if(x[1]=='I'){
			int a,b;scanf("%d%d",&a,&b);
			oper[++cnt]=(que){0,b,i};
			del.push(abs(l[a+1]-r[a]));
			Q.push(abs(r[a]-b));r[a]=b;
			if(a+1<=n)Q.push(abs(l[a+1]-r[a]));
			sum[++tot]=pii(b,i);
		}else if(x[5]=='G'){
			while(true){
				if(del.empty()){ans[i]=Q.top();break;}
				if(Q.top()!=del.top()){ans[i]=Q.top();break;}
				Q.pop(),del.pop();
			}
		}else{
			oper[++cnt]=(que){1,0,i};
		}
	}
	sort(sum+1,sum+tot+1);
	for(int i=1;i<=tot;i++){
		toid[sum[i].second]=i;
		if(i>1){
			Q2.push(abs(sum[i].first-sum[i-1].first));
		}
		lxx[i]=i-1,rxx[i]=i+1;
	}
	for(int i=cnt;i;i--){
		if(oper[i].opt==0){
			int id=toid[oper[i].id];
			//cout<<oper[i].id<<" "<<id<<endl;
			if(lxx[id]>0)del2.push(abs(sum[lxx[id]].first-sum[id].first));
			if(rxx[id]<=tot)del2.push(abs(sum[rxx[id]].first-sum[id].first));
			rxx[lxx[id]]=rxx[id];lxx[rxx[id]]=lxx[id];
			if(rxx[id]<=tot&&lxx[id]>0)Q2.push(abs(sum[lxx[id]].first-sum[rxx[id]].first));
		}else{
			while(true){
				if(del2.empty()){ans[oper[i].id]=Q2.top();break;}
				if(Q2.top()!=del2.top()){ans[oper[i].id]=Q2.top();break;}
				Q2.pop(),del2.pop();
			}
		}
	}
	for(int i=1;i<=m;i++)if(~ans[i]){
		printf("%d\n",ans[i]);
	}
}