#include<cctype>
#include<cstdio>
using namespace std;
using i64 = long long;

inline int getint() noexcept{
   int c;
   do
      c = getchar();
   while(!isdigit(c));
   int res = 0;
   do
      res = 10*res+(c-'0'), c = getchar();
   while(isdigit(c));
   return res;
}

int main(){
   if(getint() != 1){
      return 0;
   }
   constexpr int N = 2'800;
   static int a[N*N], b[N*N];
   int n = getint(), p = getint();
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      a[i*n+j] = getint();
   }
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      b[j*n+i] = getint();
   }
   for(int i=0; i<n*n; i+=n){
      for(int j=0; j<n*n; j+=n){
         i64 cij = 0;
         for(int k=0; k<n; ++k){
            cij += (i64)a[i+k]*b[j+k];
         }
         if(cij %= p){
            printf("%d %d %lld\n", i/n+1, j/n+1, cij);
            break;
         }
      }
   }
}
