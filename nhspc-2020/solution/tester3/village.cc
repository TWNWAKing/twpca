#include<algorithm>
#include<numeric>
#include<vector>
#include<climits>
#include<cstdio>
using namespace std;
using i64 = long long;

struct DagSssp{
   struct Arc{
      int to, w;
      Arc() = default;
      constexpr Arc(int to, int w) noexcept: to(to), w(w){}
   };
   DagSssp() = default;
   explicit DagSssp(int n): g(n){}
   void insert_arc(int u, int v, int w){
      g[v].emplace_back(u, w);
   }
   vector<i64> sssp(int s) const{
      vector<i64> d(g.size(), LLONG_MAX/2);
      vector<bool> vis(g.size());
      d[s] = 0; vis[s] = true;
      for(int u=0; u<(int)g.size(); ++u){
         dfs(u, d.data(), vis);
      }
      return d;
   }
private:
   vector<vector<Arc>> g;
   i64 dfs(int u, i64 *d, vector<bool> &vis) const noexcept{
      if(vis[u]) return d[u];
      vis[u] = true;
      for(auto [v, w]: g[u]){
         d[u] = min(d[u], dfs(v, d, vis) + w);
      }
      return d[u];
   }
};

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   DagSssp dag(n);
   while(m-- > 0){
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      dag.insert_arc(u-1, v-1, w);
   }
   auto d = dag.sssp(0);
   printf("%lld\n", accumulate(d.cbegin(), d.cend(), 0ll));
}
