#include<random>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;
using Unif = uniform_int_distribution<>;
mt19937_64 RNG(0xC8763);

struct Ore{
   int w, p;
   Ore() = default;
   constexpr Ore(int w, int p) noexcept: w(w), p(p){}
};

int conti_knapsack(Ore *a, int m, int l, int r){
   if(l > r) return 0;
   if(l == r){
      return (m<a[l].w? m: a[l].w)*a[l].p;
   }
   int i = Unif(l, r)(RNG), piv = l;
   swap(a[l], a[i]);
   for(int j=l+1; j<=r; ++j){
      if(a[j].p>a[l].p || a[j].p==a[l].p && j>i){
         swap(a[++piv], a[j]);
      }
   }
   swap(a[piv], a[l]);
   int lw = 0;
   for(int j=l; j<piv; ++j){
      lw += a[j].w;
   }
   if(m < lw){
      return conti_knapsack(a, m, l, piv-1);
   }
   int res = 0;
   for(int j=l; j<piv; ++j){
      res += a[j].w*a[j].p;
   }
   if(m <= lw+a[piv].w){
      return res + (m-lw)*a[piv].p;
   }
   return res + a[piv].w*a[piv].p + conti_knapsack(a, m-lw-a[piv].w, piv+1, r);
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<Ore> a(n);
   for(int i=0; i<n; ++i){
      scanf("%d%d", &a[i].w, &a[i].p);
   }
   printf("%d\n", conti_knapsack(a.data(), m, 0, n-1));
}
