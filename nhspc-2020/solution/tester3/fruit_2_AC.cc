#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

bool dfs(int n, int m, int const *w, int const *b, int u, int *p, int *s){
   if(u == 0){
      return true;
   }
   int j = min_element(s, s+m) - s;
   for(int i=0; i<n; ++i) if(u&1<<i && b[i]==j && p[u-(1<<i)]==-1){
      p[u-(1<<i)] = i;
      s[j] += w[i];
      if(dfs(n, m, w, b, u-(1<<i), p, s)){
         return true;
      }
      s[j] -= w[i];
   }
   return false;
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
   vector<int> p(1<<n, -1), s(m);
   if(dfs(n, m, w.data(), b.data(), (1<<n)-1, p.data(), s.data())){
      int u = 0;
      vector<int> sigma(n);
      for(int i=n; i-->0; ){
         sigma[i] = p[u]+1;
         u |= 1<<p[u];
      }
      for(int i=0; i<n; ++i){
         printf("%d%c", sigma[i], " \n"[i==n-1]);
      }
   }else puts("-1");
}
