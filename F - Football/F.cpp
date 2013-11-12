#include "bits/stdc++.h"

using namespace std;

vector< int > goalDiff;
int sa[ 100005 ];

int main()
{
    int N, G;

    while ( scanf("%d %d", &N, &G) == 2 )
    {
        int S, R;

        goalDiff.clear();
        int earnedPoints = 0;
        goalDiff.push_back( 0 );
        for (int i = 0; i < N; i++)
        {
            scanf("%d %d", &S, &R);
            if ( S > R ) earnedPoints += 3;
            else goalDiff.push_back( R - S );
        }

        sort( goalDiff.begin(), goalDiff.end() );
        sa[ 0 ] = 0;
        for (int i = 1; i < goalDiff.size(); i++) sa[ i ] = sa[ i - 1 ] + goalDiff[ i ];

        int ans = 0;

        for (int i = 0; i < goalDiff.size(); i++)
        {
            if ( sa[ i ] > G ) break;
            int le = i;
            int ri = goalDiff.size() - 1;
            int remG = G - sa[ i ];
            while ( le < ri )
            {
                int mid = (le + ri + 1) / 2;
                if ( (sa[ mid ] - sa[ i ]) + (mid - i) > remG ) ri = mid - 1;
                else le = mid;
            }

            ans = max( ans, earnedPoints + i + 3 * (le - i) );
        }

        printf("%d\n", ans);
    }

    return 0;
}
