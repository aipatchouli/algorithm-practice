#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <ctime>
 
// 涉及距离的量都要用long long防止中间结果溢出int范围
const int NMAX = 505;
const long long int INF = 0x3f3f3f3f3f3f3f3f;
int n ,m;								// 点/边数
long long int mat[NMAX][NMAX] = {};		// 两点之间的疲劳距离
long long int small[NMAX][NMAX] = {};	// 两点之间的小路距离
long long int db[NMAX] = {};			// 最后一条路是大路情况下每个点到1号点的最短距离
long long int ds[NMAX] = {};			// 最后一条路是小路情况下每个点到1号点的最短距离
bool vis[NMAX] = {};					// 节点是否在spfa队列中
 
void spfa(int st)					// spfa求最短路（分db和ds),以st为源
{
	int i, u;
	bool flag;						// 是否入队标记
	memset(db, 0x3f, sizeof(db));	// 初始化各点到源的距离为无穷大
	memset(ds, 0x3f, sizeof(ds));
	db[st] = 0;							// 初始化到源的距离为0
	ds[st] = 0;
	std::queue<int> q;					// 节点队列
	q.push(st);							// 源入队
	vis[st] = 1;						// 标记源入队
	while (!q.empty())					// 当队列不空时循环
	{
		u = q.front();					// 取队首节点
		q.pop();						// 队首节点出队
		vis[u] = 0;						// 标记队首节点出队，之后可能的话还可以再入队
		for (i=0; i<n; i++)
		{
			flag = false;
			if (small[u][i] < INF)			// 有小路连通
			{
				if (db[u] + small[u][i]*small[u][i] < ds[i])	// 如果i和u有道路相连且可以更新i到源的距离
				{
					ds[i] = db[u] + small[u][i]*small[u][i];	// 更新i到源的距离
					flag = true;
				}
			}
			if (mat[u][i] < INF)				// 有大路连通
			{
				if (db[u] + mat[u][i] < db[i] || ds[u] + mat[u][i] < db[i])
				{
					db[i] = std::min(db[u], ds[u]) + mat[u][i];
					flag = true;
				}
			}
			if (!vis[i] && flag)
			{
				vis[i] = 1;
				q.push(i);
			}
		}
	}
}


int main()
{
	int i, j, k, f, s1, s2;
	long long int l;
	bool b_flag = 0, s_flag = 0;				// 大路/小路最短路有没有访问到n号点
	scanf("%d%d", &n, &m);
	memset(mat, 0x3f, sizeof(mat));
	memset(small, 0x3f, sizeof(small));
	for (i=0; i<m; i++)
	{
		scanf("%d%d%d%lld", &f, &s1, &s2, &l);
		s1--;
		s2--;
		if (f)
		{
			small[s1][s2] = std::min(l, small[s1][s2]);
			small[s2][s1] = small[s1][s2];
		}
		else
		{
			mat[s1][s2] = std::min(l, mat[s1][s2]);
			mat[s2][s1] = mat[s1][s2];
		}
	}
	// Floyd算法求小路的所有连通支（矩阵对称性优化,使Floyd算法的时间复杂度近似变为一半）
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			for (k=j+1; k<n; k++)
			{
				small[j][k] = std::min(small[j][i] + small[i][k], small[j][k]);
				small[k][j] = small[j][k];
			}
	// SPFA, 将最后一步通过大路达到的距离和最后一步通过小路达到的距离分开讨论
	spfa(0);
	printf("%lld\n", std::min(db[n-1], ds[n-1]));
	
	return 0;
}