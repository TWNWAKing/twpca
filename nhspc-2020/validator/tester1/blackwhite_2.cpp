#include "testlib.h"
constexpr int MN_N = 1;
constexpr int MX_N = 3'000;
constexpr int MN_W = 1;
constexpr int MX_W = 10'000;
int main(int argc, char *argv[])
{
    registerValidation(argc, argv);

    // n, m
    const int n = inf.readInt(MN_N, MX_N);
    inf.readChar('\n');
    for (int c = 0; c < 3; ++c)
    {
        for (int i = 0; i < n; ++i)
        {
            inf.readInt(MN_W, MX_W);
            inf.readChar(i == n - 1 ? '\n' : ' ');
        }
    }
    inf.readEof();
}