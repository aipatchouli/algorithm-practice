#include <queue>
#include <iostream>
#include <cstring>

#define fi first
#define se second
using namespace std;
#define INF 0x3f3f3f3f
#define CLR(x,y) memset(x,y,sizeof(x))
#define LC(x) (x<<1)
#define RC(x) ((x<<1)+1)
#define MID(x,y) ((x+y)>>1)
typedef pair<int, int> pii;
typedef long long LL;
const int N = 505;
const int M = 1e5 + 5;

struct edge
{
    int to, nxt, f;
    LL w;
    edge() {}
    edge(int _to, int _nxt, LL _w, int _f): to(_to), nxt(_nxt), w(_w), f(_f) {}
} E[M << 3];

struct info
{
    int u, f;
};

int head[N], tot;
int vis[N][2];
LL d[N][2], G[N][N], inf = 0x3f3f3f3f3f3f3f3f;

void init()
{
    CLR(head, -1);
}

inline void add(int s, int t, int w, int f)
{
    E[tot] = edge(t, head[s], w, f);
    head[s] = tot++;
}

inline LL sqr(const LL &x)
{
    return x * x;
}

void spfa(int s)
{
    queue<pii>Q;
    Q.push(pii(s, 0));
    Q.push(pii(s, 1));
    vis[s][0] = 1;
    vis[s][1] = 1;
    d[s][0] = 0LL;
    d[s][1] = 0LL;
    while (!Q.empty())
    {
        pii t = Q.front();
        Q.pop();
        vis[t.fi][t.se] = 0;
        for (int i = head[t.fi]; ~i; i = E[i].nxt)
        {
            int v = E[i].to;
            if (E[i].f == 0) //走大路
            {
                if (t.se == 0) //从大路来
                {
                    if (d[v][0] > d[t.fi][0] + E[i].w)
                    {
                        d[v][0] = d[t.fi][0] + E[i].w;
                        if (!vis[v][0])
                        {
                            vis[v][0] = 1;
                            Q.push(pii(v, 0));
                        }
                    }
                }
                else if (t.se == 1) //从小路来
                {
                    if (d[v][0] > d[t.fi][1] + E[i].w)
                    {
                        d[v][0] = d[t.fi][1] + E[i].w;
                        if (!vis[v][0])
                        {
                            vis[v][0] = 1;
                            Q.push(pii(v, 0));
                        }
                    }
                }
            }
            else//走小路
            {
                if (t.se == 0)//从大路来
                {
                    if (d[v][1] > d[t.fi][0] + sqr(E[i].w))
                    {
                        d[v][1] = d[t.fi][0] + sqr(E[i].w);
                        if (!vis[v][1])
                        {
                            vis[v][1] = 1;
                            Q.push(pii(v, 1));
                        }
                    }
                }
            }
        }
    }
}
int main()
{
    int n, m, a, b, f, i, j, k;
    LL w;
    while (cin >> n && cin >> m)
    {
        init();
        for (i = 0; i <= n; ++i)
        {
            d[i][0] = d[i][1] = inf;
            for (j = 0; j <= n; ++j)
                G[i][j] = inf;
        }
        for (i = 0; i < m; ++i)
        {
            cin >> f >> a >> b >> w ;
            if (f == 0)
            {
                add(a, b, w, f);
                add(b, a, w, f);
            }
            else
            {
                G[a][b] = min(G[a][b], w);
                G[b][a] = min(G[b][a], w);
            }
        }
        for (k = 1; k <= n; ++k)
        {
            for (i = 1; i <= n; ++i)
            {
                for (j = i + 1; j <= n; ++j)
                {
                    if (k == i || k == j)
                        continue;
                    if (G[i][j] > G[i][k] + G[k][j])
                        G[i][j] = G[j][i] =  G[i][k] + G[k][j];
                }
            }
        }
        for (i = 1; i <= n; ++i)
        {
            for (j = i + 1; j <= n; ++j)
            {
                if (G[i][j] == inf)
                    continue;
                add(i, j, G[i][j], 1);
                add(j, i, G[i][j], 1);
            }
        }
        spfa(1);
        cout << min(d[n][0], d[n][1]) << endl ;
    }
    return 0;
}