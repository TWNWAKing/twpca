#ifndef TESTER3_NUMBER_THEORY_HH
#define TESTER3_NUMBER_THEORY_HH

#include<array>

#define U32 unsigned
#define I64 long long
#define U64 unsigned long long

namespace tester3{
constexpr std::array<I64, 2> extgcd(I64 a, I64 b){
   // assert(a>=0 && b>=0);
   if(b == 0) return {1, 0};
   auto [x, y] = extgcd(b, a%b);
   return {y, x-a/b*y};
}

constexpr I64 inv_mod(I64 a, I64 mod){
   // assert(mod>1 && std::gcd(mod, a%mod)==1);
   if((a%=mod) < 0) a += mod;
   auto [_, x] = extgcd(mod, a);
   return x<0? x+mod: x;
}

constexpr U32 pow_mod(I64 a, I64 n, U32 mod){
   // assert(mod > 0);
   if(mod == 1) return 0;
   if((a%=mod) < 0) a += mod;
   if(n < 0) a = inv_mod(a, mod);
   U64 res = 1, t = a;
   while(n){
      if(n%2) res = res*t%mod;
      if(n/=2) t = t*t%mod;
   }
   return res;
}

constexpr bool miller_rabin(U32 n, U32 witness){
   // assert(n>=3 && n%2==0);
   if((witness%=n) == 0) return true;
   U32 d = n-1;
   int r = 0;
   while(d%2 == 0){
      d>>=1, ++r;
   }
   U32 x = pow_mod(witness, d, n);
   if(x==1 || x==n-1) return true;
   for(int cnt=r-1; cnt-->0; ){
      x = (U64)x*x%n;
      if(x == n-1) return true;
   }
   return false;
}

constexpr bool primality_test(U32 n) noexcept{
   if(n <= 1) return false;
   if(n == 2) return true;
   if(n%2 == 0) return false;
   return miller_rabin(n, 2) && (n < 2047 || (miller_rabin(n, 7) && miller_rabin(n, 61)));
}

constexpr bool primality_test(int n) noexcept{
   return n<0? false: primality_test((U32)n);
}
}

#undef U64
#undef I64
#undef U32

#endif
