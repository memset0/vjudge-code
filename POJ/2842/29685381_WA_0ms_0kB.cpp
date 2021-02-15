// source: https://blog.csdn.net/cfzjxz/article/details/8175747



#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <deque>
#include <queue>
#include <map>
#include <queue>
#include <list>
#include <iomanip>
using namespace std;                                              
///
///
#define INF 20000000
#define MAX 200
#define max(a,b)(a>b?a:b)
///
#define LL __int64
int n, W, H;//组数，宽度，高度
struct Point{
	LL x, y, light;//坐标x，坐标y，亮度
}points[MAX];
struct Line{
	LL x;        //插入线的x坐标值
	int leftmark, rightmark;//包含区间的左右下标
	int light;   //包含的光亮程度
	int flag;    //是否是入边还是出边
}lines[MAX * 2];
struct node{
	int lc, rc;  //线段树左右结点下标
	//针对具体问题
	int val;     //当前的光亮值
	int maxVal;  //有过的最大光亮值
};
LL ypos[MAX]; //暂存分割用的y坐标值
int line_cnt; //线段的个数
int ynums;    //不重复的y值个数，用于建树
 
 
node segtree[MAX * 4];
 
bool cmp(Line a,Line b){
    if(a.x == b.x)  return a.flag < b.flag;
	return a.x < b.x;
}
//建树
void buildtree(int root, int l, int r)
{
	segtree[root].lc = l;
	segtree[root].rc = r;
	segtree[root].val = segtree[root].maxVal = 0;
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	buildtree(root * 2, l, mid);
	buildtree(root * 2 + 1, mid + 1, r);
}
//插入
 
void insert_sg(int root, int l, int r, int val)
{
	//如果匹配子结点，更细数值
	if (segtree[root].lc == l && segtree[root].rc == r)
	{
		segtree[root].val += val;
		segtree[root].maxVal += val;
		return;
	}
	//push_down
	if (segtree[root].val != 0)
	{
		segtree[root * 2].val += segtree[root].val;
		segtree[root*2 + 1].val += segtree[root].val;
		segtree[root*2].maxVal += segtree[root].val;
		segtree[root*2+1].maxVal += segtree[root].val;
		segtree[root].val = 0;
	}
	//拆分插入操作
	int mid = (segtree[root].lc + segtree[root].rc) >> 1;
	if(r <= mid)   insert_sg(root * 2, l, r, val);
	else if(l > mid)   insert_sg(root * 2 + 1, l, r, val);
	else
	{
		insert_sg(root * 2, l, mid, val);
		insert_sg(root * 2 + 1, mid + 1, r, val);
	}
	//更新数值，最大值
	segtree[root].maxVal = max(segtree[root*2].maxVal, segtree[root*2+1].maxVal);
}
//
 
int main()
{
	///
	int i, j;
	while (scanf("%d %d %d", &n, &W, &H) != EOF)
	{
		ynums = 0;
		//读入所有坐标，初始化y坐标数组
		for (i = 0; i < n; i++)
		{
			scanf("%I64d%I64d%I64d",&points[i].x, &points[i].y, &points[i].light);
			ypos[ynums++] = points[i].y;
			ypos[ynums++] = points[i].y + H;
		}
		sort(ypos, ypos + ynums);//对y坐标进行排序
		ynums = unique(ypos, ypos + ynums) - ypos;//去重，STL的unique函数
		line_cnt = 0;
		for (i = 0; i < n; i++)
		{
			lines[line_cnt].x = points[i].x;//x赋值
			lines[line_cnt].leftmark = lower_bound(ypos, ypos + ynums, points[i].y) - ypos + 1;
			lines[line_cnt].rightmark = lower_bound(ypos, ypos + ynums, points[i].y + H) - ypos + 1;
			lines[line_cnt].light = points[i].light;
			lines[line_cnt++].flag = 1;
 
			lines[line_cnt].x = points[i].x + W;//x赋值
			lines[line_cnt].leftmark = lower_bound(ypos, ypos + ynums, points[i].y) - ypos + 1;
			lines[line_cnt].rightmark = lower_bound(ypos, ypos + ynums, points[i].y + H) - ypos + 1;
			lines[line_cnt].light = -points[i].light;
			lines[line_cnt++].flag = -1;
		}
		sort(lines, lines + line_cnt, cmp);//对扫描线的x坐标进行排序，从而从左到右进行扫描
		//建树
		buildtree(1, 1, ynums);
 
		int ans = 0;
		for (i = 0; i < line_cnt; i++)
		{
			insert_sg(1, lines[i].leftmark, lines[i].rightmark - 1, lines[i].light);//这个地方是对上边界的处理，让他不计算在里面！
			ans = max(ans, segtree[1].maxVal);
		}
		printf("%d\n", ans);
	}
	
	
	///
    return 0;
}                                              
 
