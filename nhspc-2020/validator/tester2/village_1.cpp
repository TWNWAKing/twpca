#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MP make_pair
#define F first
#define S second
#define MN_N 2
#define MX_N 100
#define MN_M 1
#define MX_M 1'000
#define MN_W -110'000
#define MX_W  110'000
using namespace std;
using P = pair<int,int>;
int n, m;
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
    }
    inf.readEof();
    return 0;
}

