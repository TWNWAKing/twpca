// Expect: AC
// O(2^26 * n)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 20
#define B(x) (1<<(x))
using namespace std;
int n,m,in[M];

int read_str() {
    int res=0;
    char s[105];
    scanf("%s", s+1);
    int len = strlen(s+1);

    REP(i,1,len) {
        if (s[i]>='a' && s[i]<='z') res |= B(s[i]-'a');
    }
    return res;
}
bool check(int x) {
    REP(i,1,n) {
        int a = x&in[i];
        if (a!=in[i] && a!=x && a!=0) return false;
    }
    return true;
}
int main()
{
    scanf("%d", &n);
    m = read_str();
    REP(i,1,n) in[i] = read_str();

    int a1=0, a2=0, a3=0, a4=0, a5=0;
    REP(i,1,n) {
        int a = m & in[i];
        if (a==0) a1++;
        if (a==m && a!=in[i]) a2++;
        if (a==in[i] && a!=m) a3++;
        if (a!=m && a!=in[i] && a!=0) a4++;
    }

    for (int i=m; i>=0; i=(i-1)&m) {
        int j = m^i;
        if (check(i) && check(j)) a5++;
        if (i==0) break;
    }
    printf("%d %d %d %d %d\n",a1,a2,a3,a4,a5);
    return 0;
}
