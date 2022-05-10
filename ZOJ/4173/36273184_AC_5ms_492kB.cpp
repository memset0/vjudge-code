#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define inf (1e9)
#define assert(X) if(!(X)) printf("error on %d\n",__LINE__)
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
#define N 205
int a[N],b[N],n;
int x,y;
int cnt=0;
bool f;
int sign(int x){return x>0?1:0;}
void work()
{
	cnt++;
	cin>>n; for(int i=1;i<=n;i++) read(a[i]); read(x);
	for(int i=1;i<=n;i++) read(b[i]); read(y);
	std::vector<double> v;
	for(int i=1;i<=n;i++)
	{
		if(a[i]*b[i]<0)
		{
			if(f)
			{
				for(int j=1;j<=n;j++)
				{
					if(j==i) v.pb(9999.0);
					else v.pb(0.0);
				}
			}
			else
			{
				for(int j=1;j<=n;j++)
				{
					if(j==i) printf("9999%c"," \n"[j==n]),v.pb(9999.0);
					else printf("0%c"," \n"[j==n]),v.pb(0.0);
				}
			}
			double A=0,B=0;
			for(int i=0;i<n;++i) A+=1.0*a[i+1]*v[i],B+=1.0*b[i+1]*v[i];
			A+=x,B+=y;
			assert(A*B<0);
			return ;
		}
	}
	if(x*y<0)
	{
		if(!f) for(int i=1;i<=n;i++) printf("0%c"," \n"[i==n]);
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(x||y)
		{
			if(a[i]==0&&x==0) continue;
			if(b[i]==0&&y==0) continue;
			double A=(double)-x/a[i],B=(double)-y/b[i];
			if(!a[i]&&b[i]&&x)
			{
				int ans=-9999;
				if(sign(x)^sign(b[i])) ans=-ans;
				if(f)
				{
					for(int j=1;j<=n;j++)
					{
						if(j==i) v.pb(ans);
						else v.pb(0);
					}
				}
				else
				{
					for(int j=1;j<=n;j++)
					{
						if(j==i) printf("%d%c",ans," \n"[j==n]),v.pb(ans);
						else printf("0%c"," \n"[j==n]),v.pb(0);
					}
				}
				double A=0,B=0;
				for(int i=0;i<n;++i) A+=1.0*a[i+1]*v[i],B+=1.0*b[i+1]*v[i];
				A+=x,B+=y;
				assert(A*B<0);
				return ;
			}
			if(!b[i]&&a[i]&&y)
			{
				int ans=-9999;
				if(sign(y)^sign(a[i])) ans=-ans;
				if(f)
				{
					for(int j=1;j<=n;j++)
					{
						if(j==i) v.pb(ans);
						else v.pb(0);
					}
				}
				else
				{
					for(int j=1;j<=n;j++)
					{
						if(j==i) printf("%d%c",ans," \n"[j==n]),v.pb(ans);
						else printf("0%c"," \n"[j==n]),v.pb(0);
					}
				}
				double A=0,B=0;
				for(int i=0;i<n;++i) A+=1.0*a[i+1]*v[i],B+=1.0*b[i+1]*v[i];
				A+=x,B+=y;
				assert(A*B<0);
				return ;
			}
			if(!a[i]||!b[i]||!x||!y) continue;
			if(!a[i]) A=x>0?10000:-10000;
			if(!b[i]) B=y>0?10000:-10000;
//			if(!a[i]) A=0;
//			if(!b[i]) B=0;
			if(abs(A-B)>1e-6)
			{
				A=(A+B)/2;
				double ans=A;
				if(f)
				{
					for(int j=1;j<=n;j++)
					{
						if(j==i) v.pb(A);
						else v.pb(0);
					}
				}
				else
				{
					for(int j=1;j<=n;j++)
					{
						if(j==i) printf("%.6lf%c",A," \n"[j==n]),v.pb(A);
						else printf("0%c"," \n"[j==n]),v.pb(0);
					}
				}
				double A=0,B=0;
				for(int i=0;i<n;++i) A+=1.0*a[i+1]*v[i],B+=1.0*b[i+1]*v[i];
				A+=x,B+=y;
				assert(A*B<0);
				if(A*B>=0)
				{
					cout<<i<<" "<<ans<<endl;
					for(int i=1;i<=n;i++) printf("%d ",a[i]); cout<<x<<"\n";
					for(int i=1;i<=n;i++) printf("%d ",b[i]); cout<<y<<"\n";
				}
				return ;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			if(a[i]==0&&b[i]==0) continue;
			if(a[j]==0&&b[j]==0) continue; 
			double A=1-x,B=-1-y;
			if(a[i]*b[j]==a[j]*b[i])
			{
				if(a[i]*B==b[i]*A)
				{
					if(a[j]==0) continue;
					double x1=0,x2=-A/(double)a[j];
					if(abs(x1)>10000||abs(x2)>10000) continue;
					if(f)
					{
						for(int k=1;k<=n;k++)
						{
							if(k==i) v.pb(x1);
							else if(k==j) v.pb(x2);
							else v.pb(0);
						}
					}
					else
					{
						for(int k=1;k<=n;k++)
						{
							if(k==i) printf("%.6lf%c",x1," \n"[k==n]),v.pb(x1);
							else if(k==j) printf("%.6lf%c",x2," \n"[k==n]),v.pb(x2);
							else printf("0%c"," \n"[k==n]),v.pb(0);
						}
					}
					
			double A=0,B=0;
			for(int i=0;i<n;++i) A+=1.0*a[i+1]*v[i],B+=1.0*b[i+1]*v[i];
			A+=x,B+=y;
//			if(A*B>=0)
//			{
//				cerr<<i<<' '<<j<<endl;
//				cerr<<x1<<' '<<x2<<endl;
//				for(int i=1;i<=n;i++) cerr<<a[i]<<' '; cerr<<x<<endl;
//				for(int i=1;i<=n;i++) cerr<<b[i]<<' '; cerr<<y<<endl;
//			}
			assert(A*B<0);
					return ;
				}
				continue;
			}
			double x1=(A*b[j]-B*a[j])/(a[i]*b[j]-b[i]*a[j]);
			double x2=(A*b[i]-B*a[i])/(a[j]*b[i]-b[j]*a[i]);
			if(abs(x1)>10000||abs(x2)>10000) continue;
			if(f)
			{
				for(int k=1;k<=n;k++)
				{
					if(k==i) v.pb(x1);
					else if(k==j) v.pb(x2);
					else v.pb(0);
				}
			}
			else
			{
				for(int k=1;k<=n;k++)
				{
					if(k==i) printf("%.6lf%c",x1," \n"[k==n]),v.pb(x1);
					else if(k==j) printf("%.6lf%c",x2," \n"[k==n]),v.pb(x2);
					else printf("0%c"," \n"[k==n]),v.pb(0);
				}
			}
			double _A=0,_B=0;
			for(int i=0;i<n;++i) _A+=1.0*a[i+1]*v[i],_B+=1.0*b[i+1]*v[i];
			_A+=x,_B+=y;
			assert(_A*_B<0);
			return ;
		}
	}
	cout<<"No\n";
}
int main()
{
	int T; read(T); while(T--) work();
}