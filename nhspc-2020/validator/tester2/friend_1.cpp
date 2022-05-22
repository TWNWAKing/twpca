#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MP make_pair
#define F first
#define S second
#define MN_N 1
#define MX_N 200
#define MN_F 0
#define MX_F 2500
using namespace std;
using P = pair<int,int>;
int n;
bool isf[MX_N + 5][MX_N + 5];
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // n
    n = inf.readInt(MN_N, MX_N);
    inf.readChar('\n');

    REP(i,1,n) {
        int cf = inf.readInt(MN_F, MX_F);
        REP(j,1,cf) {
            inf.readChar(' ');
            int x = inf.readInt(1, n);

            ensuref(x!=i, "self cycle found");
            ensuref(!isf[i][x], "duplicate edge");
            isf[i][x] = true;
        }
        inf.readChar('\n');
    }
    inf.readEof();

    REP(i,1,n) REP(j,1,n) {
        ensuref(isf[i][j]==isf[j][i], "not symmetric");
    }
    return 0;
}

