#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using vi=vector<int>;
const int N=1e2+9;
int T,n;
string op;
vi p[720];
map<vi,int> mp6;
int tra[3][720],rev[3][720];
map<vi,vi> mp5;
vi discret(vi a){
	vi b=a;
	sort(all(b));
	for(int i=0;i<a.size();i++){
		a[i]=lower_bound(all(b),a[i])-b.begin();
	}
	return a;
}
vi transmit(vi a){
	sort(all(a));
	int x=0;
	for(int u:a)x^=u;
	// cerr<<"x="<<x<<" "<<p[x].size()<<endl;
	vi b[3];
	for(int i=0;i<3;i++){
		vi c;
		for(int j=0;j<6;j++)c.push_back(a[i*6+j]);
		for(int k:p[tra[i][x]]){
			b[i].push_back(c[k]);
		}
	}
	vi t;
	for(int i=20;i<a.size();i++){
		t.push_back(a[i]);
	}
	random_shuffle(all(t));
	vi c;
	c.insert(c.end(),all(b[0]));
	c.push_back(a[18]);
	c.insert(c.end(),all(b[1]));
	c.insert(c.end(),all(t));
	c.push_back(a[19]);
	c.insert(c.end(),all(b[2]));
	return c;
}
vi operator&&(const vi &a,const vi &b){
	vi c;
	for(int x:a)
		for(int y:b)
			if(x==y){
				c.push_back(x);
			}
	return c;
}
vi recover(vi a){
	vector<int> xors;
	auto calc=[&](int k,int l,int r){
		// fprintf(stderr,">>> l=%d r=%d\n",l,r);
		vi b;
		for(int i=l;i<r;i++){
			b.push_back(a[i]);
		}
		b=discret(b);
		// for(int x:b)cerr<<x<<" ";cerr<<endl;
		if(b.size()==5){
			// fprintf(stderr,"mp5::");for(int x:mp5[b])cerr<<x<<" ";cerr<<endl;
			vi t;
			for(int x:mp5[b])t.push_back(rev[k][x]);
			return t;
		}else{
			// fprintf(stderr,"mp6::%d\n",mp6[b]);
			int x=rev[k][mp6[b]];
			// xors.push_back(x);
			return vi{x};
		}
	};
	auto check=[&](int aa,int bb,int cc){
		vi u=calc(0,0,aa)&&calc(1,aa+1,aa+bb+1)&&calc(2,a.size()-cc,a.size());
		if(u.size()){
			xors.insert(xors.end(),all(u));
			// sort(all(u)),u.erase(unique(all(u)),u.end());
			// fprintf(stderr,"! x=%d u[0]=%d u.size()=%d\n",x,u[0],(int)u.size());
			// for(int x:u)cerr<<"u="<<x<<endl;
			// assert(u.size()==1);
			// assert(x==-1||x==u[0]);
			// x=u[0];
		}
	};
	if(a.size()>19)check(6,6,6);
	check(5,6,6);
	check(6,5,6);
	check(6,6,5);
	assert(xors.size()!=0);
	// cerr<<"xors: ";for(int x:xors)cerr<<x<<" ";cerr<<endl;
	map<int,int> p;
	for(int x:xors)p[x]++;
	int x=-1,c=-1;
	for(const auto &it:p){
		if(it.second>c){
			x=it.first;
			c=it.second;
		}
	}
	for(int u:a)x^=u;
	// cerr<<"! x="<<x<<endl;
	if(x){
		assert(1<=x&&x<=500);
		a.push_back(x);
	}
	sort(all(a));
	return a;
}
int main(){
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	vi id={0,1,2,3,4,5};
	for(int k=0;k<3;k++){
		for(int i=0;i<720;i++){
			tra[k][i]=i;
		}
		random_shuffle(tra[k],tra[k]+720);
		for(int i=0;i<720;i++){
			rev[k][tra[k][i]]=i;
		}
	}
	int cnt=0;
	do{
		// cerr<<cnt<<endl;
		p[cnt]=id;
		mp6[id]=cnt;
		for(int i=0;i<6;i++){
			vi b;
			for(int j=0;j<6;j++)
				if(i!=j){
					b.push_back(id[j]);
				}
			b=discret(b);
			// for(int x:b)cerr<<x<<" ";cerr<<endl;
			auto it=mp5.find(b);
			if(it==mp5.end()){
				mp5[b]={cnt};
			}else{
				if(find(all(it->second),cnt)==it->second.end()){
					it->second.push_back(cnt);
				}
			}
		}
		cnt++;
	}while(next_permutation(all(id)));
	cin>>op>>T;
	if(op=="transmit"){
		while(T--){
			cin>>n;
			vi a(n);
			for(int i=0;i<n;i++)cin>>a[i];
			vi b=transmit(a);
			for(int i=0;i<b.size();i++)cout<<b[i]<<" \n"[i+1==b.size()];

			// sort(all(a));
			// assert(recover(b)==a);
			// for(int i=0;i<b.size();i++){
			// 	vi c;
			// 	for(int j=0;j<b.size();j++)
			// 		if(i!=j){
			// 			c.push_back(b[j]);
			// 		}
			// 	vi d=recover(c);
			// 	for(int x:d)cerr<<x<<" ";cerr<<endl;
			// 	assert(d==a);
			// }
		}
	}else{
		while(T--){
			cin>>n;
			vi b(n);
			for(int i=0;i<n;i++)cin>>b[i];
			vi a=recover(b);
			for(int i=0;i<a.size();i++)cout<<a[i]<<" \n"[i+1==a.size()];
		}
	}
}