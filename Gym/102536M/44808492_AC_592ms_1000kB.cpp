#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
int T,r,c,nx,ny,sx,sy;
char get_move(const pii &a,const pii &b){
	if(a.first-1==b.first)return 'U';
	if(a.first+1==b.first)return 'D';
	if(a.second-1==b.second)return 'L';
	if(a.second+1==b.second)return 'R';
}
vector<pii> solve_even(int n,int m){
	bool fl=false;
	if(n&1){
		fl=true;
		swap(n,m);
	}
	vector<pii> res;
	res.emplace_back(1,1);
	for(int i=1;i<=n;i+=2){
		for(int j=2;j<=m;j++)res.emplace_back(i,j);
		for(int j=m;j>=2;j--)res.emplace_back(i+1,j);
	}
	for(int i=n;i>=2;i--){
		res.emplace_back(i,1);
	}
	if(fl){
		for(auto &it:res)swap(it.first,it.second);
	}
	return res;
}
void Go(char c){
	if(c=='L')--ny;
	if(c=='R')++ny;
	if(c=='U')--nx;
	if(c=='D')++nx;
	putchar(c);
}
void Dash(char x,int dest){
	if(x=='L'||x=='R'){
		while(ny!=dest)Go(x);
	}else{
		while(nx!=dest)Go(x);
	}
}
void Move(int x,char l,char _r,char u,char d){
	if(x!=1&&x!=c){
		for(int i=x+1;i<=c;++i)putchar(_r);
		putchar(d);
		for(int i=c;i>x;--i)putchar(l);
		for(int i=x;i>1;i-=2){
			putchar(l),putchar(u),putchar(l),putchar(d);
		}
		for(int i=3;i<=r;++i){
			putchar(d);
			for(int j=1;j<c;++j)putchar(i&1?_r:l);
		}
	}else{
		if(x==c)x=1,swap(l,_r);
		for(int i=1;i<=r;++i){
			if(i!=1)putchar(d);
			for(int j=1;j<c;++j)putchar(i&1?_r:l);
		}
	}
	puts("");
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d",&r,&c,&nx,&ny);
		if(r==1){
			if(ny!=1&&ny!=c){
				puts("IMPOSSIBLE");
				continue;
			}
			if(ny==1)Dash('R',c);
			else Dash('L',1);
			putchar('\n');
			continue;
		}
		if(c==1){
			if(nx!=1&&nx!=r){
				puts("IMPOSSIBLE");
				continue;
			}
			if(nx==1)Dash('D',r);
			else Dash('U',1);
			putchar('\n');
			continue;
		}
		if((r&1)&&(c&1)){
			if((nx^ny)&1){
				puts("IMPOSSIBLE");
				continue;
			}
			if(nx==1){
				Move(ny,'L','R','U','D');
				continue;
			}
			if(nx==r){
				Move(ny,'L','R','D','U');
				continue;
			}
			if(ny==1){
				swap(r,c);
				Move(nx,'U','D','L','R');
				continue;
			}
			if(ny==c){
				swap(r,c);
				Move(nx,'U','D','R','L');
				continue;
			}
			sx=nx,sy=ny;
			if(!(nx&1)){
				for(int i=sy;i<=c;i+=2){
					if(i!=sy)Go('R');
					Dash('U',1),Go('R'),Dash('D',sx);
				}
				Dash('D',r),Dash('L',1);
				for(int i=r;i>sx+1;i-=2){
					Go('U'),Dash('R',c-1),Go('U'),Dash('L',1);
				}
				Dash('U',1);
				for(int i=1;i+2<sy;i+=2){
					Go('R'),Dash('D',sx),Go('R'),Dash('U',1);
				}
			}else{
				for(int i=sy;i<c;i+=2){
					Go('R'),Dash('U',1),Go('R'),Dash('D',r-1);
				}
				Go('D'),Dash('L',sy+1),Dash('U',sx+1),Go('L'),Dash('D',r);
				Dash('L',1),Dash('U',1);
				for(int i=1;i<sy-2;i+=2){
					Go('R'),Dash('D',r-1),Go('R'),Dash('U',1);
				}
				Go('R');
				for(int i=1;i<sx-1;i+=2){
					Go('R'),Go('D'),Go('L'),Go('D');
				}
				Dash('D',r-1);
			}
			putchar('\n');
		}else{
			auto v=solve_even(r,c);
			for(int i=0;i<v.size();i++)
				if(v[i].first==nx&&v[i].second==ny){
					vector<pii> w;
					for(int j=i;j<v.size();j++)w.push_back(v[j]);
					for(int j=0;j<i;j++)w.push_back(v[j]);
					// for(auto x:w)cerr<<"> "<<x.first<<" "<<x.second<<endl;
					for(int i=1;i<w.size();i++)putchar(get_move(w[i-1],w[i]));
					break;
				}
			putchar('\n');
		}
	}
	return 0;
}
/*
4
5 3 3 1
5 3 3 3
5 3 2 2
5 5 3 3
*/