#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
using i64 = std::int64_t;
using i32 = std::int32_t;
template <class T, class H> i64 sub(T &b, H &t)
{
    const int n = b[0].size();
    T sum(2, H(n));
    std::partial_sum(b[0].begin(), b[0].end(), sum[0].begin());
    std::partial_sum(b[1].begin(), b[1].end(), sum[1].begin());
    T dp(2, H(n));
    i32 ans = std::min(sum[0][n - 1], sum[1][n - 1]);
    dp[0][0] = b[0][0];
    dp[1][0] = b[1][0];
    for (int i = 1; i < n; ++i)
    {
        for (int s = 0; s < 2; ++s)
        {
            i32 mmax = 0;
            i32 tmp = 0x7FFFFFFF;
            for (int j = i - 1; j >= 0; --j)
            {
                mmax = std::max(mmax, sum[s ^ 1][j] + t[j]);
                // dp[0][i] = std::min(dp[1][j] + max(sum[1][j] + t[j],
                // sum_b[j+1] + t[j+1], sum_b[j+2] + t[j+2], sum_b[j+3] + t[j+3]
                // ... , ) - sum[1][j]);
                tmp = std::min(tmp, mmax + dp[s ^ 1][j] - sum[s ^ 1][j]);
            }
            dp[s][i] = tmp + b[s][i];
            ans = std::min(ans, dp[s][i] + sum[s][n - 1] - sum[s][i]);
        }
    }
    return ans;
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
    i64 ans_0 = sub(b, t);
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
