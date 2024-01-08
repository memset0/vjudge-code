#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using V=long double;
const int N=2e5+9;
const V eps=1e-6,T=10,L=1e9+T*T;
int n;
int sgn(V x){
	if(fabsl(x)<eps)return 0;
	return x<0?-1:1;
}
bool mem_equal(V x,V y){
	return fabsl(x-y)<eps*max(fabsl(x),fabsl(y));
}
bool mem_less(V x,V y){
	if(mem_equal(x,y))return false;
	return x<y;
}
bool mem_greater(V x,V y){
	if(mem_equal(x,y))return false;
	return x>y;
}
struct point{
	V x,y;
	friend V operator^(const point &a,const point &b){return a.x*b.y-a.y*b.x;}
	friend V operator*(const point &a,const point &b){return a.x*b.x+a.y*b.y;}
	friend inline point operator+(const point &a,const point &b){return {a.x+b.x,a.y+b.y};}
	friend inline point operator-(const point &a,const point &b){return {a.x-b.x,a.y-b.y};}
};
bool check_less(const point &a,const point &b){
	return mem_less(a.x*b.y,a.y*b.x);
}
bool check_greater(const point &a,const point &b){
	return mem_greater(a.x*b.y,a.y*b.x);
}
struct line{
	point s,e;
	V angle;
	line(){}
	int x,y;
	line(point s,point e,int _x=-1,int _y=-1):s(s),e(e){
		x=_x,y=_y;
		angle=atan2l(e.y-s.y,e.x-s.x);
	}
	inline bool operator<(const line &rhs)const{
		return angle<rhs.angle;
	}
	point crosspoint(const line &v){
		V a1=(v.e-v.s)^(s-v.s);
		V a2=(v.e-v.s)^(e-v.s);
		return point{
			(s.x*a2-e.x*a1)/(a2-a1),
			(s.y*a2-e.y*a1)/(a2-a1)
		};
	}
	bool parallel(const line &v){
		point a=e-s;
		point b=v.e-v.s;
		return mem_equal(a.x*b.y,a.y*b.x);
		// return sgn((e-s)^(v.e-v.s))==0;
	}
};
struct rectangle{
	int x1,y1,x2,y2;
}a[N];
void FOUND(){
	cout<<"possible"<<endl;
	exit(0);
}
struct halfplanes{
	int n=0,st,ed;
	vector<line> hp;
	vector<point> p;
	vector<int> que;
	void push(const line &x){
		if(hp.size()<n+5){
			p.resize(n+5);
			hp.resize(n+5);
			que.resize(n+5);
		}
		hp[n++]=x;
	}
	void unique(){
		int m=1;
		for(int i=1;i<n;i++){
			if(!mem_equal(hp[i].angle,hp[i-1].angle)){
				hp[m++]=hp[i];
			}else if(check_greater(hp[m-1].e-hp[m-1].s,hp[i].s-hp[m-1].s)){
				hp[m-1]=hp[i];
			}
		}
		n=m;
	}
	void debug(){
		fprintf(stderr,"st=%d ed=%d\n",st,ed);
		for(int i=st;i<=ed;i++)fprintf(stderr,"que[%d]=%d :: %d %d\n",i,que[i],hp[que[i]].x,hp[que[i]].y);
	}
	bool solve(){
		sort(hp.begin(),hp.begin()+n);
		// for(int i=0;i<n;i++)fprintf(stderr,"hp[%d]::%d %d::(%d,%d)->(%d,%d)\n",i,hp[i].x,hp[i].y,(int)hp[i].s.x,(int)hp[i].s.y,(int)hp[i].e.x,(int)hp[i].e.y);
		unique();
		que[st=0]=0;
		que[ed=1]=1;
		p[1]=hp[0].crosspoint(hp[1]);
		for(int i=2;i<n;i++){
			while(st<ed&&check_less(hp[i].e-hp[i].s,p[ed]-hp[i].s))ed--;
			while(st<ed&&check_less(hp[i].e-hp[i].s,p[st+1]-hp[i].s))st++;
			que[++ed]=i;
			if(hp[i].parallel(hp[que[ed-1]]))return false;
			p[ed]=hp[i].crosspoint(hp[que[ed-1]]);
			// debug();
		}
		while(st<ed&&check_less(hp[que[st]].e-hp[que[st]].s,p[ed]-hp[que[st]].s))ed--;
		while(st<ed&&check_less(hp[que[ed]].e-hp[que[ed]].s,p[st+1]-hp[que[ed]].s))st++;
		// debug();
		if(st+1>=ed)return false;
		return true;
	}
};
void check(){
	halfplanes sol;
	for(int i=1;i<=n;i++){
		// fprintf(stderr,"a[%d] :: %d %d %d %d\n",i,a[i].x1,a[i].y1,a[i].x2,a[i].y2);
		sol.push(line({1,(V)(a[i].y1-a[i].x1)},{0,(V)a[i].y1},i,1));
		sol.push(line({0,(V)a[i].y2},{1,(V)(a[i].y2-a[i].x2)},i,2));
	}
	sol.push(line({-L,-L-T},{L,-L}));
	sol.push(line({L-T,-L},{L,L}));
	sol.push(line({L,L-T},{-L,L}));
	sol.push(line({-L-T,L},{-L,-L}));
	if(sol.solve())FOUND();
}
void basic_check(vector<pair<int,int>> &a){
	vector<int> val;
	for(auto &it:a){
		val.push_back(it.first);
		val.push_back(it.second);
	}
	sort(all(val));
	val.erase(unique(all(val)),val.end());
	vector<int> ins(val.size()),del(val.size());
	for(auto &it:a){
		it.first=lower_bound(all(val),it.first)-val.begin();
		it.second=lower_bound(all(val),it.second)-val.begin();
		ins[it.first]++;
		del[it.second]++;
	}
	int cur=0;
	for(int i=0;i<val.size();i++){
		cur+=ins[i];
		if(cur==n)FOUND();
		cur-=del[i];
	}
}
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	vector<pair<int,int>> allx,ally;
	for(int i=1;i<=n;i++){
		cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2; 
		// a[i].x1+=T>>1;
		// a[i].y1+=T>>1;
		// a[i].x2+=T>>1;
		// a[i].y2+=T>>1;
		allx.emplace_back(a[i].x1,a[i].x2);
		ally.emplace_back(a[i].y1,a[i].y2);
		swap(a[i].y1,a[i].y2);
	}
	basic_check(allx);
	basic_check(ally);
	check();
	for(int i=1;i<=n;i++){
		a[i].y1=1e9-a[i].y1;
		a[i].y2=1e9-a[i].y2;
		swap(a[i].y1,a[i].y2);
	}
	check();
	cout<<"impossible"<<endl;
}