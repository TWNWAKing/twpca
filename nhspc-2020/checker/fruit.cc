#define CMS
#define TESTSYS
#include"testlib.h"
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

int main(int argc, char **argv){
   registerTestlibCmd(argc, argv);
   ouf.strict = true;
   int s0 = ouf.readInt();
   if(ans.readInt() > 0){
      if(s0 == -1){
         quitf(_wa, "expected a permutation; found -1.");
      }
   }else{
      if(s0 == -1){
         quitf(_ok, "good");
      }
      quitf(_wa, "expected -1; found a permutation.");
   }
   int n = inf.readInt(), m = inf.readInt();
   if(s0<1 || s0>n){
      quitf(_wa, "bad permutation");
   }
   vector<int> sigma(n);
   vector<bool> used(n);
   sigma[0] = s0-1;
   used[s0-1] = true;
   for(int i=1; i<n; ++i){
      ouf.readChar(' ');
      sigma[i] = ouf.readInt(1, n)-1;
      if(used[sigma[i]]){
         quitf(_wa, "bad permutation");
      }
      used[sigma[i]] = true;
   }
   vector<int> w(n);
   for(int i=0; i<n; ++i){
      w[i] = inf.readInt();
   }
   vector<int> a(n);
   for(int i=0; i<m; ++i){
      int ki = inf.readInt();
      while(ki-- > 0){
         a[inf.readInt()-1] = i;
      }
   }
   priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
   for(int i=0; i<m; ++i){
      pq.emplace(0, i);
   }
   vector<int> b(n);
   for(int i: sigma){
      auto [sj, j] = pq.top(); pq.pop();
      b[i] = j;
      pq.emplace(sj+w[i], j);
   }
   if(a != b){
      quitf(_wa, "the permutation doesn't yield the given configuration");
   }
   quitf(_ok, "good");
}
