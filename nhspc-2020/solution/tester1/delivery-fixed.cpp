#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using i64 = std::int64_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
struct ele_t
{
    i32 sum;
    i32 max;
};
struct ttt_t
{
    std::vector<ele_t> a;
    i32 kk;
    ttt_t() = default;
    ttt_t(i32 k) : a(), kk(k)
    {
        for (; kk & (kk - 1);)
            kk += kk & -kk;
        a.resize(4 * kk);
    }
    void modify(i32 qs, i32 qe, i32 delta, i32 ts, i32 te, i32 w)
    {
        if (qs <= ts && te <= qe)
        {
            a[w].sum += delta;
            return;
        }
        i32 m = (ts + te) / 2;
        i32 l = 2 * w + 0;
        i32 r = 2 * w + 1;
        if (qs < m)
            modify(qs, qe, delta, ts, m, l);
        if (m < qe)
            modify(qs, qe, delta, m, te, r);
        a[w].max = std::max(a[l].max + a[l].sum, a[r].max + a[r].sum);
    }
    i32 add(i32 l, i32 r, i32 delta)
    {
        modify(l, r, delta, 0, kk, 1);
        return a[1].max + a[1].sum;
    }
};
template <class T> i32 solve_nlogn(T &a, i32 k)
{
    ttt_t tree(k);
    i32 ans = 0;
    for (auto mod : a)
    {
        //std::cerr << mod[2] << ' ' << mod[3] + 1 << ' ' << -mod[1] << '\n';
        ans = std::max(ans, tree.add(mod[2], mod[3] + 1, -mod[1]));
    }
    return ans;
}
template <class T> int lisan(T &a)
{
    std::vector<i32 *> b(a.size() * 2);
    const i32 n = a.size();
    for (int i = 0; i < n; ++i)
    {
        b[2 * i + 0] = &(a[i][2]);
        b[2 * i + 1] = &(a[i][3]);
    }
    std::sort(b.begin(), b.end(), [](i32 *a, i32 *b) { return *a < *b; });
    int k = 0;
    for (int i = 0, m = b.size(); i < m; ++k)
    {
        const int v = *b[i];
        int j = i + 1;
        for (; j < m && *b[j] == v; ++j)
            *b[j] = k;
        *b[i] = k;
        //std::cerr << v << "->" << k << '\n';
        i = j;
    }
    return k + 1;
}
bool solve()
{
    int n{};
    if (!(std::cin >> n))
        return false;
    std::vector<std::array<i32, 4>> ip(n);
    for (auto &e : ip)
    {
        if (!(std::cin >> e[0] >> e[1] >> e[2] >> e[3]))
            return false;
    }
    i64 ans = 0;
    for (int parity = 0; parity < 2; ++parity)
    {
        std::vector<std::array<i32, 4>> a(2 * n);
        int cap = 0;
        for (int i = 0; i < n; ++i)
        {
            i32 x = ip[i][0], y = ip[i][1], r = ip[i][2], w = ip[i][3];
            //(x-r, y) -> (x, y-r)
            //(x, y+r) -> (x+r, y)
            auto st = std::array<i32, 4>{x + y - r, -w, x - y - r, x - y + r};
            auto ed = std::array<i32, 4>{x + y + r, +w, x - y - r, x - y + r};
            st[0] += (st[0] & 1) != parity;
            st[2] += (st[2] & 1) != parity;
            st[3] -= (st[3] & 1) != parity;
            ed[0] -= (ed[0] & 1) != parity;
            ed[2] += (ed[2] & 1) != parity;
            ed[3] -= (ed[3] & 1) != parity;
            if (st[0] > ed[0] || st[2] > st[3])
                continue;
            a[cap++] = st;
            a[cap++] = ed;
            //{x + y - r, x-y-r, x-y+r+1, +w}
            //{x + y + r, x-y-r, x-y+r+1, -w}
        }
        a.erase(a.begin() + cap, a.end());
        std::sort(a.begin(), a.end());
        const i32 k = lisan(a);
        i64 ans_0 = solve_nlogn(a, k);
        ans = std::max(ans, ans_0);
    }
    std::cout << ans << '\n';
    return true;
}
int main()
{
    try
    {
        while (solve())
            ;
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
}
