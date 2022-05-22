#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MP make_pair
#define F first
#define S second
#define MN_N 2
#define MX_N 100'000
#define MN_M 1
#define MX_M 200'000
#define MN_W -110'000
#define MX_W  110'000
using namespace std;
using P = pair<int,int>;
int n, m, ord[MX_N + 5];
vector<P> e[MX_N + 5];
bool vis[MX_N + 5], ins[MX_N + 5];
bool dfs(int cur) {
    vis[cur] = true;
    ins[cur] = true;
    bool res = true;
    for (auto i: e[cur]) {
        if (vis[i.F] && ins[i.F]) res = false; // cycle
        else if (!vis[i.F]) res &= dfs(i.F);
    }
    ins[cur] = false;
    return res;
}
void connected_dag() {
    MSET(vis, false);
    MSET(ins, false);
    ensuref(dfs(1), "Found cycle");
    ensuref(accumulate(vis+1, vis+n+1, 0) == n, "Not connected from 1");
}
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // n, m
    n = inf.readInt(MN_N, MX_N);
    inf.readChar(' ');
    m = inf.readInt(MN_M, MX_M);
    inf.readChar('\n');

    // u, v, w
    REP(i,1,m) {
        int x = inf.readInt(1, n);
        inf.readChar(' ');
        int y = inf.readInt(1, n);
        inf.readChar(' ');
        int w = inf.readInt(MN_W, MX_W);
        inf.readChar('\n');
        e[x].push_back(MP(y, w));
    }
    inf.readEof();

    connected_dag();
    return 0;
}
