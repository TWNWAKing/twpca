#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define MP make_pair
#define F first
#define S second
#define MN_N 1
#define MX_N 18
#define CHARSET "[a-j]{1,10}"
using namespace std;
int n;
string X, s[MX_N + 5];
void check(string x) {
    map<char,bool> vis;
    int len = x.length();
    REP(i,0,len-1) {
        ensuref(!vis[x[i]], "found duplicate char");
        vis[x[i]] = true;
    }
}
set<char> to_set(string x) {
    set<char> res;
    int len = x.length();
    REP(i,0,len-1) {
        res.insert(x[i]);
    }
    return res;
}
set<char> inter(set<char> x,set<char> y) {
    set<char> res;
    set_intersection(x.begin(), x.end(), y.begin(), y.end(), inserter(res, res.begin()));
    return res;
}
bool subset(set<char> x,set<char> y) {
    return includes(x.begin(), x.end(), y.begin(), y.end()) ||
        includes(y.begin(), y.end(), x.begin(), x.end());
}
bool partial_inter(string x,string y) {
    auto sx = to_set(x);
    auto sy = to_set(y);
    auto in = inter(sx, sy);
    return in.size() && (sx != sy) && !subset(sx, sy);
}
int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    // n
    n = inf.readInt(MN_N, MX_N);
    inf.readChar('\n');

    X = inf.readToken(CHARSET, "x");
    check(X);
    inf.readChar('\n');
    REP(i,1,n) {
        s[i] = inf.readToken(CHARSET, "si");
        check(s[i]);
        inf.readChar('\n');
    }
    inf.readEof();

    // partial inter
    REP(i,1,n) REP(j,i+1,n) {
        ensuref(!partial_inter(s[i], s[j]), "%s and %s partial inter", s[i].c_str(), s[j].c_str());
    }

    // equal
    REP(i,1,n) sort(s[i].begin(), s[i].end());
    REP(i,1,n) REP(j,i+1,n) {
        ensuref(s[i] != s[j], "%s and %s equal", s[i].c_str(), s[j].c_str());
    }

    int cnt = 0;
    REP(i,1,n) {
        cnt += partial_inter(X, s[i]) ? 1 : 0;
    }
    ensuref(cnt>=1, "X should partial inter with some other set");
    return 0;
}

