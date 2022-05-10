#include<bits/stdc++.h>
const int N=20;
int T,n,k,cnt,s[N];
std::vector<int> res;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(scanf("%d",&T);T--;){
		scanf("%d%d",&n,&k),res.clear();
		for(int x=0;x<(1<<n);x++){
			std::set<std::vector<int>> set;
			for(int i=0;i<n;i++)s[i]=(x>>i)&1;
			for(int l=0;l<n;l++)
				for(int r=l;r<n;r++){
					bool fl=true;
					for(int i=l;i<=r;i++)fl&=s[i]==s[l+r-i];
					if(fl)set.insert(std::vector<int>(&s[l],&s[r]+1));
				}
			// for(int i=0;i<n;i++)putchar(((x>>i)&1)+'0');
			// printf(" >> %d %d\n",x,set.size());
			if(set.size()==k)res.push_back(x);
		}
		if(res.size()){
			puts("Yes");
			for(int i=0;i<1;i++){
			// for(int i=0;i<res.size();i++){
				for(int j=0;j<n;j++)putchar(((res[i]>>j)&1)+'0');
				putchar('\n');	
			}
		}else{
			puts("No");
		}
	}
}