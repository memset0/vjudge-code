#include <cstdio>
#include <vector>

std::vector<int> vec[50001];
int n,m,k;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&k);
		int last,tem;
		scanf("%d",&last);
		for(int i=2;i<=k;i++){
			scanf("%d",&tem);
			vec[last].push_back(tem);
			vec[tem].push_back(last);
			last=tem;
		}
	}
}