#include<algorithm>
#include<numeric>
#include<tuple>
#include<vector>
#include<climits>
#include<cstdio>
using namespace std;

int main(){
   int n; scanf("%d", &n);
   vector<int> s[2];
   for(int h: {0, 1}){
      s[h].resize(n+1);
      for(int i=1; i<=n; ++i){
         scanf("%d", &s[h][i]);
      }
      partial_sum(s[h].cbegin(), s[h].cend(), s[h].begin());
   }
   vector<int> t(n+1);
   for(int i=1; i<=n; ++i){
      scanf("%d", &t[i]);
   }
   int ans = min(s[0][n], s[1][n]);
   vector<int> d[2];
   vector<tuple<int, int, int>> stk[2];
   for(int h: {0, 1}){
      d[h].resize(n+1);
      stk[h].emplace_back(INT_MAX, 0, INT_MAX);
   }
   for(int i=1; i<=n-1; ++i){
      for(int h: {0, 1}){
         int b = d[1-h][i]-s[1-h][i-1];
         while(get<0>(stk[h].back()) <= s[1-h][i]+t[i]){
            b = min(b, get<1>(stk[h].back()));
            stk[h].pop_back();
         }
         d[h][i+1] = min(get<2>(stk[h].back()), s[1-h][i]+t[i]+b);
         stk[h].emplace_back(s[1-h][i]+t[i], b, d[h][i+1]);
         ans = min(ans, d[h][i+1]+s[h][n]-s[h][i]);
      }
   }
   printf("%d\n", ans);
}
