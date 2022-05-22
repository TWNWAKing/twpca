#include<algorithm>
#include<numeric>
#include<vector>
#include<climits>
#include<cstdio>
using namespace std;

int main(){
   int n; scanf("%d", &n);
   vector<int> b[2], t(n+1);
   for(int m=0; m<=1; ++m){
      b[m].resize(n+1);
      for(int i=1; i<=n; ++i){
         scanf("%d", &b[m][i]);
      }
   }
   for(int i=1; i<=n; ++i){
      scanf("%d", &t[i]);
   }
   partial_sum(b[0].cbegin(), b[0].cend(), b[0].begin());
   partial_sum(b[1].cbegin(), b[1].cend(), b[1].begin());
   vector<int> dp1[2], dp2[2], stk_bt[2]{{0}, {0}}, stk_dbbt[2]{{0}, {0}}, stk_min_dbbt[2]{{INT_MAX, 0}, {INT_MAX, 0}};
   int min_db[2]{};
   dp1[0].resize(n+1);
   dp1[1].resize(n+1);
   dp2[0].resize(n+1);
   dp2[1].resize(n+1);
   for(int i=1; i<=n; ++i){
      for(int m=0; m<=1; ++m){
         dp1[m][i] = b[m][i] + min_db[m];
         int dbbt = dp2[m^1][i-1]-b[m][i-1]+b[m][i]+t[i];
         while(!stk_bt[m].empty() && b[m][i]+t[i] >= stk_bt[m].back()){
            dbbt = min(dbbt, stk_dbbt[m].back()-stk_bt[m].back()+b[m][i]+t[i]);
            stk_bt[m].pop_back();
            stk_dbbt[m].pop_back();
            stk_min_dbbt[m].pop_back();
         }
         stk_bt[m].push_back(b[m][i]+t[i]);
         stk_dbbt[m].push_back(dbbt);
         stk_min_dbbt[m].push_back(min(dbbt, stk_min_dbbt[m].back()));
         dp2[m][i] = stk_min_dbbt[m].back();
      }
      min_db[0] = min(min_db[0], dp2[1][i]-b[0][i]);
      min_db[1] = min(min_db[1], dp2[0][i]-b[1][i]);
   }
   printf("%d\n", min(dp1[0][n], dp1[1][n]));
}
