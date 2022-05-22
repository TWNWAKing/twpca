#include<numeric>
#include<random>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

int p;
vector<vector<int>> a, b, rv;

void dac(vector<int> const &cand, int l, int r, vector<vector<bool>> &nontrivial_entry){
   vector<bool> nontrivial_row(cand.size());
   int n_cand2 = 0;
   for(auto &u: rv){
      vector<i64> bu(b.size());
      for(size_t i=0; i<b.size(); ++i){
         for(int j=l; j<=r; ++j){
            bu[i] += (i64)b[i][j]*u[j];
         }
         bu[i] %= p;
      }
      for(size_t i=0; i<cand.size(); ++i) if(!nontrivial_row[i]){
         i64 cui = 0;
         for(size_t j=0; j<bu.size(); ++j){
            cui += a[cand[i]][j]*bu[j];
         }
         if(cui % p){
            nontrivial_row[i] = true;
            ++n_cand2;
         }
      }
      if(n_cand2 == (int)cand.size()){
         break;
      }
   }
   if(l == r){
      for(size_t i=0; i<cand.size(); ++i) if(nontrivial_row[i]){
         nontrivial_entry[cand[i]][l] = true;
      }
   }else{
      int m = l+(r-l)/2;
      vector<int> cand2; cand2.reserve(n_cand2);
      for(size_t i=0; i<cand.size(); ++i) if(nontrivial_row[i]){
         cand2.push_back(cand[i]);
      }
      dac(cand2, l, m, nontrivial_entry);
      dac(cand2, m+1, r, nontrivial_entry);
   }
}

int main(){
   int n;
   scanf("%*d%d%d", &n, &p);
   a.resize(n, vector<int>(n));
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      scanf("%d", &a[i][j]);
   }
   b.resize(n, vector<int>(n));
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      scanf("%d", &b[i][j]);
   }
   mt19937_64 rng(0xC8763);
   uniform_int_distribution<> dis(0, p-1);
   constexpr int T = 5;
   rv.resize(T, vector<int>(n));
   for(int i=0; i<T; ++i) for(int j=0; j<n; ++j){
      rv[i][j] = dis(rng);
   }
   vector<int> cand(n);
   iota(cand.begin(), cand.end(), 0);
   vector<vector<bool>> nontrivial_entry(n, vector<bool>(n));
   dac(cand, 0, n-1, nontrivial_entry);
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(nontrivial_entry[i][j]){
      i64 entry = 0;
      for(int k=0; k<n; ++k){
         entry += (i64)a[i][k]*b[k][j];
      }
      printf("%d %d %d\n", i+1, j+1, (int)(entry%=p));
   }
}
