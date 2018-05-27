// by. MiohitoKiri5474
#include<bits/stdc++.h>

#pragma GCC optimize ( "O3" )
#pragma loop_opt ( on )

using namespace std;

typedef long long LL;

// define tools
#define REPP(i,f,s) for ( int i = f ; i < s ; i++ )
#define REPM(i,f,s) for ( int i = f ; i >= s ; i-- )
#define REPALL(i,n) for ( auto &i: n )
#define debuger cout << "111\n"
#define MEM(n,i) memset ( n, i, sizeof n )

// define pair
typedef pair < LL, LL > pll;
typedef pair < int, int > pii;
#define F first
#define S second
#define mp make_pair

// define vector && some stl's api
template < class T > using vec = vector < T >;
typedef vec < int > vi;
typedef vec < LL > vl;
#define pb push_back
#define ep emplace_back
#define REV reverse
#define SZ(n) ( int ) n.size()
#define CLR(n) n.clear()
#define BEG(n) n.begin()
#define END(n) n.end()
#define EMP(n) n.empty()
#define RSZ(n,s) n.resize ( s )
#define ALL(n) BEG ( n ), END ( n )
#define PIO(n) REPALL ( i, n ) cout << i << ' '; cout << '\n'
#define GETDATA(data,n) RSZ ( data, n ); REPALL ( i, data ) cin >> i

// define set
typedef set < int > si;
typedef set < LL > sl;
#define FID(n,Index) ( n.find ( Index ) != n.end() )

// graph
#define GRE(T,edge) vec < T > edge[maxN]
#define UNI(u,v,edge) edge[u].pb ( v ), edge[v].pb ( u )
#define UNIw(u,v,w,edge) edge[u].pb ( mp ( v, w ) ), edge[v].pb ( mp ( u, w ) )

// IO
#define GL(n) getline ( cin, n )

// define stack, queue, pri-queue
template < class T > using stack = stack < T, vec < T > >;
template < class T > using MaxHeap = priority_queue < T, vec < T >, less < T > >;
template < class T > using MinHeap = priority_queue < T, vec < T >, greater < T > >;

// define stringstream
#define sstr stringstream

// number~ remember change maxN
#define INF 0x3f3f3f3f
#define NEG_INF 0x8f8f8f8f
#define maxN 100005
#define maxLog 17

// ready~ go!
// let's go coding and have fun!
// I can solve this problem!

// sparse table
// RMQ ( segment max )
int table[maxN][maxLog + 5], basic[maxN], mul[maxLog + 5];

int main(){
	ios::sync_with_stdio ( false );
	cin.tie ( 0 );
	cout.tie ( 0 );

	int n, m, l, r;
	cin >> n >> m;
	REPP ( i, 0, n ){
		cin >> basic[i];
		table[i][0] = basic[i];
	}
	mul[0] = 1;
	for ( int i = 1 ; i <= maxLog ; i++ )
		mul[i] = mul[i - 1] << 1;

	for ( int j = 1 ; ( 1 << j ) <= n ; j++ ){
		for ( int i = 0 ; i + ( 1 << j ) <= n ; i++ ){
			table[i][j] = max ( table[i][j - 1], table[i + ( 1 << ( j - 1 ) )][j - 1] );
		}
	}

	while ( m-- ){
		cin >> l >> r;
		if ( l > r )
			swap ( l, r );
		int k = log2 ( r - l + 1 );
		cout << max ( table[l][k], table[r - ( 1 << k ) + 1][k] ) << '\n';
	}
}