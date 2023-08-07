#include "bits/stdc++.h"

std::vector<int>a,b,res;
bool check_sp(std::vector<int> seq)
{
	int cl=0,cr=0;
	for(auto x:seq)
		if(x==seq[0])++cl;
		else if(x==seq.back())++cr;
		else return 0;
	return cl==cr;
}
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int n;
	std::cin>>n;
	for(int i=1;i<n;++i)
	{
		std::cout<<"? "<<i<<" "<<n<<std::endl;
		fflush(stdout);
		int x;
		std::cin>>x;
		a.emplace_back(x);
	}
	b=a;
	std::sort(b.begin(),b.end());
	if(check_sp(b))
	{
		int p,q;
		std::cout<<"? 2 1"<<std::endl;fflush(stdout);
		std::cin>>p;
		std::cout<<"? "<<n<<" 1"<<std::endl;fflush(stdout);
		std::cin>>q;
		if(p==q)
		{
			int real=a[1];
			for(int i=1;i<n;++i)
				if(a[i-1]!=real)res.emplace_back(i);
		}
		else
		{
			int real=(a[1]==b[0]?b.back():b[0]);
			for(int i=1;i<n;++i)
				if(a[i-1]!=real)res.emplace_back(i);
		}
	}
	else
	{
		int p,q,nx,ny;
		int real=b[(n-1)>>1];
		for(int i=1;i<n;++i)
			if(a[i-1]!=real)res.emplace_back(i);
		for(int i=1;i<n;++i)
			if(a[i-1]==real)
			{
				std::cout<<"? "<<i<<" "<<(i==1?2:1)<<std::endl,fflush(stdout);
				std::cin>>p;
				std::cout<<"? "<<n<<" "<<(i==1?2:1)<<std::endl,fflush(stdout);
				std::cin>>q;
				if(p!=q)res.emplace_back(n);
				break;
			}
	}	
	std::cout<<"! "<<res.size();
	for(auto x:res)std::cout<<" "<<x;
	std::cout<<std::endl;
	fflush(stdout);
	return 0;
}