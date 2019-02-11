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
// DYNAMIC SEG TREE TAKEN FROM https://ideone.com/hdI5aX
struct node {
  int from, to;
  long long value, lazy;
  node *left, *right;
  node() {
    from=1;
    to=1e18;
    value=1;
    lazy=0;
    left=NULL;
    right=NULL;
  }
  void extend() {
    if(left==NULL) {
      left=new node();
      right=new node();
      left->from=from;
      left->to=(from+to)>>1;
      right->from=((from+to)>>1)+1;
      right->to=to;
    }
  }
};
 
node *root;
int tests,n,queries;
 
void update_tree(node *curr, int left, int right, long long value) {
  if(curr->lazy) {
    curr->value+=curr->lazy;
    if(curr->from!=curr->to) {
      curr->extend();
      curr->left->lazy+=curr->lazy;
      curr->right->lazy+=curr->lazy;
    }
    curr->lazy=0;
  }
  if((curr->from)>(curr->to) || (curr->from)>right || (curr->to)<left) return;
  if(curr->from>=left && curr->to<=right) {
    curr->value+=value;
    if(curr->from!=curr->to) {
      curr->extend();
      curr->left->lazy+=value;
      curr->right->lazy+=value;
    }
    return;
  }
  curr->extend();
  update_tree(curr->left,left,right,value);
  update_tree(curr->right,left,right,value);
  curr->value=max(curr->left->value,curr->right->value);
}
 
long long query_tree(node *curr, int left, int right) {
  if((curr->from)>(curr->to) || (curr->from)>right || (curr->to)<left) return 0;
  if(curr->lazy) {
    curr->value+=curr->lazy;
    curr->extend();
    curr->left->lazy+=curr->lazy;
    curr->right->lazy+=curr->lazy;
    curr->lazy=0;
  }
  if(curr->from>=left && curr->to<=right) return curr->value;
  long long q1,q2;
  curr->extend();
  q1=query_tree(curr->left,left,right);
  q2=query_tree(curr->right,left,right);
  return max(q1,q2);
}
int32_t main(){
	
}