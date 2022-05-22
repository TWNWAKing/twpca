#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
using i64 = std::int64_t;
using i32 = std::int32_t;
template <class T, class H>
i32 dfs(const int cur, const int n, const T &b, const H &t, const H &h,
        const int last_state, const i32 cur_delay, const i32 cur_cost,
        i32 cur_ans)
{
    // for(int i = 0 ;i < cur;++i) std::cout << ' ';
    // std::cout << last_state << std::endl;
    if (cur == n)
    {
        // std::cout << "cost:" << cur_cost << std::endl;
        return cur_cost;
    }
    if (cur_cost + h[cur] >= cur_ans)
    {
        return cur_cost + h[cur];
    }
    if (cur)
    {
        {
            int new_state = last_state;
            i32 new_cost = cur_cost + b[new_state][cur];
            i32 new_ans =
                dfs(cur + 1, n, b, t, h, new_state,
                    std::max(cur_delay, new_cost + t[cur]), new_cost, cur_ans);
            cur_ans = std::min(cur_ans, new_ans);
        }
        {
            int new_state = last_state ^ 1;
            i32 new_cost = cur_delay + b[new_state][cur];
            i32 new_ans = dfs(cur + 1, n, b, t, h, new_state, new_cost + t[cur],
                              new_cost, cur_ans);
            cur_ans = std::min(cur_ans, new_ans);
        }
    }
    else
    {
        for (int new_state = 0; new_state < 2; ++new_state)
        {
            i32 new_cost = b[new_state][cur];
            i32 new_ans = dfs(cur + 1, n, b, t, h, new_state, new_cost + t[cur],
                              new_cost, cur_ans);
            cur_ans = std::min(cur_ans, new_ans);
        }
    }
    return cur_ans;
}
template <class T, class H> i32 sub(T &b, H &t)
{
    const int n = b[0].size();
    H h(n);
    for (int i = 0; i < n; ++i)
        h[i] = std::min(b[0][i], b[1][i]);
    for (int i = n - 2; i >= 0; --i)
        h[i] += h[i + 1];
    return dfs(0, n, b, t, h, -1, 0, 0, std::numeric_limits<i32>::max());
}
bool solve()
{
    int n{};
    if (!(std::cin >> n))
        return false;
    std::vector<std::vector<i32>> b(2, std::vector<i32>(n));
    std::vector<i32> t(n);
    for (int i = 0; i < n; ++i)
    {
        if (!(std::cin >> b[0][i]))
            return false;
    }
    for (int i = 0; i < n; ++i)
    {
        if (!(std::cin >> b[1][i]))
            return false;
    }
    for (int i = 0; i < n; ++i)
    {
        if (!(std::cin >> t[i]))
            return false;
    }
    i32 ans_0 = sub(b, t);
    std::cout << ans_0 << '\n';
    return true;
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    while (solve())
        ;
    std::cout.flush();
}
