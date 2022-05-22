#include<array>
#include<numeric>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

array<i64, 2> extgcd(i64 a, i64 b){
   if(!b) return {1, 0};
   auto [x, y] = extgcd(b, a%b);
   return {y, x-a/b*y};
}

i64 inv_mod(i64 a, i64 mod){
   i64 res = extgcd(a, mod)[0];
   if(res < 0) res += mod;
   return res;
}

int main(){
   int subtask;
   scanf("%d", &subtask);
   if(subtask != 1) return 0;
   int n, p;
   scanf("%d%d", &n, &p);
   vector<vector<int>> a(n, vector<int>(n)), b(n, vector<int>(n));
   for(int i=0; i<n; ++i){
      for(int j=0; j<n; ++j){
         scanf("%d", &a[i][j]);
      }
   }
   for(int i=0; i<n; ++i){
      for(int j=0; j<n; ++j){
         scanf("%d", &b[i][j]);
      }
   }
   auto ab = [n, p, &a, &b](vector<i64> &u){
      vector<i64> tmp(n);
      for(int i=0; i<n; ++i){
         tmp[i] = inner_product(b[i].cbegin(), b[i].cend(), u.cbegin(), 0ll) % p;
      }
      for(int i=0; i<n; ++i){
         u[i] = inner_product(a[i].cbegin(), a[i].cend(), tmp.cbegin(), 0ll) % p;
      }
   };
   vector<i64> u(n, 1), v(n);
   iota(v.begin(), v.end(), 0);
   ab(u); ab(v);
   for(int i=0; i<n; ++i){
      printf("%d %lld %lld\n", i+1, v[i]*inv_mod(u[i], p)%p+1, u[i]);
   }
}
