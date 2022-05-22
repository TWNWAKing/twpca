#include"line_parser.hh"
#include<algorithm>
#include<optional>
#include<string>
#include<vector>
#include<cstdio>
using namespace std;
using namespace tester3;
Parser<int> parse;

#define BAD_DAG "cycle found"
#define BAD_FORMAT "bad format"
#define BAD_RANGE "bad range"
#define BAD_VILLAGE1 "there exists a village that is not reachable from 1"

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

void dfs(vector<int> const *g, int u, unsigned char *tag){
   tag[u] = 1;
   for(int v: g[u]){
      switch(tag[v]){
      case 0:
         dfs(g, v, tag);
         break;
      case 1:
         throw BAD_DAG;
      case 2:
         continue;
      }
   }
   tag[u] = 2;
}

int main() try{
   extern const int N, M;
   auto nm = read_ints(2);
   int n = nm[0], m = nm[1];
   if(n<2 || n>N || m<1 || m>M){
      throw BAD_RANGE;
   }
   vector<vector<int>> g(n);
   while(m-- > 0){
      auto a = read_ints(3);
      int u = a[0], v = a[1], w = a[2];
      if(u<1 || u>n || v<1 || v>n || w<-110000 || w>110000){
         throw BAD_RANGE;
      }
      g[u-1].push_back(v-1);
   }
   if(!read_line().empty()){
      throw BAD_FORMAT;
   }
   vector<unsigned char> tag(n);
   dfs(g.data(), 0, tag.data());
   if(any_of(tag.cbegin(), tag.cend(), [](unsigned char t){return t != 2;})){
      throw BAD_VILLAGE1;
   }
}catch(char const *err){
   puts(err);
   return 1;
}
