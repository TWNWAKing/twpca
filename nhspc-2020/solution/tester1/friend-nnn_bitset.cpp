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
template <class ES> i64 solve_nnn(ES &e, i32 k)
{
    const i32 n = e.size();
    const i32 zn = n / 32 + (n % 32 != 0);
    std::vector<std::vector<u32>> be(n);
    for (int i = 0; i < n; ++i)
    {
        be[i].resize(zn);
        for (auto ee : e[i])
        {
            be[i][ee / 32] |= 1 << (ee & 31);
        }
    }
    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if(i32(e[i].size()) < k)
            continue;
        for (int j = i + 1; j < n; ++j)
        {
            if(i32(e[j].size()) < k)
                continue;
            i32 t = 0;
            for (int z = 0; z < zn; ++z)
            {
                t += __builtin_popcount(be[i][z] & be[j][z]);
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
    i64 ans = solve_nnn(e, k);
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
