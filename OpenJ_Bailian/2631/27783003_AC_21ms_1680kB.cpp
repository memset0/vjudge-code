
//
//You are to output a single integer: the road distance between the two most remote villages in the area.
//Sample Input
//
//5 1 6
//1 4 5
//6 3 9
//2 6 8
//6 1 7
//Sample Output
//
//22
//Source
//
//The UofA Local 1999.10.16
 
// 求树的直径
// 从任意节点开始，宽搜找最长路得到直径的一个节点s
// 从节点s开始宽搜找最长路得直径
 
#include<fstream>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
 
const int MAX = 20003;
 
void bfs(int s, vector<int> *aim, vector<int> *weight, int *len)
{
	deque<int> q;								// 双端队列
	bool mark[MAX] = {};						// 是否被标记过，初始化为否
	int p = s ,i = 0, pp = s;
	q.push_back(s);								// s入队
	mark[s] = true;
	len[s] = 0;									// s到s的距离为0
	while(!q.empty())							// 当队列不空
	{
		p = q.front();							// 取队首元素
		for (i=0; i<aim[p].size(); i++)			// 将所有没有访问的后继节点入队
		{
			pp = aim[p].at(i);					// p的后继节点
			if (!mark[pp])						// 如果没有访问过
			{
				mark[pp] = true;				// 访问它
				q.push_back(pp);				// 入队
				len[pp] = len[p] + weight[p].at(i);	// 更新路径长度
			}
 
		}
		q.pop_front();
	}
 
}
 
 
int main()
{
#ifndef ONLINE_JUDGE
	ifstream fin("poj2631.txt");
	int x,y,w,n=1;								// n统计节点个数,边数=节点数-1,故从1开始计数
	// 用正向表存储边
	vector<int> aim[MAX] = {};					// 端点向量
	vector<int> weight[MAX] = {};				// 权值向量
	while (fin >> x >> y >> w)
	{
		x--; y--;								// 下标从0开始
		aim[x].push_back(y);
		weight[x].push_back(w);
		aim[y].push_back(x);
		weight[y].push_back(w);
		n++;
	}
	fin.close();
	int len[MAX] = {};
	bfs(0, aim, weight, len);
	int i = 0, max = 0, s = 0;
	for (i=0; i<n; i++)
	{
		if (len[i] > max)
		{
			s = i;
			max = len[i];
		}
	}
	memset(len,0,sizeof(len));
	max = 0;
	bfs(s, aim, weight, len);
	for (i=0; i<n; i++)
	{
		if (len[i] > max)
		{
			s = i;
			max = len[i];
		}
	}
	cout << len[s];
	return 0;
#endif
#ifdef ONLINE_JUDGE
	int x,y,w,n=1;								// n统计节点个数,边数=节点数-1,故从1开始计数
	// 用正向表存储边
	vector<int> aim[MAX] = {};					// 端点向量
	vector<int> weight[MAX] = {};				// 权值向量
	while (cin >> x >> y >> w)
	{
		x--; y--;								// 下标从0开始
		aim[x].push_back(y);
		weight[x].push_back(w);
		aim[y].push_back(x);
		weight[y].push_back(w);
		n++;
	}
	int len[MAX] = {};
	bfs(0, aim, weight, len);
	int i = 0, max = 0, s = 0;
	for (i=0; i<n; i++)
	{
		if (len[i] > max)
		{
			s = i;
			max = len[i];
		}
	}
	memset(len,0,sizeof(len));
	max = 0;
	bfs(s, aim, weight, len);
	for (i=0; i<n; i++)
	{
		if (len[i] > max)
		{
			s = i;
			max = len[i];
		}
	}
	cout << len[s];
	return 0;
#endif

}//12312321312312