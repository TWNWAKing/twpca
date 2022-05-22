#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MN_N 1
#define MX_N 300'000
#define MN_X 0
#define MX_X 100'000'000
#define MN_W 1
#define MX_W 100
#define MN_R 0
#define MX_R 100'000'000
using namespace std;
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // n
    int n = inf.readInt(MN_N, MX_N);
    inf.readChar('\n');

    // x, y, r, w
    REP(i,1,n) {
        inf.readInt(MN_X, MX_X);
        inf.readChar(' ');
        inf.readInt(MN_X, MX_X);
        inf.readChar(' ');
        inf.readInt(MN_R, MX_R);
        inf.readChar(' ');
        inf.readInt(MN_W, MX_W);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
