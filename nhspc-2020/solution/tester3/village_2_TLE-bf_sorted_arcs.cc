#include<algorithm>
#include<numeric>
#include<deque>
#include<vector>
#include<climits>
#include<cmath>
#include<cstdio>
using namespace std;
using i64 = long long;

struct BellmanFord{
   struct Arc{
      int to, w;
      Arc() = default;
      constexpr Arc(int to, int w) noexcept: to(to), w(w){}
      constexpr bool operator<(Arc rhs) const noexcept{
         return w < rhs.w;
      }
   };
   BellmanFord() = default;
   explicit BellmanFord(int n): g(n){}
   void insert_arc(int u, int v, int w){
      g[u].emplace_back(v, w);
   }
   vector<i64> sssp(int s){
      for(auto &l: g){
         sort(l.begin(), l.end());
      }
      vector<i64> d(g.size(), LLONG_MAX);
      deque<int> dq;
      vector<bool> inq(g.size());
      vector<int> cnt(g.size());
      int thres = sqrt(g.size())/5+10;
      d[s] = 0; dq.push_back(s); inq[s] = true;
      while(!dq.empty()){
         int u = dq.front(); dq.pop_front(); inq[u] = false;
         for(auto [v, w]: g[u]) if(d[v] > d[u]+w){
            d[v] = d[u]+w;
            if(!inq[v]){
               if(++cnt[v]>thres || !dq.empty() && d[v]<d[dq.front()]){
                  dq.push_front(v);
               }else{
                  dq.push_back(v);
               }
               inq[v] = true;
            }
         }
      }
      return d;
   }
private:
   vector<vector<Arc>> g;
};

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   BellmanFord g(n);
   while(m-- > 0){
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      g.insert_arc(u-1, v-1, w);
   }
   auto d = g.sssp(0);
   printf("%lld\n", accumulate(d.cbegin(), d.cend(), 0ll));
}
