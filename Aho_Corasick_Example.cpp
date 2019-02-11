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
const int MAXN=5000,sigma=52;
int to[5000][sigma],sz=1,term[MAXN],link[MAXN];
vi id[MAXN];
int conv(char c){
	if(c<='z' && c>='a') return c-'a';
	return c-'A';
}
void add(string &s,int qn){ // adding to trie
	int cur=0;
	tcf(s,c){
		if(!to[cur][conv(c)]){
			to[cur][conv(c)]=sz++;
		}
		cur=to[cur][conv(c)];
	}
	term[cur]=cur; //points to termination node.
	id[cur].eb(qn);
	// trace2(cur,qn);
}
void push_links(){
	int que[sz];
	int st=0,fi=1;
	que[0]=0;
	while(st<fi){ // bfs
		int V=que[st++]; //current node
		int U=link[V]; // suffix link of node
		if(!term[V]) term[V]=term[U]; // if no string ends in node v, assign it the terminating node of its suffix link. (abc->bc) if bc is a word we want
		rep(c,0,sigma){ // all characters
			if(to[V][c]){ // if contains an edge with this character
				link[to[V][c]]=V?to[U][c]:0; // suffix link of next node = node obtained by following edge with character c of curents node's suffix link ( similar to kmp)
				que[fi++]=to[V][c]; // add to bfs
			}
			else{
				to[V][c]=to[U][c]; // if no edge, assign to suffix links edge. We already calculated all previous node edges so this also works.
			}
		}
	}
}
int qa[MAXN];
int32_t main(){ // http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1620
	sync;
	int t; cin>>t;
	ld(t){
		memset(to,0,sizeof(to)); sz=1; memset(term,0,sizeof(term)); memset(term,0,sizeof(term)); rep(i,0,MAXN) id[i].clear(); memset(qa,0,sizeof(qa));
		string s; cin>>s;
		int q; cin>>q;
		rep(i,0,q){
			string s; cin>>s;
			add(s,i);
		}
		push_links();
		int cur=0;
		tcf(s,c){
			cur=to[cur][conv(c)];
			tcf(id[cur],x) qa[x]=1;
		}
		rep(i,0,q){
			if(qa[i]) cout<<"y"<<endl;
			else cout<<"n"<<endl;
		}
	}
}