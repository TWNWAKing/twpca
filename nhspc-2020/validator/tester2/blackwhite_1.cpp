#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MP make_pair
#define F first
#define S second
#define MN_N 1
#define MX_N 20
#define MN_BWT 1
#define MX_BWT 10'000
using namespace std;
int n;
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // n
    n = inf.readInt(MN_N, MX_N);
    inf.readChar('\n');

    // b
    REP(i,1,n) {
        inf.readInt(MN_BWT, MX_BWT);
        if (i==n) {
            inf.readChar('\n');
        } else {
            inf.readChar(' ');
        }
    }

    // w
    REP(i,1,n) {
        inf.readInt(MN_BWT, MX_BWT);
        if (i==n) {
            inf.readChar('\n');
        } else {
            inf.readChar(' ');
        }
    }

    // t
    REP(i,1,n) {
        inf.readInt(MN_BWT, MX_BWT);
        if (i==n) {
            inf.readChar('\n');
        } else {
            inf.readChar(' ');
        }
    }
    inf.readEof();
    return 0;
}

