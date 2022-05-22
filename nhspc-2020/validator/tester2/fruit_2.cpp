#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MP make_pair
#define F first
#define S second
#define MN_N 1
#define MX_N 18
#define MN_W 1
#define MX_W 100
using namespace std;
using P = pair<int,int>;
int n,m;
bool vis[MX_N + 5];
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // n, m
    n = inf.readInt(MN_N, MX_N);
    inf.readChar(' ');
    m = inf.readInt(1, n);
    inf.readChar('\n');

    // w
    REP(i,1,n) {
        inf.readInt(MN_W, MX_W);
        if (i==n) {
            inf.readChar('\n');
        } else {
            inf.readChar(' ');
        }
    }

    int cnt = 0;
    REP(i,1,m) {
        int c = inf.readInt(0, n);
        cnt += c;
        while (c--) {
            inf.readChar(' ');
            int x = inf.readInt(1, n);
            ensuref(!vis[x], "duplicate fruit id");
            vis[x] = true;
        }
        inf.readChar('\n');
    }
    inf.readEof();

    ensuref(cnt==n, "some fruit is disappeared");
    return 0;
}

