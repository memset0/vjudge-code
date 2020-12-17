#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native") 
#include<bits/stdc++.h>
using namespace std;
inline string operator+(const string &a,int b){return a+to_string(b);}
inline string operator+(int a,const string &b){return to_string(a)+b;}
template<class T> void trans(int x,T *k){
	switch(x){
		case 0:break;
		case 1:swap(k[1],k[2]);break;
		case 2:swap(k[0],k[1]);break;
		case 3:swap(k[0],k[1]),swap(k[1],k[2]);break;
		case 4:swap(k[1],k[2]),swap(k[0],k[1]);break;
		case 5:swap(k[1],k[2]),swap(k[0],k[1]),swap(k[1],k[2]);break;
	}
}
template<class T> void transRev(int x,T *k){
	switch(x){
		case 0:break;
		case 1:swap(k[1],k[2]);break;
		case 2:swap(k[0],k[1]);break;
		case 3:swap(k[1],k[2]),swap(k[0],k[1]);break;
		case 4:swap(k[0],k[1]),swap(k[1],k[2]);break;
		case 5:swap(k[1],k[2]),swap(k[0],k[1]),swap(k[1],k[2]);break;
	}
}
void transText(int x,string op,int bas,vector<string> &out){
	auto swap=[&](int x,int y){
		out.push_back(op+" "+(x+bas)+" "+(y+bas));
	};
	switch(x){
		case 0:break;
		case 1:swap(1,2);break;
		case 2:swap(0,1);break;
		case 3:swap(0,1),swap(1,2);break;
		case 4:swap(1,2),swap(0,1);break;
		case 5:swap(1,2),swap(0,1),swap(1,2);break;
	}
}
template<const int p> inline int mul(int a,int b){return (long long)a*b%p;}
template<const int p> inline int sub(int a,int b){return (a-=b)<0&&(a+=p),a;}
template<const int p> inline int add(int a,int b){return (a+=b)>=p&&(a-=p),a;}
// struct hash_t{
// 	static const int p1=998244353,p2=1e9+7;
// 	int x,y;
// 	inline hash_t(int x=0,int y=0):x(x),y(y){}
// 	inline bool operator<(const hash_t &rhs)const{return x==rhs.x?y<rhs.y:x<rhs.x;}
// 	inline hash_t operator+(const hash_t &rhs)const{return {add<p1>(x,rhs.x),add<p2>(y,rhs.y)};}
// 	inline hash_t operator-(const hash_t &rhs)const{return {sub<p1>(x,rhs.x),sub<p2>(y,rhs.y)};}
// 	inline hash_t operator*(const hash_t &rhs)const{return {mul<p1>(x,rhs.x),mul<p2>(y,rhs.y)};}
// };
// const hash_t bas={131131,131131},val[]={{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9}};
struct hash_t{
	static const int p=998244353;
	int x;
	inline hash_t(int x=0):x(x){}
	inline bool operator<(const hash_t &rhs)const{return x<rhs.x;}
	inline hash_t operator+(const hash_t &rhs)const{return {add<p>(x,rhs.x)};}
	inline hash_t operator-(const hash_t &rhs)const{return {sub<p>(x,rhs.x)};}
	inline hash_t operator*(const hash_t &rhs)const{return {mul<p>(x,rhs.x)};}
};
const hash_t bas={131131},val[]={{1},{2},{3},{4},{5},{6},{7},{8},{9}};
struct move_t{
	int i,a,b,c,j,d,e,f;
	vector<string> movement(){
		vector<string> rsp;
		transText(i,"R",1,rsp);
		transText(a,"r",1,rsp);
		transText(b,"r",4,rsp);
		transText(c,"r",7,rsp);
		transText(j,"C",1,rsp);
		transText(d,"c",1,rsp);
		transText(e,"c",4,rsp);
		transText(f,"c",7,rsp);
		return rsp;
	}
};
struct sudoku{
	int map[9][9];
	inline int* operator[](size_t k){return map[k];}
	inline const int* operator[](size_t k)const{return map[k];}
	void input(){
		static string str;
		for(int i=0;i<9;i++){
			cin>>str;
			for(int j=0;j<9;j++){
				map[i][j]=str[j]=='.'?0:str[j]-'0';
			}
		}
	}
	sudoku flip(){
		sudoku rsp;
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				rsp[i][j]=map[j][i];
		return rsp;
	}
	sudoku apply(const move_t &x){
		int row[3][3]={{0,1,2},{3,4,5},{6,7,8}};
		int col[3][3]={{0,1,2},{3,4,5},{6,7,8}};
		trans(x.i,row),trans(x.a,row[0]),trans(x.b,row[1]),trans(x.c,row[2]);
		trans(x.j,col),trans(x.d,col[0]),trans(x.e,col[1]),trans(x.f,col[2]);
		// printf("%d %d %d %d %d %d %d %d %d\n",row[0][0],row[0][1],row[0][2],row[1][0],row[1][1],row[1][2],row[2][0],row[2][1],row[2][2]);
		// printf("%d %d %d %d %d %d %d %d %d\n",col[0][0],col[0][1],col[0][2],col[1][0],col[1][1],col[1][2],col[2][0],col[2][1],col[2][2]);
		sudoku rsp;
		for(int x=0;x<3;x++)
			for(int i=0;i<3;i++)
				for(int y=0;y<3;y++)
					for(int j=0;j<3;j++){
						rsp[x*3+i][y*3+j]=map[row[x][i]][col[y][j]];
					}
		return rsp;
	}
	hash_t hash(){
		hash_t rsp;
		int c=0,p[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++){
				rsp=rsp*bas;
				if(map[i][j]){
					if(p[map[i][j]-1]==-1){
						p[map[i][j]-1]=c++;
					}
					rsp=rsp+val[p[map[i][j]-1]];
				}
			}
		return rsp;
	}
	std::map<hash_t,move_t> init(){
		std::map<hash_t,move_t> all;
		int row[3][3]={{0,1,2},{3,4,5},{6,7,8}};
		int col[3][3]={{0,1,2},{3,4,5},{6,7,8}};
		for(int i=0;i<6;i++){
			trans(i,row);
			for(int a=0;a<6;a++){
				trans(a,row[0]);
				for(int b=0;b<6;b++){
					trans(b,row[1]);
					for(int c=0;c<6;c++){
						trans(c,row[2]);
						for(int j=0;j<6;j++){
							trans(j,col);
							for(int d=0;d<6;d++){
								trans(d,col[0]);
								for(int e=0;e<6;e++){
									trans(e,col[1]);
									for(int f=0;f<6;f++){
										trans(f,col[2]);
										move_t mov={i,a,b,c,j,d,e,f};
										sudoku nxt;
										for(int x=0;x<3;x++)
											for(int i=0;i<3;i++)
												for(int y=0;y<3;y++)
													for(int j=0;j<3;j++){
														nxt[x*3+i][y*3+j]=map[row[x][i]][col[y][j]];
													}
										// for(int i=0;i<9;i++)for(int j=0;j<9;j++)printf("%c%c",map[i][j]?map[i][j]+'0':'.'," \n"[j==8]);puts("");
										// for(int i=0;i<9;i++)for(int j=0;j<9;j++)printf("%c%c",nxt[i][j]?nxt[i][j]+'0':'.'," \n"[j==8]);puts("");
										hash_t hsh=nxt.hash();
										all[hsh]=mov;
										// printf("%d(%d %d %d) %d(%d %d %d) => %d %d\n",i,a,b,c,j,d,e,f,hsh.x,hsh.y);
										transRev(f,col[2]);
									}
									transRev(e,col[1]);
								}
								transRev(d,col[0]);
							}
							transRev(j,col);
						}
						transRev(c,row[2]);
					}
					transRev(b,row[1]);
				}
				transRev(a,row[0]);
			}
			transRev(i,row);
		}
		return all;
	}
};
vector<string> movement(const sudoku &a,const sudoku &b){
	// for(int i=0;i<9;i++)for(int j=0;j<9;j++)printf("%d%c",a[i][j]," \n"[j==8]);
	// for(int i=0;i<9;i++)for(int j=0;j<9;j++)printf("%d%c",b[i][j]," \n"[j==8]);
	int p[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			assert(!((!!a[i][j])^(!!b[i][j])));
			if(a[i][j]&&b[i][j]){
				p[a[i][j]-1]=b[i][j]-1;
			}
		}
	vector<string> rsp;
	for(int i=0;i<9;i++)
		if(p[i]!=-1&&p[i]!=i){
			rsp.push_back(string("D ")+(i+1)+" "+(p[i]+1));
			swap(p[i],p[p[i]]);
		}
	return rsp;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#else
	freopen("intellectual.in","r",stdin);
	freopen("intellectual.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	vector<sudoku> a(n);
	vector<sudoku> b(n);
	for(int i=0;i<n;i++){
		a[i].input();
		b[i]=a[i].flip();
	}
	for(int i=0;i+1<n;i++){
		auto all=a[i].init();
		for(int j=i+1;j<n;j++){
			vector<string> ans,rhs;
			// printf(">> %d %d\n",i,j);
			if(all.count(a[j].hash())){
				ans=all[a[j].hash()].movement();
				// hash_t tmp=a[i].apply(all[a[j].hash()]).hash();
				// printf("%d %d %d %d\n",tmp.x,tmp.y,a[j].hash().x,a[j].hash().y);
				rhs=movement(a[i].apply(all[a[j].hash()]),a[j]);
			}else if(all.count(b[j].hash())){
				ans=all[b[j].hash()].movement();
				ans.push_back("F");
				// hash_t tmp=a[i].apply(all[b[j].hash()]).flip().hash();
				// printf("%d %d %d %d\n",tmp.x,tmp.y,a[j].hash().x,a[j].hash().y);
				rhs=movement(a[i].apply(all[b[j].hash()]).flip(),a[j]);
			}
			if(rhs.size()){
				ans.insert(ans.end(),rhs.begin(),rhs.end());
			}
			if(ans.size()){
				cout<<"YES"<<endl;
				cout<<ans.size()<<endl;
				for(const string &line:ans){
					cout<<line<<endl;
				}
			}else{
				cout<<"NO"<<endl;
			}
		}
	}
}