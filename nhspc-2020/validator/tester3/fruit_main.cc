#include"line_parser.hh"
#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
using namespace tester3;
using i64 = long long;
Parser<int> parse;

#define BAD_FORMAT "bad format"
#define BAD_PACK "bad pack"
#define BAD_RANGE "bad range"

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
   extern int const N, W;
   auto nm = read_ints(2);
   int n = nm[0], m = nm[1];
   if(n<1 || n>N || m<1 || m>n){
      throw BAD_RANGE;
   }
   auto w = read_ints(n);
   if(!all_of(w.cbegin(), w.cend(), [](int wi){
      return 1<=wi && wi<=W;
   })){
      throw BAD_RANGE;
   }
   vector<bool> vis(n);
   i64 sk = 0;
   while(m-- > 0){
      string line = read_line();
      if(line.empty() || line.back()!='\n'){
         throw BAD_FORMAT;
      }
      line.pop_back();
      auto tokens = string_split(line);
      optional<int> p;
      if(tokens.empty() || !(p=parse(tokens[0])) || *p<0 || *p>n || (size_t)*p!=tokens.size()-1){
         throw BAD_FORMAT;
      }
      int k = *p; sk += k;
      for(int i=1; i<=k; ++i){
         if(!(p=parse(tokens[i])) || *p<1 || *p>n){
            throw BAD_FORMAT;
         }
         if(vis[*p-1]){
            throw BAD_PACK;
         }
         vis[*p-1] = true;
      }
   }
   if(sk != n){
      throw BAD_PACK;
   }
   if(!read_line().empty()){
      throw BAD_FORMAT;
   }
}catch(char const *err){
   puts(err);
   return 1;
}
