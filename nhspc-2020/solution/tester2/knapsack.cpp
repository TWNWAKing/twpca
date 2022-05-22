// Expect: AC
// O(n)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 1005
using namespace std;
using P = pair<int,int>;
int n,m;
P in[M];

int main()
{
    scanf("%d %d", &n, &m);
    REP(i,1,n) scanf("%d %d", &in[i].second, &in[i].first);
    sort(in+1, in+n+1, greater<P> ());

    int ans = 0;
    REP(i,1,n) {
        int w = min(in[i].second, m);
        ans += w * in[i].first;
        m -= w;
    }
    printf("%d\n", ans);
    return 0;
}
