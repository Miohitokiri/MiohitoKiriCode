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
#define SP(a,b) swap ( a, b )
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
#define SZ(n) ( int ) n.size()
#define CLR(n) n.clear()
#define BEG(n) n.begin()
#define END(n) n.end()
#define EMP(n) n.empty()
#define RSZ(n,s) n.resize ( s )
#define ALL(n) BEG ( n ), END ( n )
#define PIO(n) REPALL ( i, n ) cout << i << ' '; cout << '\n'

// define set
typedef set < int > si;
typedef set < LL > sl;
#define FID(n,Index) n.find ( Index ) != n.end()

// greph
#define GRE(T,edge) vec < T > edge[maxN]
#define UNI(u,v,edge) edge[u].pb ( v ), edge[v].pb ( u )
#define UNIw(u,v,w,edge) edge[u].pb ( mp ( v, w ) ), edge[v].pb ( mp ( u, w ) )

// IO
#define GL(n) getline ( cin, n )

// define stack, queue, pri-queue
template < class T > using stack = stack < T, vec < T > >;
template < class T > using MaxHeap = priority_queue < T >;
template < class T > using MinHeap = priority_queue < T, vec < T >, greater < T > >;

// define stringstream
#define sstr stringstream

// number~ remember change maxN
#define INF 0x3f3f3f3f
#define maxN 100005

// ready~ go!
// let's coding and have fun!
// I can solve this problem!

struct piece{
	int l, r, sz;
};

struct node{
	piece fro, bck, ma;
} seg[maxN << 2];
int Index, value, data[maxN];

inline bool same ( piece a, piece b ){
	return a.sz == b.sz && a.l == b.l && a.r == b.r;
}

inline node up ( node L, node R ){
	node res;
	piece stop;

	if ( same ( L.fro, L.bck ) && same ( R.fro, R.bck ) && data[L.bck.r] + 1 == data[R.fro.l] )
		res.fro = res.bck = res.ma = piece { L.fro.l, R.fro.r, L.fro.sz + R.fro.sz };
	else{
		res.fro = L.fro;
		res.bck = R.bck;
		res.ma = ( L.ma.sz > R.ma.sz ? L.ma : R.ma );

		if ( data[L.bck.r] + 1 == data[R.fro.l] ){
			stop.l = L.bck.l;
			stop.r = R.fro.r;
			stop.sz = L.bck.sz + R.fro.sz;
			if ( same ( R.fro, R.bck ) )
				res.bck = stop;
			if ( same ( L.fro, L.bck ) )
				res.fro = stop;

			res.ma = ( res.ma.sz > stop.sz ? res.ma : stop );
		}
	}

	return res;
}


inline void build ( int n, int l, int r ){
	if ( l == r ){
		seg[n].fro.l = seg[n].bck.l = seg[n].ma.l = seg[n].fro.r = seg[n].bck.r = seg[n].ma.r = l;
		seg[n].fro.sz = seg[n].bck.sz = seg[n].ma.sz = 1;
	}
	else{
		int mid = ( l + r ) >> 1, leftSon = n << 1, rightSon = leftSon | 1;
		build ( rightSon, mid + 1, r );
		build ( leftSon, l, mid );

		seg[n] = up ( seg[leftSon], seg[rightSon] );
	}
}

inline void update ( int n, int l, int r ){
	if ( l == r ){
		seg[n].fro.l = seg[n].bck.l = seg[n].ma.l = seg[n].fro.r = seg[n].bck.r = seg[n].ma.r = l;
		data[l] = value;
	}
	else{
		int mid = ( l + r ) >> 1, leftSon = n << 1, rightSon = leftSon | 1;
		if ( mid < Index )
			update ( rightSon, mid + 1, r );
		else
			update ( leftSon, l, mid );

		seg[n] = up ( seg[leftSon], seg[rightSon] );
	}
}

inline node query ( int n, int l, int r, int nowL, int nowR ){
	if ( l <= nowL && nowR <= r )
		return seg[n];
	int mid = ( nowL + nowR ) >> 1, leftSon = n << 1, rightSon = leftSon | 1;
	if ( mid < l )
		return query ( rightSon, l, r, mid + 1, nowR );
	else if ( r <= mid )
		return query ( leftSon, l, r, nowL, mid );
	else
		return up ( query ( leftSon, l, mid, nowL, mid ), query ( rightSon, mid + 1, r, mid + 1, nowR ) );
}

int main(){
	ios::sync_with_stdio ( false );
	cin.tie ( 0 );
	cout.tie ( 0 );

	int n, q, type, p, h, l, r;
	cin >> n;
	REPP ( i, 1, n + 1 ) cin >> data[i];
	build ( 1, 1, n );

	cin >> q;
	while ( q-- ){
		cin >> type >> Index >> value;
		if ( type == 1 )
			update ( 1, 1, n );
		else if ( type == 2 )
			cout << query ( 1, Index, value, 1, n ).ma.sz << '\n';
	}
}