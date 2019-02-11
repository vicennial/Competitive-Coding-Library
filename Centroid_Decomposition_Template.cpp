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
vvi g;
const int LF=17;
int par[N],level[N],st[N][LF];
void dfs(int n,int p,int ct){
	par[n]=p;
	level[n]=ct;
	st[n][0]=p;
	tcf(g[n],i){
		if(i==p) continue;
		dfs(i,n,ct+1);
	}
}
void pre(int n){
	for(int j=1;(1<<j)<=n;j++){
		for(int i=0;i<n;i++){
			if(st[i][j-1]!=-1){
				st[i][j]=st[st[i][j-1]][j-1]; 
			}
		}
	}
}
int lca(int u,int v){
	if(level[u]<level[v]) swap(u,v);
	int dist=level[u]-level[v];
	while(dist){ 
		int k=log2(dist); dist-=(1<<k);
		u=st[u][k];
	}
	if(u==v) return u;
	for(int i=LF-1;i>=0;i--){ 
		if(st[u][i]!=-1 && st[u][i]!=st[v][i]){
			u=st[u][i];
			v=st[v][i];
		}
	}
	return par[u];
}
int sc[N],nc,cenpar[N];
bool ch[N];
void subdfs(int n,int p){
	sc[n]=1;
	++nc;
	tcf(g[n],i){
		if(i==p || ch[i]) continue;
		subdfs(i,n);
		sc[n]+=sc[i];
	}
}
int getcen(int n,int p){
	tcf(g[n],i){
		if(i==p || ch[i]) continue;
		if(sc[i]>nc/2) return getcen(i,n);
	}
	return n;
}
char ans[N];
void decompose(int n,int p){
	nc=0;
	subdfs(n,-1);
	int centroid=getcen(n,-1);
	ch[centroid]=1;
	cenpar[centroid]=p;
	tcf(g[centroid],i){
		if(ch[i]) continue;
		decompose(i,centroid);
	}
}
int32_t main(){
	sync;
	int n; cin>>n; g.resize(n);
	rep(i,0,n-1){
		int x,y; cin>>x>>y; --x; --y;
		g[x].eb(y);
		g[y].eb(x);
	}
	rep(i,0,n) rep(j,0,LF) st[i][j]=-1;
	dfs(0,-1,0);
	pre(n);
}
