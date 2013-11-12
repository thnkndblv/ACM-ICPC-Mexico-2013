#include "bits/stdc++.h"

using namespace std;

typedef long long Long;

Long C[ 60 ];

Long Count(Long n)
{
    Long ret = 0LL;

    while ( n > 0LL )
    {
        Long m = n & -n;
        n -= m;

        int lsb = __builtin_ctzll( m );
        Long leftBits = __builtin_popcountll( n );

        ret += 1LL + C[ lsb ] + (leftBits << lsb);
    }

    return ret;
}

int main()
{
    C[ 0 ] = 0LL;
    for (int i = 1; i < 60; i++)
    {
        C[ i ] = C[ i - 1 ];
        C[ i ] <<= 1;
        C[ i ] += 1LL << (i - 1);
    }

    Long A, B;
    while ( scanf("%lld %lld", &A, &B) == 2 )
    {
        printf("%lld\n", Count(B) - Count(A-1LL));
    }

    return 0;
}

/*
1000000000000000 10000000000000000
2 12
9007199254740992 9007199254740992
*/