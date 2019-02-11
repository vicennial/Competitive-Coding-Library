#include<bits/stdc++.h>
#define sz(a) int((a).size())
#define int long long
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second
#define ld(a) while(a--)
#define tci(v,i) for(auto i=v.begin();i!=v.end();i++)
#define tcf(v,i) for(auto i : v)
#define all(v) v.begin(),v.end()
#define rep(i,start,lim) for(long long (i)=(start);i<(lim);i++)
#define repd(i,start,lim) for(long long (i)=(start);i>=(lim);i--)
#define present(c,x) (find(all(c),x) != (c).end())
#define sync ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define osit ostream_iterator
#define INF 		0x3f3f3f3f
#define LLINF       1000111000111000111LL
#define PI 			3.14159265358979323
#define endl '\n'
#ifdef WIN32
#define getchar_unlocked getchar
#endif
#define gc getchar
#define trace1(x)                cerr<<#x<<": "<<x<<endl
#define trace2(x, y)             cerr<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl
#define trace3(x, y, z)          cerr<<#x<<":" <<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl
#define trace4(a, b, c, d)       cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl
#define trace5(a, b, c, d, e)    cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<" | "<<#e<< ": "<<e<<endl
#define trace6(a, b, c, d, e, f) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<" | "<<#e<< ": "<<e<<" | "<<#f<<": "<<f<<endl
#define N 1000006
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
template<typename T> T sqr(T x){return x*x;}
template<typename T> T gcd(T a,T b){if(a==0) return b; return gcd(b%a,a);}
template<typename T>void read(T &x) { register T c = gc(); x = 0; int t = 0; if (c == '-') t = 1, c = gc(); for (; (c < 48 || c>57); c = gc()); for (; c > 47 && c < 58; c = gc()) { x = (x << 1) + (x << 3) + c - 48; }if (t) x = -x; }
template<typename T> T power(T x,T y,ll m=MOD){T ans=1;while(y>0){if(y&1LL) ans=(ans*x)%m;y>>=1LL;x=(x*x)%m;}return ans%m;} //using this instead of inbuilt pow due to precision issues in that
template<typename T> ll roundp(T x){ll ans=x;if(x-floor(x)<=0.001) ans=floor(x);else if(ceil(x)-x<=0.001) ans=ceil(x);return ans;}
const int cn=2;
const int lastbit=30;
int NEW;
typedef struct node{
	int edges[cn];
}Trie;
Trie trie[N*35]; //N*35 use it.
void initialize(int ind){
	rep(i,0,cn) {
		trie[ind].edges[i]=-1;	
	}
}
void pretrie(){
	initialize(0); NEW++;
}
int ch(int x,int i){
	if(x&(1<<i)) return true;
	return false;
}
void insert(int x,int idc,int idp){
	int curr;
	for(int i=lastbit;i>=0;i--){
		curr=ch(x,i);
		if(1){
			initialize(NEW);
			trie[idc].edges[curr]=NEW++;
		}
		if(idp!=-1){
			trie[idc].edges[curr^1]=trie[idp].edges[curr^1];
			idp=trie[idp].edges[curr];
		}
		idc=trie[idc].edges[curr];
	}
}
int getmax(int x,int ind){
	int curr,req;
	for(int i=lastbit;i>=0;i--){
		curr=ch(x,i);
		req=curr^1;
		if(trie[ind].edges[req]!=-1){
			x|=(1<<i);
			ind=trie[ind].edges[req];
		}
		else if(trie[ind].edges[curr]!=-1){
			x&=~(1<<i);
			ind=trie[ind].edges[curr];
		}
		else break;
	}
	return x;
}
int getmin(int x,int ind){
	int curr;
	for(int i=lastbit;i>=0;i--){
		curr=ch(x,i);
		if(trie[ind].edges[curr]!=-1){
			x&=~(1<<i);
			ind=trie[ind].edges[curr];
		}
		else if(trie[ind].edges[curr^1]!=-1){
			x|=(1<<i);
			ind=trie[ind].edges[curr^1];
		}
		else break;
	}
	return x;
}
int version[N];
int32_t main(){
	pretrie();
	version[0]=0;
	insert(6,0,-1);
	initialize(NEW); version[1]=NEW++;
	insert(5,version[1],version[0]);
//	cout<<getmax(5,version[0])<<endl;
//	cout<<getmax(5,version[1])<<endl;
	cout<<getmin(5,version[0])<<endl;
	cout<<getmin(5,version[1])<<endl;	
}


