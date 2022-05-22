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
auto my_hash = [](i16 x) -> size_t { return x; };
template <class ES> i64 solve_nm(ES &e, i32 k)
{
    constexpr int W = 64;
    const i32 n = e.size();
    const i32 zn = n / W + (n % W != 0);
    std::vector<i32> ord(n);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&e](i32 l, i32 r) {
        auto ld = e[l].size();
        auto rd = e[r].size();
        return ld > rd;
    });
    for(;!ord.empty() && e[ord.back()].size() < k;ord.pop_back());
    using map_t = std::unordered_map<i32, u64, decltype(my_hash)>;
    std::vector<map_t> be(n, map_t(1, my_hash));
    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        i32 x = ord[i];
        map_t &bi = be[x];
        for (auto ee : e[x])
        {
            bi[ee / W] |= u64(1) << (ee & (W-1));
        }
        std::vector<map_t::value_type> ce;
        ce.reserve(n / W);
        for (auto z : bi)
            ce.emplace_back(z);
        for (int j = 0; j < i; ++j)
        {
            i32 y = ord[j];
            i32 t = 0;
            auto &bj = be[y];
            for (auto z : ce)
            {
                auto it = bj.find(z.first);
                if (it == bj.end())
                    continue;
                t += __builtin_popcountll(z.second & it->second);
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
