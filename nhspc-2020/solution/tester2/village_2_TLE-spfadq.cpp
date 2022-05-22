// Expect: subtask1 AC
//         subtask2 TLE
// O(nm)
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
using P = pair<int,int>;
int n,m;
LL dis[M];
bool inq[M];
vector<P> e[M];
int main()
{
    srand(33 - 4);
    scanf("%d %d", &n, &m);
    REP(i,1,m) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        e[x].push_back(make_pair(y,z));
    }
    REP(i,1,n) random_shuffle(e[i].begin(), e[i].end());

    deque<int> q;
    fill(dis, dis+n+1, INF);

    auto add = [&](int cur,LL d) {
        if (dis[cur] <= d) return;
        dis[cur] = d;
        if (!inq[cur]) {
            inq[cur] = true;
            q.push_back(cur);
        }
    };
    auto pop = [&]() {
        int res = -1;
        int dice = rand() % 2;
        if (dice) {
            res = q.front();
            q.pop_front();
        } else {
            res = q.back();
            q.pop_back();
        }
        inq[res] = false;
        return res;
    };

    add(1, 0);
    while (!q.empty()) {
        int cur = pop();
        for (auto i: e[cur]) {
            add(i.F, dis[cur] + i.S);
        }
    }
    printf("%lld\n", accumulate(dis+1, dis+n+1, 0LL));
    return 0;
}
