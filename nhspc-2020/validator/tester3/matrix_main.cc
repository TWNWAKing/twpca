#include"line_parser.hh"
#include"number_theory.hh"
#include<vector>
using namespace std;
using namespace tester3;
using i64 = long long;
Parser<int> parse;

#define BAD_FORMAT "bad format"
#define BAD_MATRICES "bad matrices"
#define BAD_PRIME "bad prime"
#define BAD_RANGE "bad range"
#define BAD_SUBTASK "bad subtask"

vector<int> read_ints(size_t n){
   string line = read_line();
   if(line.empty() || line.back()!='\n'){
      throw BAD_FORMAT;
   }
   line.pop_back();
   vector<int> res;
   res.reserve(n);
   for(auto const &w: string_split(line)){
      optional<int> p;
      if(res.size()==n || !(p = parse(w))){
         throw BAD_FORMAT;
      }
      res.push_back(*p);
   }
   if(res.size() < n){
      throw BAD_FORMAT;
   }
   return res;
}

int main() try{
   constexpr int N = 2'800;
   constexpr int maxP = 49'999'999;
   constexpr int minP[]{0, N+1, N+1, 37};
   constexpr int minR[]{0, 1, 2, 0};
   constexpr int maxR[]{0, 1, 2, N};
   extern int const minSUBTASK, maxSUBTASK;
   static int a[N][N], b[N][N], row_cnt[N];
   static bool c[N][N];
   int subtask = read_ints(1)[0];
   if(subtask<minSUBTASK || subtask>maxSUBTASK){
      throw BAD_RANGE;
   }
   auto np = read_ints(2);
   int n = np[0], p = np[1];
   if(n<2 || n>N || p<minP[subtask] || p>maxP){
      throw BAD_RANGE;
   }
   if(!primality_test(p)){
      throw BAD_PRIME;
   }
   for(int i=0; i<n; ++i){
      auto ai = read_ints(n);
      for(int j=0; j<n; ++j){
         if(ai[j]<0 || ai[j]>=p){
            throw BAD_RANGE;
         }
         a[i][j] = ai[j];
      }
   }
   for(int i=0; i<n; ++i){
      auto bi = read_ints(n);
      for(int j=0; j<n; ++j){
         if(bi[j]<0 || bi[j]>=p){
            throw BAD_RANGE;
         }
         b[j][i] = bi[j];
      }
   }
   if(!read_line().empty()){
      throw BAD_FORMAT;
   }
#pragma omp parallel for collapse(2)
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      i64 cij = 0;
      for(int k=0; k<n; ++k){
         cij += (i64)a[i][k]*b[j][k];
      }
      c[i][j] = cij%p;
   }
   int cnt = 0;
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(c[i][j]){
      ++cnt;
      ++row_cnt[i];
   }
   if(cnt<1 || cnt>2*n){
      throw BAD_MATRICES;
   }
   for(int i=0; i<n; ++i){
      if(row_cnt[i]<minR[subtask] || row_cnt[i]>maxR[subtask]){
         throw BAD_SUBTASK;
      }
   }
}catch(char const *err){
   puts(err);
   return 1;
}
