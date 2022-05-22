#include<cstdio>
#include<vector>
using namespace std;
using u32 = unsigned;

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
      for(int k=0; k<m; ++k) if(fl[id(i, k)] & fl[id(j, k)]){
         ++cnt; break;
      }
   }
   printf("%d\n", cnt);
}
