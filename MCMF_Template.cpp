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
#define INF     0x3f3f3f3f
#define LLINF       1000111000111000111LL
#define PI       3.14159265358979323
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
const int mxN = 40;
const int inf = 2e9;
struct Edgee {
  int to, cost, cap, flow, backEdge;
};
struct MCMF {
  int s, t, n;
  vector<Edgee> g[mxN];
  MCMF(int _s, int _t, int _n) { // source,sink, total nodes
    s = _s, t = _t, n = _n;
  }
  void addEdge(int u, int v, int cost, int cap) { // src,dest,cost,capacity
    Edgee e1 = { v, cost, cap, 0, g[v].size() };
    Edgee e2 = { u, -cost, 0, 0, g[u].size() };
    g[u].push_back(e1); g[v].push_back(e2);
  }
  pair<int, int> minCostMaxFlow() {
    int flow = 0, cost = 0;
    vector<int> state(n), from(n), from_edge(n), d(n);
    deque<int> q;
    while (true) {
      for (int i = 0; i < n; i++)
        state[i] = 2, d[i] = inf, from[i] = -1;
      state[s] = 1; q.clear(); q.push_back(s); d[s] = 0;
      while (!q.empty()) {
        int v = q.front(); q.pop_front(); state[v] = 0;
        for (int i = 0; i < (int) g[v].size(); i++) {
          Edgee e = g[v][i];
          if (e.flow >= e.cap || d[e.to] <= d[v] + e.cost)
            continue;
          int to = e.to; d[to] = d[v] + e.cost;
          from[to] = v; from_edge[to] = i;
          if (state[to] == 1) continue;
          if (!state[to] || (!q.empty() && d[q.front()] > d[to]))
            q.push_front(to);
          else q.push_back(to);
          state[to] = 1;
        }
      }
      if (d[t] == inf) break;
      int it = t, addflow = inf;
      while (it != s) {
        addflow = min(addflow,
            g[from[it]][from_edge[it]].cap
            - g[from[it]][from_edge[it]].flow);
        it = from[it];
      }
      it = t;
      while (it != s) {
        g[from[it]][from_edge[it]].flow += addflow;
        g[it][g[from[it]][from_edge[it]].backEdge].flow -= addflow;
        cost += g[from[it]][from_edge[it]].cost * addflow;
        it = from[it];
      }
      flow += addflow;
    }
    return {cost,flow};
  }
};
main(){

}