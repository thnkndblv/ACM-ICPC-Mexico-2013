#include "bits/stdc++.h"

using namespace std;

#define fori(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) fori(i, 0, n)
#define pb push_back

char buff[ 1003 ];
char board[ 102 ][ 102 ];
int row[ 102 ][ 102 ];
int col[ 102 ][ 102 ];

struct Node
{
    int x, a, b;

    Node(){}
    Node(int x, int a, int b)
        :   x(x),
            a(a),
            b(b) {}
};

vector< Node > R;
vector< Node > C;

int matchL[ 10004 ];
int matchR[ 10004 ];
bool seen[ 10004 ];

bool bpm(int u)
{
    int r = R[ u ].x;

    for (int c = R[ u ].a; c < R[ u ].b; c++)
    {
        int v = col[ r ][ c ];
        if ( seen[ v ] ) continue;
        seen[ v ] = true;

        if ( matchR[ v ] < 0 || bpm( matchR[ v ] ) )
        {
            matchL[ u ] = v;
            matchR[ v ] = u;
            return true;
        }
    }

    return false;
}

int main()
{
    int N;

    while ( gets(buff) && sscanf( buff, "%d", &N ) == 1 )
    {
        forn(i, N) gets( board[ i ] );

        R.clear();
        C.clear();

        // Basically here we enumerate every horizontal segment, and we
        // For example in the first test case:
        //  X0000
        //  X1111
        //  22X33
        //  4X555
        //  6666X
        forn(i, N)
        {
            for (int le = 0, ri = 0; le < N; le = ri)
            {
                if ( board[i][le] == '.' )
                {
                    while ( ri < N && board[i][ri] == '.' ) row[ i ][ ri++ ] = R.size();
                    R.pb( Node( i, le, ri ) );
                }
                else ri++;
            }
        }

        // And here we enumerate del vertical segments in same fashion:
        //  X1356
        //  X1356
        //  01X56
        //  0X456
        //  0245X
        forn(j, N)
        {
            for (int top = 0, bottom = 0; top < N; top = bottom)
            {
                if ( board[ top ][ j ] == '.' )
                {
                    while ( bottom < N && board[ bottom ][ j ] == '.' ) col[ bottom++ ][ j ] = C.size();
                    C.pb( Node( j, top, bottom ) );
                }
                else bottom++;
            }
        }

        // Finally just running a Maximum Matching algorithm we get the answer.
        int Count = 0;

        memset( matchL, -1, sizeof matchL );
        memset( matchR, -1, sizeof matchR );
        forn(i, R.size())
        {
            memset( seen, 0, C.size() );
            if ( bpm( i ) ) Count++;
        }

        printf("%d\n", Count);
    }

    return 0;
}
