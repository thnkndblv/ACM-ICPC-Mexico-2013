#include "bits/stdc++.h"

using namespace std;

typedef long long Long;

char num[ 102 ];    // Number given as input
int Count[ 10 ];    // Count[ i ]: How many times appears digit "i" in num

Long C[ 102 ][ 102 ];   // Combinatorics: C[n][k]

Long mod(Long n, Long m = (1e9 + 7)) { return (n % m + m) % m; }

// Dynamic Programming
Long dp[ 10 ][ 5000 ][ 11 ];
/********************************************************** 
*   dp[ dig ][ n ][ rem ]: How many valid combinations we
*   can obtain if we need to distribute digits dig, dig+1, ..., 9
*   in n even positions and m odd positions, and the actual remainder
*   modulo 11 is "rem".
****************************************************************/
Long solve(int dig, int n, int m, int rem)
{
    if ( dig == 10 ) return (rem == 0) ? 1LL : 0LL;
    
    Long &ret = dp[ dig ][ n ][ rem ];
    if ( ret != -1LL ) return ret;

    ret = 0LL;

    for (int i = 0; i <= Count[ dig ]; i++)
    {
        int j = Count[ dig ] - i;
        if ( i > n ) break;
        if ( j > m ) continue;
        
        int r = rem + dig * (i - j);
        r = (r % 11 + 11) % 11;
        ret = mod( ret + mod( mod( C[n][i] * C[m][j] ) * solve( dig+1, n-i, m-j, r ) ) );
    }

    return ret;
}

int main()
{
    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= i; j++)
            if ( j==0 || j ==i ) C[i][j] = 1LL;
            else C[i][j] = mod( C[i-1][j] + C[i-1][j-1] );

    while ( gets( num ) )
    {
        int N = strlen( num );
        memset( Count, 0, sizeof Count );
        for (int i = 0; i < N; i++) Count[ num[ i ] - '0' ]++;

        Long ans = 0LL;
        for (int i = 1; i < 10; i++) if ( Count[ i ] > 0 )
        {
            Count[ i ]--;

            memset( dp, -1, sizeof dp );
            ans = mod( ans + solve( 0, (N - 1) / 2, (N-1) - (N-1)/2, i ));

            Count[ i ]++;
        }

        printf("%lld\n", ans);
    }
    
    return 0;
}
