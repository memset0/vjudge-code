#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N=109;
int tot,Q;
map<string,int> mp;
struct Struct{
	string name;
	long long size;
	int width;
	vector<string> cname;
	vector<int> cid;
	vector<long long> start;
	map<string,int> idx;
	long long push(string,string);
	inline void update_size(){
//		cerr<<"! size="<<size<<" width="<<width<<endl;
		assert(width!=0);
		while(size%width)++size;
	}
}a[N];
long long Struct::push(string type,string vname){
	idx[vname]=cid.size();
	int id=mp[type];
	cid.push_back(id);
	cname.push_back(vname);
	width=max(width,a[id].width);
	while(size%a[id].width)++size;
//	cerr<<"push "<<type<<" "<<vname<<" :: "<<id<<" size="<<size<<" new_size="<<a[id].size<<endl;
	start.push_back(size);
	size+=a[id].size;
	return start.back();
}
long long walk(string pattern){
	vector<string> p;
	pattern+='.';
	for(int lst=-1,i=0;i<pattern.length();i++)
		if(pattern[i]=='.'){
			string current;
			for(int j=lst+1;j<i;j++)current+=pattern[j];
			p.push_back(current);
			lst=i;
		}
	long long ans=0;
	int u=0;
	for(int i=0;i<p.size();i++){
		int x=a[u].idx[p[i]];
		ans+=a[u].start[x];
		u=a[u].cid[x];
	}
	return ans;
}
string locate(long long addr){
	string ans;
	int u=0;
	while(u<1||u>4){
		if(a[u].size==0){
			return "ERR";
		}
		int x=upper_bound(all(a[u].start),addr)-a[u].start.begin()-1;
		addr-=a[u].start[x];
		if(addr>=a[a[u].cid[x]].size){
			return "ERR";
		}
		ans+=a[u].cname[x];
		ans+='.';
		u=a[u].cid[x];
	}
	ans.pop_back();
	return ans;
}
int main(){
#ifdef memset0
	freopen("struct3.in","r",stdin);
	freopen("struct3.out","w",stdout);
#else
	freopen("struct.in","r",stdin);
	freopen("struct.out","w",stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	a[1].name="byte",a[1].size=a[1].width=1;
	a[2].name="short",a[2].size=a[2].width=2;
	a[3].name="int",a[3].size=a[3].width=4;
	a[4].name="long",a[4].size=a[4].width=8;
	for(int i=1;i<=4;i++){
		mp[a[i].name]=i;
	}
	tot=4;
	cin>>Q;
	int op,k;
	string s,t,n;
	long long addr;
	while(Q--){
		cin>>op;
//		cerr<<"! "<<op<<endl;
		if(op==1){
			cin>>s>>k;
			++tot;
			mp[s]=tot;
			a[tot].name=s;
			for(int i=1;i<=k;i++){
				cin>>t>>n;
				a[tot].push(t,n);
			}
			a[tot].update_size();
			cout<<a[tot].size<<" "<<a[tot].width<<endl;
		}else if(op==2){
			cin>>t>>n;
			cout<<a[0].push(t,n)<<endl;
		}else if(op==3){
			cin>>s;
			cout<<walk(s)<<endl;
		}else if(op==4){
			cin>>addr;
			cout<<locate(addr)<<endl;
		}
	}
}