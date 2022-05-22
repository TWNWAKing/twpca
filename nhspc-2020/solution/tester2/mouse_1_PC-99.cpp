// Expect: PC
// max n+m: 99
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
void init() {
    LL x;
    scanf("%lld", &x);
    n = 0;
    while (x) {
        b[++n] = x % 10;
        x /= 10;
    }
    reverse(b+1, b+n+1);
}
int main()
{
    init();

    int X = 3;
    int Y = 2;
    int vu[] = {0, 4, 1};
    int vl[] = {0, 6, 3, 1};
    int mxx = 1, mxy = 1;
    int x=2, y=2;
    add(1, 2, 1, 0);
    add(2, 1, 0, 1);

    REP(i,1,n) {
        // right
        REP(xx, x, x+X-1) add(xx, y+Y, 0, 1);
        // down
        REP(yy, y, y+Y-1) add(x+X, yy, 1, 0);

        int cx = x + 1;
        int cy = y + 1;
        while (cx<=x+X || cy<=y+Y) {
            auto add_x = [&]() {
                if (vl[cx-x] <= b[i]) {
                    b[i] -= vl[cx-x];
                    REP(yy, 2, y-1) { // add up & down
                        add(cx, yy, -1, 0);
                        add(cx, yy, 1, 0);
                    }
                    mxx = cx;
                } else {
                    add(cx, y, 0, -1); // left
                    add(cx, 1, 0, 1); // right
                }
                cx++;
            };
            auto add_y = [&]() {
                if (vu[cy-y] <= b[i]) {
                    b[i] -= vu[cy-y];
                    REP(xx, 2, x-1) { // add
                        add(xx, cy, 0, -1);
                        add(xx, cy, 0, 1);
                    }
                    mxy = cy;
                } else {
                    add(x, cy, -1, 0); // up
                    add(1, cy, 1, 0); // down
                }
                cy++;
            };
            if (cx<=x+X && cy<=y+Y) {
                if (vl[cx-x] >= vu[cy-y]) add_x();
                else add_y();
            } else if (cx<=x+X) {
                add_x();
            } else {
                add_y();
            }
        }

        x += X;
        y += Y;
    }
    add(1, mxy, 0, 1);
    add(mxx, 1, 1, 0);
    filter(x, y);

    printf("%d %d\n", x, y);
    printf("%d\n", (int)ans.size());
    for (auto i: ans) {
        printf("%d %d %d %d\n", i.F.F, i.F.S, i.S.F, i.S.S);
    }
    return 0;
}
