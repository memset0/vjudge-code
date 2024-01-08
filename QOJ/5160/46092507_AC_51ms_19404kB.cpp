#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int n,K,tt,u,v,slf[N+10],del[N+10],t1[N+10],t2[N+10],fl,tmp,ls,td;
set<int>s[N+10];
set<int>::iterator it,nx;
int nex(int x,int y){
	return t1[y]==x?t2[y]:t1[y];
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&u,&v);
		if(u==v)slf[u]=1;
		else{
			s[u].insert(v),s[v].insert(u);
		}
	}
	for(int i=1;i<=K;++i)if(!slf[i]&&((s[i].size()==1&&!del[*s[i].begin()])||!s[i].size())){
		del[i]=1,++tt;
		//cout<<"DEL "<<i<<"\n";
	}
	for(int i=1;i<=K;++i)if(!del[i]){
		it=s[i].begin();
		while(it!=s[i].end()){
			nx=it,++nx;
			if(del[*it])s[i].erase(it);
			else{
				if(t1[i]){
					if(!t2[i])t2[i]=*it;
					else return puts("impossible"),0;
				}else t1[i]=*it;
			}
			it=nx;
		}
	}
	for(int i=1;i<=K;++i)if(!del[i]&&!t2[i]){
		fl=1;
		tmp=i;
		ls=0;
		while(tmp){
			del[tmp]=1;
			++tt;
			td=tmp;
			tmp=nex(ls,tmp),ls=td;
		}
	}
	for(int i=1;i<=K;++i)if(!del[i]){
		if(fl)return puts("impossible"),0;
		ls=t1[i];
		tmp=i;
		do{
			//cout<<"TMP="<<tmp<<"\n";
			++tt;
			td=tmp;
			tmp=nex(ls,tmp),ls=td;
		}while(tmp!=i);
		//cout<<"TT="<<tt<<"\n";
		if(tt!=K)return puts("impossible"),0;
		else return puts("possible"),0;
	}
	puts("possible");
	return 0;
}
/*
7 6
2 2
3 6
1 1
1 5
4 5
6 6
6 5

5 5
1 3
1 5
2 3
2 5
3 4

6 7
1 2
2 3
3 4
4 5
3 6
6 7

6 6
1 2
1 1
2 2
3 4
3 3
4 4
*/