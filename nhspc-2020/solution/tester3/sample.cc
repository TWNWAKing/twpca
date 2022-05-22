#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
using namespace std;

int read_sample(){
   string s; cin >> s;
   int res = 0;
   for(char c: s){
      res |= 1<<(c-'a');
   }
   return res;
}

int relation(int a, int b){
   if(a == b) return 0;
   if((a&b) == 0) return 1;
   if((a&b) == b) return 2;
   if((a&b) == a) return 3;
   return 4;
}

int main(){
   int n; cin >> n;
   int x = read_sample(), x1 = -1, x2 = -1;
   vector<int> s(n);
   int p[6]{};
   for(int i=0; i<n; ++i){
      s[i] = read_sample();
      int r = relation(s[i], x);
      ++p[r];
      if(r == 4){
         x1 = x&s[i], x2 = x-x1;
      }
   }
   auto test = [&s](int xi){
      return all_of(s.cbegin(), s.cend(), [xi](int sj){
         return relation(xi, sj) != 4;
      });
   };
   p[5] = 2*(test(x1) && test(x2));
   printf("%d %d %d %d %d\n", p[1], p[2], p[3], p[4], p[5]);
}
