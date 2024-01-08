#include<iostream>
#include<cstdio>
struct one
{
	int x,y,w;
};
bool umax(int& a,int t){if(t>a)return a=t,1;return 0;}
struct line
{
	one a1,a2;
	one b1,b2;
	void update()
	{
		if(a2.w>a1.w)std::swap(a1,a2);
		if(b2.w>b1.w)std::swap(b1,b2);
		if(b1.w>a1.w)std::swap(a1,b1),std::swap(a2,b2);
	}
	int eval(int x,int y)
	{
		int res=0;
		if(a1.x!=x&&a1.y!=y)umax(res,a1.w);
		if(a2.x!=x&&a2.y!=y)umax(res,a2.w);		
		if(b1.x!=x&&b1.y!=y)umax(res,b1.w);
		if(b2.x!=x&&b2.y!=y)umax(res,b2.w);
		return res;
	}
}fx,fy,now;
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int q;std::cin>>q;
	int lst=0;
	while(q--)
	{
		int op,x,y,w;
		std::cin>>op>>x>>y;
		x^=lst,y^=lst;
		if(op==1)
		{
			std::cin>>w;
			w^=lst;
			if(x==fx.a1.x)
			{
				if(y==fx.a1.y)umax(fx.a1.w,w);
				else if(y==fx.a2.y)umax(fx.a2.w,w);
				else if(w>fx.a2.w)fx.a2=one{x,y,w};
				fx.update();
			}
			else if(x==fx.b1.x)
			{
				if(y==fx.b1.y)umax(fx.b1.w,w);
				else if(y==fx.b2.y)umax(fx.b2.w,w);
				else if(w>fx.b2.w)fx.b2=one{x,y,w};
				fx.update();
			}
			else if(w>fx.a1.w)
			{
				now={one{x,y,w},one{x,0,0},fx.a1,fx.a2};
				fx=now;
			}
			else if(w>fx.b1.w)
			{
				now={fx.a1,fx.a2,one{x,y,w},one{x,0,0}};
				fx=now;
			}

			if(y==fy.a1.y)
			{
				if(x==fy.a1.x)umax(fy.a1.w,w);
				else if(x==fy.a2.x)umax(fy.a2.w,w);
				else if(w>fy.a2.w)fy.a2=one{x,y,w};
				fy.update();
			}
			else if(y==fy.b1.y)
			{
				if(x==fy.b1.x)umax(fy.b1.w,w);
				else if(x==fy.b2.x)umax(fy.b2.w,w);
				else if(w>fy.b2.w)fy.b2=one{x,y,w};
				fy.update();
			}
			else if(w>fy.a1.w)
			{
				now={one{x,y,w},one{0,y,0},fy.a1,fy.a2};
				fy=now;
			}
			else if(w>fy.b1.w)
			{
				now={fy.a1,fy.a2,one{x,y,w},one{0,y,0}};
				fy=now;
			}
			fx.update(),fy.update();
		}
		else printf("%d\n",lst=std::max(fx.eval(x,y),fy.eval(x,y)));
	}
	return 0;
}