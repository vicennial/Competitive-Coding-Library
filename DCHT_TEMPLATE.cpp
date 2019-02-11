//Gvs Akhil (Vicennial)
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define ld(a) while(a--)
#define tci(v,i) for(auto i=v.begin();i!=v.end();i++)
#define tcf(v,i) for(auto i : v)
#define all(v) v.begin(),v.end()
#define rep(i,start,lim) for(long long (i)=(start);i<(lim);i++)
#define sync ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define osit ostream_iterator
#define INF 		0x3f3f3f3f
#define LLINF       1000111000111000111LL
#define PI 			3.14159265358979323
#define endl '\n'
#define trace1(x)                cerr<<#x<<": "<<x<<endl
#define trace2(x, y)             cerr<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl
#define trace3(x, y, z)          cerr<<#x<<":" <<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl
#define trace4(a, b, c, d)       cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl
#define trace5(a, b, c, d, e)    cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<" | "<<#e<< ": "<<e<<endl
#define trace6(a, b, c, d, e, f) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<" | "<<#e<< ": "<<e<<" | "<<#f<<": "<<f<<endl
const int N=1000006;
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
typedef vector<long long> vll;
typedef vector<vll> vvll;
typedef long double ld;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef tuple<int,int,int> iii;
typedef set<int> si;
typedef complex<double> pnt;
typedef vector<pnt> vpnt;
typedef priority_queue<ii,vii,greater<ii> > spq;
const ll MOD=1000000007LL;
template<typename T> T gcd(T a,T b){if(a==0) return b; return gcd(b%a,a);}
template<typename T> T power(T x,T y,ll m=MOD){T ans=1;while(y>0){if(y&1LL) ans=(ans*x)%m;y>>=1LL;x=(x*x)%m;}return ans%m;}
// SOURCE : http://codeforces.com/blog/entry/11339 

/*
 * Dynamic version of data structure
 * to be used in dynamic programming optimisation
 * called "Convex Hull trick"
 * 'Dynamic' means that there is no restriction on adding lines order
 */
class ConvexHullDynamic // 0-Min,1-Max
{
    typedef long long coef_t;
    typedef long long coord_t;
    typedef long long val_t;
 
    /*
     * Line 'y=a*x+b' represented by 2 coefficients 'a' and 'b'
     * and 'xLeft' which is intersection with previous line in hull(first line has -INF)
     */
private:
    struct Line
    {
        coef_t a, b;
        double xLeft;
 
        enum Type {line, maxQuery, minQuery} type;
        coord_t val;
 
        explicit Line(coef_t aa=0, coef_t bb=0) : a(aa), b(bb), xLeft(-INFINITY), type(Type::line), val(0) {}
        val_t valueAt(coord_t x) const { return a*x+b; }
        friend bool areParallel(const Line& l1, const Line& l2) { return l1.a==l2.a; }
        friend double intersectX(const Line& l1, const Line& l2) { return areParallel(l1,l2)?INFINITY:1.0*(l2.b-l1.b)/(l1.a-l2.a); }
        bool operator<(const Line& l2) const
        {
            if (l2.type == line)
                return this->a     < l2.a;
            if (l2.type == maxQuery)
                return this->xLeft < l2.val;
            if (l2.type == minQuery)
                return this->xLeft > l2.val;
        }
    };
 
private:
    bool            isMax; //whether or not saved envelope is top(search of max value)
    std::set<Line>  hull;  //envelope itself
 
private:
    /*
     * INFO:        Check position in hull by iterator
     * COMPLEXITY:  O(1)
     */
    bool hasPrev(std::set<Line>::iterator it) { return it!=hull.begin(); }
    bool hasNext(std::set<Line>::iterator it) { return it!=hull.end() && std::next(it)!=hull.end(); }
 
    /*
     * INFO:        Check whether line l2 is irrelevant
     * NOTE:        Following positioning in hull must be true
     *              l1 is next left to l2
     *              l2 is right between l1 and l3
     *              l3 is next right to l2
     * COMPLEXITY:  O(1)
     */
    bool irrelevant(const Line& l1, const Line& l2, const Line& l3) { return intersectX(l1,l3) <= intersectX(l1,l2); }
    bool irrelevant(std::set<Line>::iterator it)
    {
        return hasPrev(it) && hasNext(it)
               && (    isMax && irrelevant(*std::prev(it), *it, *std::next(it))
                       || !isMax && irrelevant(*std::next(it), *it, *std::prev(it)) );
    }
 
    /*
     * INFO:        Updates 'xValue' of line pointed by iterator 'it'
     * COMPLEXITY:  O(1)
     */
    std::set<Line>::iterator updateLeftBorder(std::set<Line>::iterator it)
    {
        if (isMax && !hasPrev(it) || !isMax && !hasNext(it))
            return it;
 
        double val = intersectX(*it, isMax?*std::prev(it):*std::next(it));
        Line buf(*it);
        it = hull.erase(it);
        buf.xLeft = val;
        it = hull.insert(it, buf);
        return it;
    }
 
public:
    explicit ConvexHullDynamic(bool isMax): isMax(isMax) {}
    
    /*
     * INFO:        Adding line to the envelope
     *              Line is of type 'y=a*x+b' represented by 2 coefficients 'a' and 'b'
     * COMPLEXITY:  Adding N lines(N calls of function) takes O(N*log N) time
     */
    void addLine(coef_t a, coef_t b)
    {
        //find the place where line will be inserted in set
        Line l3 = Line(a, b);
        auto it = hull.lower_bound(l3);
 
        //if parallel line is already in set, one of them becomes irrelevant
        if (it!=hull.end() && areParallel(*it, l3))
        {
            if (isMax && it->b < b || !isMax && it->b > b)
                it = hull.erase(it);
            else
                return;
        }
 
        //try to insert
        it = hull.insert(it, l3);
        if (irrelevant(it)) { hull.erase(it); return; }
 
        //remove lines which became irrelevant after inserting line
        while (hasPrev(it) && irrelevant(std::prev(it))) hull.erase(std::prev(it));
        while (hasNext(it) && irrelevant(std::next(it))) hull.erase(std::next(it));
 
        //refresh 'xLine'
        it = updateLeftBorder(it);
        if (hasPrev(it))
            updateLeftBorder(std::prev(it));
        if (hasNext(it))
            updateLeftBorder(std::next(it));
    }
    /*
     * INFO:        Query, which returns max/min(depends on hull type - see more info above) value in point with abscissa 'x'
     * COMPLEXITY:  O(log N), N-amount of lines in hull
     */
    val_t getBest(coord_t x) const
    {
        Line q;
        q.val = x;
        q.type = isMax ? Line::Type::maxQuery : Line::Type::minQuery;
 
        auto bestLine = hull.lower_bound(q);
        if (isMax) --bestLine;
        return bestLine->valueAt(x);
    }
    void clear(){
        hull.clear();
    }
};
//dp[n]=max{dp[k]+val};
ConvexHullDynamic dp(0); //0-Min,1-Max
int32_t main(){	

}