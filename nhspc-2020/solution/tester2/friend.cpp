// Expect: AC
// O(n^3 / 32)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 2505
#define B(x) (1<<(x))
using namespace std;
int n,m,f[M][M/32+5];
void add(int x,int y) {
    f[x][y/32] |= B(y%32);
}
int main()
{
    scanf("%d", &n);
    m = 1;
    REP(i,0,n-1) {
        int c, x;
        scanf("%d", &c);
        while (c--) {
            scanf("%d", &x);
            x--;
            add(i, x);
        }
    }

    int ans = 0;
    REP(i,0,n-1) REP(j,i+1,n-1) {
        int cnt = 0;
        REP(k,0,n/32+1) {
            cnt += __builtin_popcount(f[i][k] & f[j][k]);
        }
        if (cnt >= m) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
