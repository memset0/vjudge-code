#include<bits/stdc++.h>
using namespace std;
int t;
struct Date{
	int y,m,d;
	inline bool operator<(const Date &rhs)const{
		return y==rhs.y?(m==rhs.m?d<rhs.d:m<rhs.m):y<rhs.y;
	}
	inline bool verify()const{
		int s=y*10000+m*100+d;
		if(s%1000==202)return true;
		if(s/10%1000==202)return true;
		if(s/100%1000==202)return true;
		if(s/1000%1000==202)return true;
		if(s/10000%1000==202)return true;
		if(s/100000%1000==202)return true;
		if(s/1000000%1000==202)return true;
		return false;
	}
	inline int dayLimit()const{
		if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
			return 31;
		}
		if(m==4||m==6||m==9||m==11){
			return 30;
		}
		if(y%4==0&&(y%100!=0||y%400==0)){
			return 29;
		}
		return 28;
	}
	inline void next(){
		d++;
		if(d>dayLimit()){
			d=1;
			++m;
			if(m==13){
				m=1;
				++y;
			}
		}
	}
}s,e;
vector<Date> vec;
int main(){
#ifdef memset0
//	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	vec.push_back({999,12,31});
	vec.push_back({10000,1,1});
	Date s={1000,1,1};
	Date e={10000,1,1};
	while(s<e){
		if(s.verify()){
			vec.push_back(s);
		}
//		if(s.y==2020){
//			cerr<<s.y<<" "<<s.m<<" "<<s.d<<endl;
//		}
		s.next();
	}
//	cerr<<vec.size()<<endl;
	cin>>t;
	while(t--){
		cin>>s.y>>s.m>>s.d>>e.y>>e.m>>e.d;
		auto l=lower_bound(vec.begin(),vec.end(),s);
		auto r=--upper_bound(vec.begin(),vec.end(),e);
		if(l<=r){
			cout<<(r-l+1)<<endl;
		}else{
			cout<<0<<endl;
		}
	}
}