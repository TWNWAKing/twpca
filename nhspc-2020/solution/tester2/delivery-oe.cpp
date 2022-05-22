// Expect: AC
// O(n log n)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 300005
#define L (cur*2)
#define R (L+1)
using LL = long long;
using namespace std;
struct P{
    int x1, x2, y1, y2, r, w;
    int ox1;
    P () {}
    P (int a,int b,int c,int d,int e,int f) {
        x1 = a; ox1 = a;
        x2 = b;
        y1 = c;
        y2 = d;
        r = e;
        w = f;
    }
    bool operator < (const P &c) const {
        return x2 > c.x2;
    }
};
struct Seg {
    int sz, segid;
    vector<LL> mx, sum;
    Seg () {}
    Seg (int _sz, int _segid) {
        sz = _sz;
        segid = _segid;
        mx = vector<LL> (sz*4, 0LL);
        sum = vector<LL> (sz*4, 0LL);
    }
    void push(int cur,int ll,int rr) {
        if (ll==rr) return;

        sum[L] += sum[cur];
        sum[R] += sum[cur];
        mx[L] += sum[cur];
        mx[R] += sum[cur];
        sum[cur] = 0;
    }
    void pull(int cur,int ll,int rr) {
        if (ll==rr) return;
        assert(sum[cur] == 0);
        mx[cur] = max(mx[L], mx[R]);
    }
    void upd(int cur,int ll,int rr,int l,int r,int v) {
        if (ll==l && rr==r) {
            mx[cur] += v;
            sum[cur] += v;
            return;
        }

        push(cur, ll, rr);
        int mid = (ll+rr)/2;
        if (r<=mid) upd(L, ll, mid, l, r, v);
        else if (l>mid) upd(R, mid+1, rr, l, r, v);
        else {
            upd(L, ll, mid, l, mid, v);
            upd(R, mid+1, rr, mid+1, r, v);
        }
        pull(cur, ll, rr);
    }
    void upd(int l,int r,int v) {
        if (l%2!=segid) l++;
        if (r%2!=segid) r--;
        if (l>r) return;
        upd(1, 1, sz, (l+1)/2, (r+1)/2, v);
    }
    LL get_max() {
        return mx[1];
    }
};
int n;
P in[M];
void init() {
    scanf("%d", &n);
    REP(i,1,n) {
        int x, y, r, w;
        scanf("%d %d %d %d", &x, &y, &r, &w);
        in[i] = P(x+y-r, x+y+r, x-y-r, x-y+r, r, w);
    }

    // lisan x
    vector<int> lisan;
    REP(i,1,n) {
        lisan.push_back(in[i].x1);
        lisan.push_back(in[i].x2);
    }
    sort(lisan.begin(), lisan.end());
    lisan.resize(unique(lisan.begin(), lisan.end()) - lisan.begin());
    
    int adj = 0;
    int sz = lisan.size();
    REP(i,0,sz-1) {
        if ((i+1+adj)%2 != abs(lisan[i]%2)) {
            lisan.push_back(lisan[i]-1);
            adj++;
        }
    }
    sort(lisan.begin(), lisan.end());
    lisan.resize(unique(lisan.begin(), lisan.end()) - lisan.begin());
    REP(i,0,(int)lisan.size()-1) assert(abs(lisan[i]%2) == (i+1)%2);

    REP(i,1,n) {
        in[i].x1 = lower_bound(lisan.begin(), lisan.end(), in[i].x1) - lisan.begin() + 1;
        in[i].x2 = lower_bound(lisan.begin(), lisan.end(), in[i].x2) - lisan.begin() + 1;
    }

    // lisan y
    lisan.clear();
    REP(i,1,n) {
        lisan.push_back(in[i].y1);
        lisan.push_back(in[i].y2);
    }
    sort(lisan.begin(), lisan.end());
    lisan.resize(unique(lisan.begin(), lisan.end()) - lisan.begin());

    adj = 0;
    sz = lisan.size();
    REP(i,0,sz-1) {
        if ((i+1+adj)%2 != abs(lisan[i]%2)) {
            lisan.push_back(lisan[i]-1);
            adj++;
        }
    }
    sort(lisan.begin(), lisan.end());
    lisan.resize(unique(lisan.begin(), lisan.end()) - lisan.begin());
    REP(i,0,(int)lisan.size()-1) assert(abs(lisan[i]%2) == (i+1)%2);
    
    REP(i,1,n) {
        in[i].y1 = lower_bound(lisan.begin(), lisan.end(), in[i].y1) - lisan.begin() + 1;
        in[i].y2 = lower_bound(lisan.begin(), lisan.end(), in[i].y2) - lisan.begin() + 1;
    }

    sort(in+1, in+n+1, [](P a,P b) { return a.x1 < b.x1; });
}
LL calc() {
    LL res = 0;
    Seg seg0 = Seg(4*n, 0);
    Seg seg1 = Seg(4*n, 1);

    priority_queue<P> q;
    REP(i,1,n) {
        int x = in[i].x1;
        int j = i;
        while (j+1<=n && in[j+1].x1==x) j++;
        REP(k,i,j) {
            q.push(in[k]);
            seg0.upd(in[k].y1, in[k].y2, in[k].w);
            seg1.upd(in[k].y1, in[k].y2, in[k].w);
        }

        while (q.top().x2 < x) {
            auto p = q.top();
            q.pop();
            seg0.upd(p.y1, p.y2, -p.w);
            seg1.upd(p.y1, p.y2, -p.w);
        }

        // x~x
        if (in[i].x1%2==0) {
            res = max(res, seg0.get_max());
        } else {
            res = max(res, seg1.get_max());
        }

        // x ~ x+1
        while (!q.empty() && q.top().x2 < x+1) {
            auto p = q.top();
            q.pop();
            seg0.upd(p.y1, p.y2, -p.w);
            seg1.upd(p.y1, p.y2, -p.w);
        }

        if (j==n || in[j+1].ox1 != in[i].ox1+1) {
            res = max(res, seg0.get_max());
            res = max(res, seg1.get_max());
        }
        i = j;
    }
    return res;
}
int main()
{
    init();
    printf("%lld\n", calc());
    return 0;
}
