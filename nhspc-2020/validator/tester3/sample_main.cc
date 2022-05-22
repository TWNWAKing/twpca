#include"line_parser.hh"
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
using namespace tester3;
Parser<int> parse;
extern char const C;
extern int const P5;

#define BAD_FORMAT "bad format"
#define BAD_RANGE "bad range"
#define BAD_SAMPLES "bad samples"

int read_sample(int max_len = 26){
   auto s = read_line();
   if(s.size()<2 || s.size()>max_len+1 || s.back()!='\n'){
      throw BAD_FORMAT;
   }
   s.pop_back();
   if(!all_of(s.cbegin(), s.cend(), [](char c){
      return 'a'<=c && c<=C;
   })){
      throw BAD_RANGE;
   }
   int res = 0;
   for(char c: s){
      if(res & 1<<c-'a'){
         throw BAD_FORMAT;
      }
      res |= 1<<c-'a';
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

int main() try{
   auto line1 = read_line();
   if(line1.empty() || line1.back()!='\n'){
      throw BAD_FORMAT;
   }
   line1.pop_back();
   int n;
   if(auto p = parse(line1); !p){
      throw BAD_FORMAT;
   }else{
      n = *p;
      if(n<1 || n>18){
         throw BAD_RANGE;
      }
   }
   int x = read_sample(20);
   vector<int> s(n);
   for(int i=0; i<n; ++i){
      s[i] = read_sample();
   }
   if(!read_line().empty()){
      throw BAD_FORMAT;
   }
   for(int i=0; i<n; ++i) for(int j=i+1; j<n; ++j){
      if(int r=relation(s[i], s[j]);  r==0 || r==4){
         throw BAD_SAMPLES;
      }
   }
   int x1, x2;
   if(auto it = find_if(s.cbegin(), s.cend(), [x](int si){
      return relation(x, si) == 4;
   }); it == s.cend()){
      throw BAD_SAMPLES;
   }else x1 = x&*it, x2 = x-x1;
   auto test = [&s](int xi){
      return all_of(s.cbegin(), s.cend(), [xi](int si){
         return relation(si, xi) != 4;
      });
   };
   int p5 = 2*(test(x1) && test(x2));
   if(p5 > P5){
      throw BAD_RANGE;
   }
}catch(char const *err){
   puts(err);
   return 1;
}
