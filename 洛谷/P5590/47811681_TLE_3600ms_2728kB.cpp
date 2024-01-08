// std 9->8

#include<bits/stdc++.h>
const int N=1e4+10;
struct edge{
	int u,v;
	edge(){}
	edge(int x,int y){u=x,v=y;}
};
struct graph{
	int nod;
	std::vector<edge> e;
	graph(){nod=0,e.clear();}
	graph(int n,std::vector<std::pair<int,int>> q){
		nod=n;
		for(auto it:q)e.push_back(edge(it.first,it.second));
	}
	void clear(){nod=0,e.clear();}
	void output(){
		printf("%d %d\n",nod,(int)e.size());
		for(auto it:e)printf("%d %d\n",it.u,it.v);
	}
	void bfs(int s,bool *vis,std::vector<int> *G){
		static std::queue<int> q; memset(vis,0,nod+1);
		vis[s]=1,q.push(s);
		while(q.size()){
			int u=q.front(); q.pop();
			for(auto v:G[u])if(!vis[v])vis[v]=1,q.push(v);
		}
	}
	bool bfs2(int s,bool *vis,std::vector<int> *G){
		static std::queue<int> q; memset(vis,0,nod+1); while(q.size())q.pop();
		vis[s]=1,q.push(s);
		while(q.size()){
			int u=q.front(); q.pop();
			for(auto v:G[u]){
				if(vis[v])return false;
				vis[v]=1,q.push(v);
			}
		}
		return true;
	}
	bool check_legal(int flag){
		if(flag&&rand()%50==0)return true;
		static bool fl[N],fl1[N],fl2[N];
		static std::vector<int> G[N],G1[N],G2[N];
		for(int i=1;i<=nod;i++)G[i].clear(),G1[i].clear(),G2[i].clear();
		for(auto it:e){
			G1[it.u].push_back(it.v);
			G2[it.v].push_back(it.u);
		}
		bfs(1,fl1,G1),bfs(nod,fl2,G2);
		// fprintf(stderr,"check legal : %d\n",nod);
		// for(int i=1;i<=nod;i++)fprintf(stderr,"%d%c",fl1[i]," \n"[i==nod]);
		// for(int i=1;i<=nod;i++)fprintf(stderr,"%d%c",fl2[i]," \n"[i==nod]);
		for(int i=1;i<=nod;i++)fl[i]=fl1[i]&&fl2[i];
		if(!fl[1]||!fl[nod])return false;
		for(auto it:e){
			if(fl[it.u]&&fl[it.v])G[it.u].push_back(it.v);
		}
		// for(int i=1;i<=nod;i++)for(int j:G[i])fprintf(stderr,"> %d %d\n",i,j);
		return bfs2(1,fl1,G);
	}
	void random_shuffle(){
		if(nod<=2)return;
		std::vector<int> id(nod-2);
		for(int i=0;i<nod-2;i++)id[i]=i;
		std::random_shuffle(id.begin(),id.end());
		for(auto &it:e)it.u=id[it.u-2]+2,it.v=id[it.v-2]+2;
		std::random_shuffle(e.begin(),e.end());
	}
	void merge_graph(const graph &other){
		for(auto it:other.e)e.push_back(edge(it.u+nod,it.v+nod));
		e.push_back(edge(nod,nod+1)),nod+=other.nod;
	}
};
std::vector<graph> seed={
	{2,{{1,2}}},
	{3,{{1,2},{2,3},{1,3}}},
	{4,{{1,2},{2,3},{3,4},{1,4}}},
	{5,{{1,2},{2,3},{3,4},{4,5},{1,5}}},
	{8,{{1,2},{2,3},{3,4},{2,4},{1,5},{5,6},{5,7},{6,7},{4,8},{7,8}}},
	{10,{{1,2},{2,3},{3,4},{2,4},{1,5},{5,6},{5,7},{6,7},{4,10},{7,10},{1,8},{8,9},{9,10}}},
	{10,{{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{1,10}}},
	{10,{{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{1,7}}},
	{8,{{1,2},{2,8},{1,3},{3,4},{4,8},{1,5},{5,6},{6,7},{7,8}}},
	{2,{{1,2}}},
	{2,{{1,2}}},
	{2,{{1,2}}},
	{2,{{1,2}}},
};
graph random_graph(int ln,int lm,int id){
	graph cur;
	if(rand()&1){
		ln=std::min(20+rand()%10,rand()%ln+1),lm=std::min(40+rand()%20,std::min(rand()%lm+1,ln*(ln-1)/2));
		fprintf(stderr,"> random graph %d %d\n",ln,lm);
		do{
			static std::set<std::pair<int,int>> set; set.clear();
			cur.nod=ln,cur.e.resize(lm);
			for(int u,v,i=0;i<cur.e.size();i++){
				do{
					u=rand()%cur.nod+1,v=rand()%cur.nod+1;
				}while(u==v||set.count(std::make_pair(u,v)));
				cur.e[i]=edge(u,v);
				set.insert(std::make_pair(u,v));
			}
		}while(!cur.check_legal(id%10==9));
	}else{
		cur=seed[rand()%seed.size()];
		if(id%10==8&&rand()%3==0){
			return (graph){11,{{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{1,11}}};
		}
	}
	return cur;
}
graph build_graph(int n,int m,int id,int flag){
	if(id<10)return seed[id];
	graph cur=random_graph(n,m,flag),nxt;
	while(nxt=random_graph(n,m,flag),cur.nod+nxt.nod<=n&&cur.e.size()+nxt.e.size()<=m)
		cur.merge_graph(nxt);
	return cur;
}
int main(){
	srand(20040725);
	// system("mkdir ./data");
	// system("g++ ./std.cpp -o ./std -std=c++11 -O2");
	for(int i=0;i<30;i++){
		fprintf(stderr,"====== %d ======\n",i);
		auto input_file="data/car"+std::to_string(i)+".in";
		auto output_file="data/car"+std::to_string(i)+".out";
		freopen(input_file.c_str(),"w",stdout);
		graph cur;
		if(i/10==0)cur=build_graph(10,15,i,i);
		if(i/10==1)cur=build_graph(300,1000,i,i);
		if(i/10==2)cur=build_graph(10000,20000,i,i);
		// cur.random_shuffle();
		cur.output();
		fclose(stdout);
		system(("./std<"+input_file+">"+output_file).c_str());
	}
}