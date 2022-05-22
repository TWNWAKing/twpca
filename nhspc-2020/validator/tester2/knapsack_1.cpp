#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MN_N 1
#define MX_N 1'000
#define MN_M 1
#define MX_M 100'000
#define MN_W 1
#define MX_W 100
#define MN_P 1
#define MX_P 1000
using namespace std;
int p[MX_N + 5];
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // n, m
    int n = inf.readInt(MN_N, MX_N);
    inf.readChar(' ');
    inf.readInt(MN_M, MX_M);
    inf.readChar('\n');

    // w, p
    REP(i,1,n) {
        inf.readInt(MN_W, MX_W);
        inf.readChar(' ');
        p[i] = inf.readInt(MN_P, MX_P);
        inf.readChar('\n');
    }
    inf.readEof();

    // ensure monotone
    REP(i,1,n-1) ensuref(p[i]>=p[i+1], "p[i] >= p[i+1]");
    return 0;
}
