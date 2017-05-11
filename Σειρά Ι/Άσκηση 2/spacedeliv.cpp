/* Programming Languages 1 :: Homework #1
 * Exercise 2: Space Delivery
 * Michalis Papadopoullos (mechatr0nic.cy@gmail.com)
 * NATIONAL TECHNICAL UNIVERSITY OF ATHENS -- ECE DEPT.
 * Notes: For DEBUGGING information
 *        compile with -DDEBUG flag
 */

// libraries
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <functional>
#include <climits>
// ------------------
using namespace std;

// Macros
#define INF (INT_MAX)
#define MAXN 1000
#define PIZZA_H(x)   (get<0>(x))
#define GETX(x)      (get<1>(x))
#define GETY(x)      (get<2>(x))
#define GET_PATH(x)  (get<3>(x))
#define GET_STEPS(x) (get<4>(x))

typedef tuple<bool,
        int,
        int,
        string,
        int> tuple_t;   // holdsPizza,
                        // coordX
                        // coordY
                        // directions
                        // number of steps

/*  TODO:
 *          * Implement an array PREV which will holds
 *          the character of the current's state last move
 *
 *
 *
 * 
 */


// global variables
priority_queue<tuple_t,
               vector<tuple_t>,     /* priority_queue, with custom lambda comparator */
               function<bool(tuple_t, tuple_t)> > Q( [](tuple_t A, tuple_t B) -> bool {
                       int diff = GET_STEPS(A) - GET_STEPS(B);
                       if (diff > 0) return true;
                       else if (diff == 0) return ( (PIZZA_H(A) - PIZZA_H(B)) >= 0 )? true : false;
                       return false;
                       } );;
                                    // <0> bool::holdsPizza
                                    // <1, 2> coordinates
                                    // <3> path
                                    // <4> number of steps
vector<string> grid;    // our 2D map, as a vector of strings
int N,
    M;      // dimensions of the grid (N x M)
int VISITED[2][MAXN][MAXN];  // VISITED Matrix [2 x 1000 x 1000]
static int  S[2],      // 'start' node coordinates
            E[2];      // 'final' node coordinates
// -----------------

inline void init ()
{
    // initialization routine
    // parse input
    string s;
    while (cin >> s) { // read until '\n'
        grid.push_back (s); // append line
    }
    N = grid.size ();       // number of ROWS
    M = grid.back().length();   // number of COLUMNS

#ifdef DEBUG
    printf ("Dimensions: %d x %d\n", N, M);
#endif
    for (int i = 0; i < N; i++) { // ACCESS ROWS
        for (int j = 0; j < M; j++) { // ACCESS COLUMNS

            VISITED[0][i][j] = VISITED[1][i][j] = INF;

            if ( grid[i][j] == 'S' ) { // Found START coordinates
                S[0] = i, S[1] = j;
            } else if ( grid[i][j] == 'E' ) { // Found END coordinates
                E[0] = i, E[1] = j;
            }
        }
    }
}


inline bool check (tuple_t &c)
{
    if ( (GETX(c) == E[0]) &&
         (GETY(c) == E[1]) ) { // We have found final node
        return true;
    } else
        return false;
}

inline void possibleMoves (tuple_t &c)
{
    string DIR = "LRUD";
    int  xOFFSET[4] = {0, 0, -1, 1};
    int  yOFFSET[4] = {-1, 1, 0, 0};
    for (int i = 0; i < 4; i++) {
        int x = GETX(c) + xOFFSET[i],
            y = GETY(c) + yOFFSET[i],
            steps = GET_STEPS(c) + 2 - PIZZA_H(c);
                    // if we hold pizza then extra cost is +2
                    // otherwise is +1

        if (x < 0 || x >= N) { continue; }
        if (y < 0 || y >= M) { continue; }

        if (grid[x][y] != 'X') {
            if (VISITED[PIZZA_H(c)][x][y] > steps) {
                Q.push(make_tuple(PIZZA_H(c), x, y, GET_PATH(c) + DIR[i], steps));
#ifdef DEBUG
                cout << GET_STEPS(c) << " NEW: " << GET_PATH(c) + DIR[i] << endl;
#endif
            }
        }
    }

}

inline void solve ()
{
    tuple_t c; // current state

    Q.push (make_tuple(0, S[0], S[1], "", 0)); // initial state
    while ( !(Q.empty()) ) { // while QUEUE is not EMPTY
        c = Q.top(); // get first element
        Q.pop(); // remove element

        if ( check (c) && (PIZZA_H(c) == 0) ) {
            // we have found END and we are holding pizza
            // print solution
            cout << GET_STEPS(c) << " " << GET_PATH(c) << endl;
            return;
        }

        // Check adjacent nodes
        if ( VISITED[PIZZA_H(c)][GETX(c)][GETY(c)]
                <= GET_STEPS(c) ) {
            continue; // skip this one
        }

        VISITED[PIZZA_H(c)][GETX(c)][GETY(c)] = GET_STEPS(c);

        // Consider to use wormhole
        if ( grid[GETX(c)][GETY(c)] == 'W' ) { // We are in a wormhole
            Q.push (make_tuple(
                    1 - PIZZA_H(c),
                    GETX(c),
                    GETY(c),
                    GET_PATH(c) + "W",
                    GET_STEPS(c) + 1
            ) );
        }

        // check all possible moves {L,R,U,D}
        possibleMoves (c);

    }
    printf ("NOT POSSIBLE\n");
}

int main (int argc, char *argv[])
{
    if ( argc != 2 ) { exit (EXIT_FAILURE); }

    freopen (argv[1], "r", stdin); // redirect IO
    std::ios::sync_with_stdio(false); // optimization

    init (); // call initialization routine
    solve (); // processing routine

    return 0;
}

/* CHECK FOR ADJACENT NODES
if ( i + 1 < M ) { AdjM[i + 1][j] = true; }
if ( i > 0 ) { AdjM[i - 1][j] = true; }
if ( j + 1 < N ) { AdjM[i][j + 1] = true; }
if ( j > 0 ) { AdjM[i][j - 1] = true; }
*/
