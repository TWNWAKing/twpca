// Expect: AC
// O(n logn + (m+n) logm)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
#define F first
#define S second
#define MP make_pair
using namespace std;
using i64 = long long;
using P = pair<i64,int>;
int n,m,w[M],pos[M];
vector<int> b[M];
int main()
{
    scanf("%d %d", &n, &m);
    REP(i,1,n) scanf("%d", &w[i]);
    REP(i,1,m) {
        int x, y;
        scanf("%d", &x);
        while (x--) {
            scanf("%d", &y);
            b[i].push_back(y);
        }
    }
    REP(i,1,m) sort(b[i].begin(), b[i].end(), [](int x,int y) { return w[x] < w[y]; });

    vector<int> ans;
    priority_queue<P,vector<P>,greater<P>> q;
    REP(i,1,m) q.push(MP(0ll, i));

    while ((int)ans.size() < n) {
        i64 wb;
        int id;
        tie(wb, id) = q.top();
        q.pop();

        if (pos[id] >= (int)b[id].size()) { // fail
            break;
        }
        int &p = pos[id];
        int it = b[id][p];
        q.push(MP(wb + w[it], id));
        ans.push_back(it);
        p++;
    }

    if ((int)ans.size() != n) {
        puts("-1");
    } else {
        REP(i,0,(int)ans.size()-1) {
            if (i) printf(" ");
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}
