// Expect: AC
// max n+m: 89
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 70
#define MP make_pair
#define F first
#define S second
using namespace std;
using P = pair<int,int>;
using PP = pair<P,P>;
using LL = long long;
int n, b[M];
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
void block(int xl, int yl) { // avoid dead end
    bool end[M][M], st[M][M];
    auto go = [](int x,int y,int dx,int dy) {
        auto it = ans.find(MP(MP(x, y), MP(x+dx, y+dy)));
        return it == ans.end();
    };

    MSET(end, false);
    end[xl][yl] = true;
    for (int i=xl; i>=1; i--) for (int j=yl; j>=1; j--) {
        if (i+1<=xl && go(i, j, 1, 0)) {
            end[i][j] |= end[i+1][j];
        }
        if (j+1<=yl && go(i, j, 0, 1)) {
            end[i][j] |= end[i][j+1];
        }
    }

    MSET(st, false);
    st[1][1] = true;
    REP(i, 1, xl) REP(j, 1, yl) {
        if (i-1>=1 && go(i-1, j, 1, 0)) {
            st[i][j] |= st[i-1][j];
        }
        if (j-1>=1 && go(i, j-1, 0, 1)) {
            st[i][j] |= st[i][j-1];
        }
        if (st[i][j]) {
            if (i+1<=xl && !end[i+1][j]) add(i, j, 1, 0);
            if (j+1<=yl && !end[i][j+1]) add(i, j, 0, 1);
        }
    }
}
void init() {
    LL x;
    scanf("%lld", &x);
    n = 0;
    while (x) {
        b[++n] = x % 20;
        x /= 20;
    }
    reverse(b+1, b+n+1);
}
int main()
{
    init();

    int X = 3;
    int Y = 3;
    int vu[] = {0, 10, 4, 1};
    int vl[] = {0, 10, 4, 1};
    int x=2, y=3;
    add(x-1, y, 1, 0);
    add(x, y-1, 0, 1);

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
                } else {
                    add(cx, y, 0, -1); // left
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
                } else {
                    add(x, cy, -1, 0); // up
                }
                cy++;
            };

            if (b[i]==3) {
                add(x+1, y, 0, -1); //l
                add(x+2, y, 0, -1); //l
                add(x, 2, 1, 0); //d
                REP(yy, 3, y-1) {
                    add(x+3, yy, -1, 0); //u
                    add(x+3, yy, 1, 0); //d
                }
                // spend cy
                REP(yy, cy, y+Y) add(x, yy, -1, 0); //u
                break;
            } else if (cx<=x+X && cy<=y+Y) {
                // use y first
                if (vl[cx-x] <= vu[cy-y]) add_y();
                else add_x();
            } else if (cx<=x+X) {
                add_x();
            } else {
                add_y();
            }
        }
        x += X;
        y += Y;
    }
    block(x, y);
    filter(x, y);

    printf("%d %d\n", x, y);
    printf("%d\n", (int)ans.size());
    for (auto i: ans) {
        printf("%d %d %d %d\n", i.F.F, i.F.S, i.S.F, i.S.S);
    }
    return 0;
}

