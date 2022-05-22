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
template <class ES> i64 solve_native_nnn(ES &e, i32 k)
{
    const i32 n = e.size();
    std::vector<std::vector<bool>> be(n);
    for (int i = 0; i < n; ++i)
    {
        be[i].resize(n);
        for (auto ee : e[i])
        {
            be[i][ee] = 1;
        }
    }
    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i32(e[i].size()) < k)
            continue;
        for (int j = i + 1; j < n; ++j)
        {
            if (i32(e[j].size()) < k)
                continue;
            i32 t = 0;
            for (int z = 0; z < n; ++z)
            {
                t += be[i][z] & be[j][z];
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
    i64 ans = solve_native_nnn(e, k);
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
