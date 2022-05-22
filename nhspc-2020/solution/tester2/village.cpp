// Expect: AC
// O(n + m)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
#define INF (1LL << 60)
#define F first
#define S second
using namespace std;
using LL = long long;
using P = pair<int,int>;
int n,m,ord[M],top;
LL dis[M];
bool vis[M];
vector<P> e[M], fr[M];
void dfs(int cur) {
    vis[cur] = true;
    for (auto i: e[cur]) if (!vis[i.F]) dfs(i.F);
    ord[top++] = cur;
}
int main()
{
    scanf("%d %d", &n, &m);
    REP(i,1,m) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        e[x].push_back(make_pair(y,z));
        fr[y].push_back(make_pair(x, z));
    }

    fill(dis, dis+n+1, INF);
    dis[1] = 0;
    top = 1;
    dfs(1);
    for (int i=n; i>=1; i--) {
        int p = ord[i];
        for (auto j: fr[p]) dis[p] = min(dis[p], dis[j.F] + j.S);
    }
    printf("%lld\n", accumulate(dis+1, dis+n+1, 0LL));
    return 0;
}
