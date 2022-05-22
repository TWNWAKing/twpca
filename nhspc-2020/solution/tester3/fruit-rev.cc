#include<algorithm>
#include<queue>
#include<set>
#include<tuple>
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
   priority_queue<tuple<i64, int, int>> pq;
   set<pair<i64, int>> b;
   for(int i=0; i<m; ++i){
      int ki; scanf("%d", &ki);
      p[i].resize(ki);
      i64 si = 0;
      for(int j=0; j<ki; ++j){
         scanf("%d", &p[i][j]);
         si += w[--p[i][j]];
      }
      sort(p[i].begin(), p[i].end(), [&](int i, int j){
         return w[i] < w[j];
      });
      if(ki > 0){
         pq.emplace(si-w[p[i][ki-1]], i, ki-1);
      }
      b.emplace(si, i);
   }
   vector<int> sigma;
   while(n-- > 0){
      auto [si, i, j] = pq.top(); pq.pop();
      if(make_pair(si, i) >= *b.cbegin()){
         sigma = {-1}; break;
      }
      sigma.push_back(p[i][j]+1);
      if(j > 0){
         pq.emplace(si-w[p[i][j-1]], i, j-1);
      }
      b.erase(make_pair(si+w[p[i][j]], i));
      b.emplace(si, i);
   }
   reverse(sigma.begin(), sigma.end());
   for(size_t i=0; i<sigma.size(); ++i){
      printf("%d%c", sigma[i], " \n"[i+1==sigma.size()]);
   }
}
