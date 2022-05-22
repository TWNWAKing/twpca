// WARNING: constraints about result matrix C is not tested in this validator
// see others validator
#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MP make_pair
#define F first
#define S second
#define MN_S 1
#define MX_S 3
#define MN_N 2
#define MX_N 2'800
#define MN_P 37
#define MX_P 50'000'000
using namespace std;
int n;
bool is_prime(int x) {
    if (x<=1) return false;
    int sq = (int)sqrt(x);
    REP(i,2,sq) if (x%i==0) return false;
    return true;
}
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // subtask
    inf.readInt(MN_S, MX_S);
    inf.readChar('\n');

    // n, p
    n = inf.readInt(MN_N, MX_N);
    inf.readChar(' ');
    int p = inf.readInt(MN_P, MX_P);
    inf.readChar('\n');
    ensuref(is_prime(p), "p=%d should be a prime.", p);

    // A
    REP(i,1,n) {
        REP(j,1,n) {
            inf.readInt(0, p-1);
            if (j==n) {
                inf.readChar('\n');
            } else {
                inf.readChar(' ');
            }
        }
    }

    // B
    REP(i,1,n) {
        REP(j,1,n) {
            inf.readInt(0, p-1);
            if (j==n) {
                inf.readChar('\n');
            } else {
                inf.readChar(' ');
            }
        }
    }
    inf.readEof();
    return 0;
}

