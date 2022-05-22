#include<algorithm>
#include<numeric>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

vector<int> solve(int n, int m, int const *w, int const *b){
   vector<int> sigma(n);
   iota(sigma.begin(), sigma.end(), 1);
   do{
      vector<i64> s(m);
      for(int i: sigma){
         int j = min_element(s.cbegin(), s.cend()) - s.cbegin();
         if(b[i-1] != j){
            goto next_sigma;
         }
         s[j] += w[i-1];
      }
      return sigma;
   next_sigma:;
   }while(next_permutation(sigma.begin(), sigma.end()));
   return {-1};
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> w(n);
   for(int i=0; i<n; ++i){
      scanf("%d", &w[i]);
   }
   vector<int> b(n);
   for(int i=0; i<m; ++i){
      int ki; scanf("%d", &ki);
      while(ki-- > 0){
         int j; scanf("%d", &j);
         b[j-1] = i;
      }
   }
   auto sigma = solve(n, m, w.data(), b.data());
   for(size_t i=0; i<sigma.size(); ++i){
      printf("%d%c", sigma[i], " \n"[i+1==sigma.size()]);
   }
}
