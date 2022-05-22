#include<bits/stdc++.h>
#define CMS
#define TESTSYS
#include "testlib.h"
using namespace std;
typedef long long LL;
#define N 210
#define OVERFLOW_LL 2'000'000'000'000'000'000LL
#define MAX_SUM 140
#define MAX_SCORE_SUM 90
char state[N][N]={0}; // which door is closed, 1=right, 2=down, 3=both
LL d[N][N]; // num of road

void error() {
    quitf(_wa, "invalid output");
}
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    ouf.strict = true;

    LL t = inf.readLong();

    // no answer file
    // read contestant's output
    int n = ouf.readInt(1, MAX_SUM);
    ouf.readChar(' ');
    int m = ouf.readInt(1, MAX_SUM);
    ouf.readEoln();
    if (n+m > MAX_SUM)
        error();

    // set state of door
    int k = ouf.readInt(0, m*n*2);
    // tolerate the last eoln
    if (k >= 1) {
        ouf.readEoln();
    }
    for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) {
        state[i][j] = d[i][j] = 0;
    }
    for (int i=0; i<k; i++) {
        int x1,x2,y1,y2;
        x1 = ouf.readInt(1, n);
        ouf.readChar(' ');
        y1 = ouf.readInt(1, m);
        ouf.readChar(' ');
        x2 = ouf.readInt(1, n);
        ouf.readChar(' ');
        y2 = ouf.readInt(1, m);
        // tolerate the last eoln
        if (i!=k-1) {
            ouf.readEoln();
        }

        // swap unordered doors
        if (x1>x2 || (x1==x2 && y1>y2)) {
            swap(x1, x2);
            swap(y1, y2);
        }

        // bit 1: (x, y) -> (x, y+1)
        // bit 2: (x, y) -> (x+1, y)
        if (x1==x2 && y2==y1+1) {
            if (state[x1][y1] & 1) error(); // duplicate
            else state[x1][y1] |= 1;
        } else if (x1+1==x2 && y2==y1) {
            if (state[x1][y1] & 2) error(); // duplicate
            else state[x1][y1] |= 2;
        } else error();
    }
    // evaluate
    for (int i=1; i<=n; i++) state[i][m] |= 1;
    for (int j=1; j<=m; j++) state[n][j] |= 2;
    d[1][1] = 1;
    for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) {
        if ((state[i][j] & 1)==0) {
            d[i][j+1] += d[i][j];
            d[i][j+1] = min(d[i][j+1], OVERFLOW_LL);
        }
        if ((state[i][j] & 2)==0) {
            d[i+1][j] += d[i][j];
            d[i+1][j] = min(d[i+1][j], OVERFLOW_LL);
        }
        if (d[i][j]!=0 && state[i][j]==3 && !(i==n && j==m)) {
            quitf(_wa, "Dead end found at %d, %d", i, j);
        }
    }
    if (d[n][m] == t) {
        if (n+m >= MAX_SUM) {
            quitf(_wa, "n + m too big");
        } else if (n+m <= MAX_SCORE_SUM) {
            quitf(_ok, "good");
        } else {
            double score = (double)min(100, (MAX_SUM - n - m) * 2) / 100.0;
            fprintf(stdout, "%.5f\n", score);
            // testlib style partial, score is ranged [0, 200]
            quitf(_pc(int(score*200)), "partial");
        }
    } else {
        quitf(_wa, "Expected %lld paths, get %lld", t, d[n][m]);
    }
    return 0;
}
