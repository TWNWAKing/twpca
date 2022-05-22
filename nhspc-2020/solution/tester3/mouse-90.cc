#include<algorithm>
#include<unordered_set>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

struct Maze{
   Maze() = default;
   Maze(int n, int m): n(n), m(m){}
   void set_right_wall(int x, int y){
      wall.insert((x*m+y-1)*2);
   }
   void set_up_wall(int x, int y){
      wall.insert((x*m+y-1)*2+1);
   }
   void print() const{
      printf("%d %d\n", n, m);
      printf("%zu\n", wall.size());
      for(int w: wall){
         int x = w/2/m, y = w/2%m+1;
         if(w%2){
            printf("%d %d %d %d\n", x, y, x, y+1);
         }else printf("%d %d %d %d\n", x, y, x+1, y);
      }
   }
private:
   int n, m;
   unordered_set<int> wall;
};

int main(){
   i64 n; scanf("%lld", &n);
   if(n <= 6){
      Maze(2, n).print();
      return 0;
   }
   n -= 6;
   vector<int> d;
   while(n > 0){
      d.push_back(n%20);
      n /= 20;
   }
   reverse(d.begin(), d.end());
   Maze maze(3*d.size()+3, 3*d.size()+3);
   maze.set_up_wall(1, 2);
   maze.set_up_wall(2, 3);
   switch(d[0]%5){
   case 0:
      maze.set_right_wall(3, 2);
      maze.set_up_wall(4, 1);
      maze.set_up_wall(5, 1);
      break;
   case 1:
      maze.set_right_wall(3, 2);
      maze.set_up_wall(4, 1);
      break;
   case 2:
      maze.set_right_wall(3, 2);
      maze.set_up_wall(4, 2);
      break;
   case 3:
      maze.set_up_wall(4, 1);
      maze.set_up_wall(4, 2);
      maze.set_up_wall(5, 1);
      break;
   case 4:
      maze.set_up_wall(4, 2);
      maze.set_up_wall(5, 1);
      break;
   }
   if(d[0]%5){
      maze.set_right_wall(5, 2);
      maze.set_right_wall(5, 3);
      maze.set_right_wall(5, 4);
   }
   auto set_5ch = [&maze](int i, int q){
      switch(q){
      case 0:
         maze.set_right_wall(3, 3*i+3);
         maze.set_right_wall(3, 3*i+4);
         maze.set_right_wall(3, 3*i+5);
         break;
      case 1:
         maze.set_right_wall(3, 3*i+3);
         maze.set_right_wall(3, 3*i+4);
         break;
      case 2:
         maze.set_right_wall(3, 3*i+3);
         maze.set_right_wall(4, 3*i+4);
         break;
      case 3:
         maze.set_right_wall(4, 3*i+3);
         maze.set_right_wall(4, 3*i+4);
         break;
      }
      if(q){
         for(int j=4; j<=3*i+1; ++j){
            maze.set_up_wall(j, 3*i+5);
         }
      }
   };
   set_5ch(0, d[0]/5);
   if(d[0]/5){
      maze.set_up_wall(4, 5);
   }
   auto set_1ch = [&maze](int i, int r){
      switch(r){
      case 0:
         maze.set_up_wall(3*i+3, 1);
         maze.set_up_wall(3*i+4, 1);
         maze.set_up_wall(3*i+5, 1);
         break;
      case 1:
         maze.set_up_wall(3*i+3, 1);
         maze.set_up_wall(3*i+4, 1);
         break;
      case 2:
         maze.set_up_wall(3*i+3, 1);
         maze.set_up_wall(3*i+4, 2);
         break;
      case 3:
         maze.set_up_wall(3*i+3, 2);
         maze.set_up_wall(3*i+4, 2);
         break;
      case 4:
         maze.set_up_wall(3*i+3, 3);
         maze.set_up_wall(3*i+4, 2);
         maze.set_up_wall(3*i+4, 3);
         break;
      }
      if(r){
         for(int j=2; j<=3*i+1; ++j){
            maze.set_right_wall(3*i+5, j);
         }
      }
   };
   for(size_t i=1; i<d.size(); ++i){
      maze.set_up_wall(3*i+2, 3*i+5);
      maze.set_up_wall(3*i+3, 3*i+5);
      maze.set_up_wall(3*i+4, 3*i+5);
      maze.set_right_wall(3*i+5, 3*i+2);
      maze.set_right_wall(3*i+5, 3*i+3);
      maze.set_right_wall(3*i+5, 3*i+4);
      set_5ch(i, d[i]/5);
      set_1ch(i, d[i]%5);
   }
   maze.set_right_wall(3*d.size()+2, 3*d.size()+2);
   maze.print();
}
