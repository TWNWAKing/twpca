#include<algorithm>
#include<functional>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<pair<int, int>> ore(n);
   for(int i=0; i<n; ++i){
      int w, p;
      scanf("%d%d", &w, &p);
      ore[i] = {p, w};
   }
   sort(ore.begin(), ore.end(), greater<>());
   int ans = 0;
   for(auto [p, w]: ore){
      if(w < m){
         ans += p*w;
         m -= w;
      }else{
         ans += p*m; break;
      }
   }
   printf("%d\n", ans);
}
