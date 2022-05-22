// Expect: subtask1 AC
//         subtask2 TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
#define INF (1LL << 60)
#define F first
#define S second
#define MP make_pair
using namespace std;
using LL = long long;
using P = pair<LL,int>;
int n,m;
LL dis[M];
vector<P> e[M];
int main()
{
    scanf("%d %d", &n, &m);
    REP(i,1,m) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        e[x].push_back(make_pair(y,z));
    }

    priority_queue<P,vector<P>,greater<P>> q;
    fill(dis, dis+n+1, INF);

    auto add = [&](int cur,LL d) {
        if (dis[cur] <= d) return;
        q.push(MP(d, cur));
    };

    add(1, 0);
    while (!q.empty()) {
        int cur;
        LL d;
        tie(d, cur) = q.top();
        q.pop();
        if (dis[cur] <= d) continue;

        dis[cur] = d;
        for (auto i: e[cur]) {
            add(i.F, dis[cur] + i.S);
        }
    }
    printf("%lld\n", accumulate(dis+1, dis+n+1, 0LL));
    return 0;
}
