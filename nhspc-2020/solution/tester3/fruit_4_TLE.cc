#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> w(n);
   for(int i=0; i<n; ++i){
      scanf("%d", &w[i]);
   }
   vector<vector<int>> p(m);
   for(int i=0; i<m; ++i){
      int ki; scanf("%d", &ki);
      p[i].resize(ki);
      for(int j=0; j<ki; ++j){
         scanf("%d", &p[i][j]);
         --p[i][j];
      }
      sort(p[i].begin(), p[i].end(), [&w](int i, int j){
         return w[i] < w[j];
      });
   }
   vector<i64> b(m);
   vector<int> ans(n), it(m);
   for(int i=0; i<n; ++i){
      int j = min_element(b.cbegin(), b.cend()) - b.cbegin();
      if(it[j] == (int)p[j].size()){
         ans = {-1}; break;
      }
      ans[i] = p[j][it[j]]+1;
      b[j] += w[p[j][it[j]++]];
   }
   for(size_t i=0; i<ans.size(); ++i){
      printf("%d%c", ans[i], " \n"[i+1==ans.size()]);
   }
}
