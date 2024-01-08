#include<bits/stdc++.h>
#define opp(x) (x&1?x+1:x-1)
using namespace std;
const int N=1e5,Q=3e5;
int T,n,k,rem,n2,n3,p,sz[Q+10],id;
int ind[Q+10],qi[N+10];
int pos(int x,int y){
	if(x==2)return(y<<1)-1;
	return n-y*3+1;
}
void Allo(int x){
	ind[T]=x,qi[x]=T;
	printf("A %d\n",x);
	fflush(stdout);
}
void Move(int x,int y){
	ind[qi[x]]=qi[y],qi[y]=qi[x];
	printf("M %d %d\n",x,y);
	fflush(stdout);
}
void Done(){
	printf("D\n");
	fflush(stdout);
}
void Shift(int x,int y){
	if(x==y)return;
	if(x==p){
		Move(x,y),p=y;
		return;
	}
	if(sz[qi[x]]==1)Move(x,y),Move(x+1,y+1);
	else Move(x,y);
}
int main(){
	scanf("%d",&n);
	for(T=1;;++T){
		scanf("%d",&k);
		if(!k)break;
		if(k>0){
			sz[T]=k;
			if(k==3)Allo(pos(3,++n3));
			else if(k==2)Allo(pos(2,++n2));
			else if(p)Allo(p+1),p=0;
			else Allo(pos(2,++n2)),p=pos(2,n2);
		}else{
			k=-k,id=ind[k],k=sz[k];
			if(k==3){
				if(id==pos(3,n3))Done();
				else Move(pos(3,n3),id),Done();
				--n3;
			}else if(k==2){
				if(id==pos(2,n2))Done();
				else Shift(pos(2,n2),id),Done();
				--n2;
			}else{
				if(p==id)Shift(pos(2,n2),id),p=0,--n2,Done();
				else if(p){
					if(p==pos(2,n2))Move(p,id),p=0,--n2,Done();
					else if(sz[qi[pos(2,n2)]]==2){
						Move(opp(id),p+1);
						Move(pos(2,n2),id);
						--n2,p=0,Done();
					}else{
						Move(pos(2,n2),p+1),Move(pos(2,n2)+1,id);
						--n2,p=0;
						Done();
					}
				}else{
					if(id&1)Move(id+1,id),p=id;
					else p=opp(id);
					Done();
				}
			}
		}
	}
	return 0;
}