#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <unordered_map>
#include <vector>
using i64 = std::int64_t;
using i32 = std::int32_t;
using i16 = std::int16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
template <class ES> i64 solve_nm(ES &e, i32 k)
{
    const i32 n = e.size();
    std::vector<i32> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&e](i32 l, i32 r) {
        auto ld = e[l].size();
        auto rd = e[r].size();
        return ld > rd;
    });
    for(;!ord.empty() && e[ord.back()].size() < k;ord.pop_back());
    using map_t = std::vector<bool>;
    std::vector<map_t> be(n);
    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        i32 x = ord[i];
        map_t &bi = be[x];
        bi = map_t(n);
        for (auto ee : e[x])
        {
            bi[ee] = true;
        }
        for (int j = 0; j < i; ++j)
        {
            i32 y = ord[j];
            i32 t = 0;
            auto &bj = be[y];
            for (auto z : e[x])
            {
                t += bj[z];
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
