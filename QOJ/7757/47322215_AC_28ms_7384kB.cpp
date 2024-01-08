#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=1000;
int T,n,a[N+10],b[N+10],pos[N+10],nxt[N+10],lst[N+10],nw,t,fl;
int prt[N*N+N+10],sz,ls;
int main(){
#ifdef memset0
	//freopen(".in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i)cin>>a[i];
		for(int i=1;i<=n;++i)cin>>b[i];
		for(int i=1;i<=n;++i)pos[b[i]]=i;
		for(int i=1;i<=n;++i)nxt[a[i]]=a[i+1],lst[a[i]]=a[i-1];
		lst[a[1]]=a[n],nxt[a[n]]=a[1];
		nw=a[1];
		sz=0,ls=0;
		fl=1;
		while(1){
			if(pos[nw]<pos[nxt[nw]]||pos[nw]==n){
				prt[++sz]=1;
				if(pos[nw]==n){
					if(!fl)break;
					fl=0;
				}
				nw=nxt[nw];
			}else{
				t=nxt[nw];
				nxt[lst[t]]=nxt[t],lst[nxt[t]]=lst[t];
				nxt[t]=nw,nxt[lst[nw]]=t;
				lst[t]=lst[nw],lst[nw]=t;
				prt[++sz]=2;
				ls=sz;
				fl=1;
			}
			assert(sz-n<=n*n);
		}
		for(int i=1;i<=sz-n;++i)cout<<prt[i];
		cout<<"\n";
	}
}
/*
2
3
1 2 3
2 3 1
4
1 2 3 4
2 1 3 4
*/