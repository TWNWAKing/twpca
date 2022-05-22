#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
using i64 = std::int64_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
template <class ES> i64 solve_nm(ES &e, i32 k)
{
    const i32 n = e.size();
    const i32 zn = n / 32 + (n % 32 != 0);
    std::vector<std::vector<u32>> be(n);
    std::vector<std::vector<i32>> ce(n);
    for (int i = 0; i < n; ++i)
    {
        be[i].resize(zn);
        std::vector<bool> used(zn);
        for (auto ee : e[i])
        {
            be[i][ee / 32] |= 1 << (ee & 31);
            if (!used[ee / 32])
            {
                used[ee / 32] = true;
                ce[i].push_back(ee / 32);
            }
        }
    }
    std::vector<i32> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&e](i32 l, i32 r) {
        auto ld = e[l].size();
        auto rd = e[r].size();
        return std::tie(ld, l) < std::tie(rd, r);
    });
    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        i32 x = ord[i];
        if (i32(e[x].size()) < k)
            continue;
        for (int j = i + 1; j < n; ++j)
        {
            auto y = ord[j];
            i32 t = 0;
            for (auto ee : ce[x])
            {
                t += __builtin_popcount(be[x][ee] & be[y][ee]);
            }
            ans += t >= k;
        }
    }
    return ans;
}
bool solve()
{
    i32 n{}, k{1};
    if (!(std::cin >> n))
        return false;
    std::vector<std::vector<i32>> e(n);
    for (i32 i = 0; i < n; ++i)
    {
        i32 d{};
        if (!(std::cin >> d))
            return false;
        e[i].resize(d);
        for (auto &ee : e[i])
        {
            if (!(std::cin >> ee))
                return false;
            ee--;
        }
    }
    i64 ans = solve_nm(e, k);
    std::cout << ans << '\n';
    return true;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    while (solve())
        ;
    std::cout.flush();
}
