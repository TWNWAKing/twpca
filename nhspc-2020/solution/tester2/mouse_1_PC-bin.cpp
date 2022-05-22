// binary
// Expect: PC
// max n+m: 121
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
#define MP make_pair
#define F first
#define S second
using namespace std;
using P = pair<int,int>;
using PP = pair<P,P>;
using LL = long long;
int n, b[70];
set<PP> ans;
void add(int x,int y,int dx,int dy) {
    if (dx<0) { x += dx; dx *= -1; }
    if (dy<0) { y += dy; dy *= -1; }
    ans.insert(MP(MP(x,y), MP(x+dx, y+dy)));
}
void filter(int xl,int yl) {
    auto inr = [](int x,int y1,int y2) {
        return y1<=x && x<=y2;
    };
    auto inr2 = [&](P a) {
        return inr(a.F, 1, xl) && inr(a.S, 1, yl);
    };

    auto it = ans.begin();
    while (it != ans.end()) {
        if (!inr2(it->F) || !inr2(it->S)) {
            ans.erase(it++);
        } else {
            it++;
        }
    }
}
int main()
{
    {
        LL x;
        scanf("%lld", &x);
        n = 0;
        while (x) {
            b[++n] = x&1;
            x >>= 1;
        }
        reverse(b+1, b+n+1);
    }

    int mx1 = 1;
    int x=2, y=1;
    REP(i,2,n) {
        add(x+1, y, 0, -1);
        add(x+1, y, 1, 0);
        add(x, y+1, 0, 1);
        if (b[i] == 0) {
            add(x, y+1, -1, 0);
            add(1, y+1, 1, 0);
        } else {
            mx1 = i;
            REP(i2, 2, x-1) {
                add (i2, y+1, 0, -1);
                add (i2, y+1, 0, 1);
            }
        }
        x++;
        y++;
    }
    add(1, mx1, 0, 1);
    filter(x, y);

    printf("%d %d\n", x, y);
    printf("%d\n", (int)ans.size());
    for (auto i: ans) {
        printf("%d %d %d %d\n", i.F.F, i.F.S, i.S.F, i.S.S);
    }
    return 0;
}
