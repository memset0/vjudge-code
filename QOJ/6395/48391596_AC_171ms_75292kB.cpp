#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
#define double long double
using namespace std;
enum oper{PLUS,MINUS,TIME,DIV,SIN,COS,NONE};
string name[]={"+","-","*","/","sin","cos","x"};
const int N=25;
int n;
double x[N],y[N];
double getdiff(double x,double y){
	return abs(x-y)/max<double>(1,abs(y));
}
struct func{
	oper op;
	string str;
	func *l,*r;
	pair<double,bool> calc(double x){
		if(op==NONE)return {x,false};
		if(PLUS<=op&&op<=DIV){
			auto a=l->calc(x),b=r->calc(x);
			// fprintf(stderr,"%d !! %.10Lf %d :: %.10Lf %d\n",op,a.first,a.second,b.first,b.second);
			if(a.second||b.second)return {0,true};
			if(op==DIV){
				if(abs(b.first)<0.01)return {0,true};
			}
			if(op==PLUS)a.first+=b.first;
			if(op==MINUS)a.first-=b.first;
			if(op==TIME)a.first*=b.first;
			if(op==DIV)a.first/=b.first;
			// cerr<<"! "<<a.first<<endl;
			if(isnan(a.first)||isinf(a.first)||a.first>1e50||a.first<-1e50)return {0,true};
			return a;
		}
		if(SIN<=op&&op<=COS){
			auto a=l->calc(x);
			if(a.second)return {0,true};
			a.first=op==SIN?sinl(a.first):cosl(a.first);
			if(isnan(a.first)||isinf(a.first)||a.first>1e50||a.first<-1e50)return {0,true};
			return a;
		}
		return {0,true};
	}
};
vector<func> f[10];
int main(){
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	f[0].push_back({NONE,"x",nullptr,nullptr});
	for(int k=1;k<=9;k++){
		for(oper op=PLUS;op<=DIV;op=(oper)((int)op+1)){
			for(int i=0;i<=k;i++)
				for(int j=0;j<=k;j++)
					if(i+j+2==k){
						// if(op!=MINUS&&op!=DIV&&i>j)continue;
						for(int x=0;x<f[i].size();x++)
							for(int y=0;y<f[j].size();y++){
								f[k].push_back({
									op,
									"("+f[i][x].str+")"+name[op]+"("+f[j][y].str+")",
									&f[i][x],
									&f[j][y],
								});
							}
					}
		}
		for(oper op=SIN;op<=COS;op=(oper)((int)op+1)){
			for(int x=0;x<f[k-1].size();x++){
				f[k].push_back({
					op,
					name[op]+"("+f[k-1][x].str+")",
					&f[k-1][x],
					nullptr
				});
			}
		}
		// cerr<<k<<" >> "<<f[k].size()<<endl;
		// for(auto x:f[k])cerr<<x.str<<endl;
	}
	for(int k=0;k<=9;k++)
		for(auto fc:f[k]){
			// if(fc.str!="cos(cos(((x)+(x))/(x)))")continue;
			bool ok=true;
			for(int i=1;i<=n;i++){
				auto res=fc.calc(x[i]);
				// fprintf(stderr,"%.2Lf %.2Lf => %.10Lf %d\n",x[i],y[i],res.first,res.second);
				if(res.second||isnan(res.first)||isinf(res.first)||(getdiff(res.first,y[i])>3e-4)){
					ok=false;
					break;				
				}
			}
			if(ok){
				// cerr<<"k="<<k<<endl;
				cout<<fc.str<<endl;
				return 0;
			}
		}
	assert(0);
}