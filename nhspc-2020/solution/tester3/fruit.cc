#include<algorithm>
#include<functional>
#include<queue>
#include<tuple>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;
using t3i = tuple<i64, int, int>;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> w(n);
   for(int i=0; i<n; ++i){
      scanf("%d", &w[i]);
   }
   vector<vector<int>> p(m);
   for(int i=0; i<m; ++i){
      int l; scanf("%d", &l);
      p[i].resize(l);
      for(int j=0; j<l; ++j){
         scanf("%d", &p[i][j]);
         --p[i][j];
      }
   }
   for(int i=0; i<m; ++i){
      sort(p[i].begin(), p[i].end(), [&w](int i, int j){
         return w[i] < w[j];
      });
   }
   vector<int> ans;
   ans.reserve(n);
   priority_queue<t3i, vector<t3i>, greater<>> pq;
   for(int i=0; i<m; ++i){
      pq.emplace(0, i, 0);
   }
   while(n-- > 0){
      auto [wi, i, j] = pq.top(); pq.pop();
      if(j == (int)p[i].size()){
         ans = {-1}; break;
      }
      ans.push_back(p[i][j]+1);
      pq.emplace(wi+w[p[i][j]], i, j+1);
   }
   for(size_t i=0; i<ans.size(); ++i){
      printf("%d%c", ans[i], " \n"[i+1==ans.size()]);
   }
}
