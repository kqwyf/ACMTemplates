//standard algorithm
#define INF 0x3f3f3f3f3f3f3f3f
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>
#include <stack>
#include <map>
#include <set>

using namespace std;
double const esp=1e-7;
inline bool z(double a) {return abs(a)<esp;}
inline bool at(double a,double b,double c) {return (a<=b&&b<=c)||(a>=b&&b>=c);}
template<typename T> T repmin(T a,T b) {return a==-1||b==-1?a+b+1:min(a,b);}
template<typename T> T repmax(T a,T b) {return a==-1||b==-1?-1:max(a,b);}
template<typename T> bool repless(T a,T b) {return a==-1||b==-1?a>b:a<b;}
template<typename T> int sgn(T a) {return a>0?1:(a<0?-1:0);}
