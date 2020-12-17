#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n,p,c,h;
int b[N], l[N], cnt[N], v[N];

int main()
{
	freopen("kabaleo.in","r",stdin);
	freopen("kabaleo.out","w",stdout);
	cin >> n >> p >> c >> h;
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		cnt[b[i]]++;
	}
	for(int i=1;i<=p;i++){
		scanf("%d",&l[i]);
		cnt[l[i]]++;
	}
	if(n==1){
		if(l[p] == h)cout << 1 << endl << 1 << endl;
		else cout << 0 << endl;
		return 0;
	}
	cnt[h]-=p-1;
	vector<int> ans;
	int mx=0,s=0;
	for(int i=1;i<=c;i++)if(i!=h){
		if(cnt[i]>mx)mx=cnt[i],s=1;
		else if(cnt[i] == mx) s++;
	}
	for(int i=1;i<=n;i++){
		if(b[i]!=h){
			if((cnt[b[i]]==mx && s==1 && cnt[h] == mx) || cnt[h] > mx)ans.push_back(i);
		}else{
			if(cnt[h]-1>mx)ans.push_back(i);
		}
	}
	cout << ans.size() << endl;
	for(int i=0;i<(int)ans.size();i++){
		printf("%d%c",ans[i],i+1==(int)(ans.size())?'\n':' ');
	}
}
//