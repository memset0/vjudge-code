#include<bits/stdc++.h>
const int N=20;
int T,n,k;
int count(int x){
	std::vector<int> s(n);
	std::set<std::vector<int>> set;
	for(int i=0;i<n;i++)s[i]=(x>>(n-i-1))&1;
	for(int l=0;l<n;l++)
		for(int r=l;r<n;r++){
			bool fl=true;
			for(int i=l;i<=r;i++)fl&=s[i]==s[l+r-i];
			if(fl)set.insert(std::vector<int>(&s[l],&s[r]+1));
			// if(fl&&s[0]==0&&s[1]==0&&s[2]==1&&s[3]==1&&s[4]==0&&s[5]==1)set.insert(std::vector<int>(&s[l],&s[r]+1));
		}
	return set.size();
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
#endif
	for(scanf("%d",&T);T--;){
		scanf("%d%d",&n,&k);
		if(n<=15){
			int res=-1;
			for(int x=0;x<(1<<n);x++)if(count(x)==k){res=x;break;}
			if(~res){
				puts("Yes");
				for(int i=0;i<n;i++)putchar(((res>>i)&1)+'0');
				putchar('\n');
			}else{
				puts("No");
			}
		}else if(n==k){
			puts("Yes");
			for(int i=0;i<n;i++)putchar('0');
			putchar('\n');
		}else if(k<8){
			puts("No");
		}else{
			puts("Yes");
			std::vector<int> s;
			while(s.size()<n){
				s.push_back(0),s.push_back(0),s.push_back(1),s.push_back(1),s.push_back(0),s.push_back(1);
				for(int i=8;i<k&&s.size()<n;i++)s.push_back(0);
			}
			for(int i=0;i<n;i++)putchar(s[i]+'0');
			putchar('\n');
		}
	}
}