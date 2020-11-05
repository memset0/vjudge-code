#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
int T,l,n,m;
bool check(const std::vector<std::pair<int,bool>> &p){
	for(int i=0;i+2<p.size();i++)
		if(!p[i].second&&!p[i+1].second&&!p[i+2].second)
			return true;
	
	return false;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;){
		std::vector<int> a,b;
		std::vector<std::pair<int,bool>> p;
		read(l),read(n),read(m);
		for(int x,i=0;i<n;i++)read(x),a.push_back(x),p.push_back({x,0});
		for(int x,i=0;i<m;i++)read(x),b.push_back(x),p.push_back({x,1});
		if(n==1&&m==1){puts("R"); continue;}
		if(n==2&&m==1){puts("B"); continue;}
		if(n==1&&m==2){puts("C"); continue;}
		std::sort(p.begin(),p.end());
		bool fl0=check(p);
		for(auto &it:p)it.second^=1;
		bool fl1=check(p);
		if(fl0&&fl1)puts("R");
		else if(fl0)puts("B");
		else if(fl1)puts("C");
		else{
			std::vector<int> nim;
			if(p.front().second^p.back().second)
				nim.push_back(p.front().first+l-p.back().first-1);
			for(int i=0;i<n+m;i++)
				if(p[i].second^p[i+1].second)
					nim.push_back(p[i+1].second-p[i].second-1);
			int ans=std::accumulate(nim.begin(),nim.end(),0,[](int a,int b){return a^b;});
			puts(ans?"B":"C");
		}
	}
}