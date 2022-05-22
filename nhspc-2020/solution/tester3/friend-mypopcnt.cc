#include<cstdio>
#include<array>
#include<vector>
using namespace std;
using u8 = unsigned char;
using u32 = unsigned;

constexpr array<u8, 65536> get_popcnt() noexcept{
   array<u8, 65536> res{};
   for(int i=1; i<65536; ++i){
      res[i] = res[i/2] + i%2;
   }
   return res;
}
constexpr array<u8, 65536> popcnt = get_popcnt();

int main(){
   int n; scanf("%d", &n);
   int m = (n+31)>>5;
   vector<u32> fl(n*m);
   auto id = [m](int i, int j){
      return i*m+j;
   };
   for(int i=0; i<n; ++i){
      int d; scanf("%d", &d);
      while(d-- > 0){
         int j; scanf("%d", &j); --j;
         fl[id(i, j>>5)] |= 1u<<(j&31);
      }
   }
   int cnt = 0;
   for(int i=0; i<n; ++i) for(int j=i+1; j<n; ++j){
      int cf = 0;
      for(int k=0; k<m; ++k){
         u32 a = fl[id(i, k)] & fl[id(j, k)];
         cf += popcnt[a&65535] + popcnt[a>>16];
      }
      cnt += cf >= 1;
   }
   printf("%d\n", cnt);
}
