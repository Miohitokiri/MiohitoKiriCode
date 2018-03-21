#include<bits/stdc++.h>
using namespace std;
long long basic[100005], dp[100005], sum[100005];
int main(){
	ios::sync_with_stdio ( false );
	cin.tie ( 0 );
	
	int n;
	while ( cin >> n ){
		memset ( basic, 0, sizeof ( basic ) );
		memset ( dp, 0, sizeof ( dp ) );
		memset ( sum, 0, sizeof ( sum ) );
		cin >> basic[0];
		sum[0] += basic[0];
		// dp[0] = sum[0];
		dp[0] = max ( dp[0], sum[0] );
		if ( sum[0] < 0 )
			sum[0] = 0;
		for ( int i = 1 ; i < n ; i++ ){
			cin >> basic[i];
			sum[i] = basic[i] + sum[i - 1];
			if ( sum[i] < 0 )
				sum[i] = 0;
			dp[i] = max ( sum[i], dp[i - 1] );
		}

		cout << dp[n - 1] << '\n';
	}
}