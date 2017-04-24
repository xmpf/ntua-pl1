// ECE NTUA
// Michalis Papadopoullos (031-14702)
// Programming Languages I : First exercise (skitrip)

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int bigInt;
vector<bigInt>  A,  // Heights
                L,  // indexes LEFT -> RIGHT
                R;  // indexes RIGHT -> LEFT
bigInt  n = 0; // number of stops

/****[ init ]*****/
inline void init (void)
{
    bigInt i = 0; // index
    cin >> n;
    L.push_back (0);
    R.push_back (n - 1);
    A.resize ((unsigned long long)n);

    // parse input
    for (i = 0; i < n; i++) { cin >> A[i]; }

    // populate L vector
    for (i = 1; i < n; i++) {
        if (A[L.back()] > A[i]) { L.push_back(i); } // store indexes
    }

    // populate R vector
    for (i = n - 2; i >= 0; i--) {
        if (A[R.back()] < A[i]) { R.push_back(i); } // store indexes
    }

} // end-of-init

/*****[ skitrip ]****/
inline bigInt skitrip (void)
{
    bigInt ans = 0; // result
    int i = 0, j;   // indexes

    for (i = 0; i < (int)L.size(); i++) { // LEFT -> RIGHT
        for (j = (int)R.size() - 1; A[L[i]] < A[R[j]]; j--) { /* find minimum j */ }
        ans = max (ans, R[j + 1] - L[i]);
    }

    return ans;
} // end-of-skitrip

/********[ main ]**********/
int main (int argc, char *argv[])
{
    if (argc != 2) { throw std::runtime_error ("Error: Wrong parameters!\n"); }
    freopen (argv[1], "r", stdin); // I/O redirection
    std::ios::sync_with_stdio(false); //  If the synchronization is turned off, the C++ standard streams are allowed to buffer their I/O independently, which may be considerably faster in some cases.

    init (); // call initialization routine

    cout << "Result: " << skitrip () << endl;

    { // Return (possible) memory to OS
        A.clear();      A.shrink_to_fit();
        L.clear();      L.shrink_to_fit();
        R.clear();      R.shrink_to_fit();
    }

    return 0;
} // end-of-main

/******************************************************************************************************

 From Valgrind FAQ: "My program uses the C++ STL and string classes.
                    Valgrind reports 'still reachable' memory leaks
                    involving these classes at the exit of the program,
                    but there should be none."

 First of all: relax, it's probably not a bug, but a feature.
 Many implementations of the C++ standard libraries use their own
 memory pool allocators. Memory for quite a number of destructed objects
 is not immediately freed and given back to the OS, but kept in the pool(s)
 for later re-use. The fact that the pools are not freed at the exit
 of the program cause Valgrind to report this memory as still reachable.
 The behaviour not to free pools at the exit could be called a bug of the library.

 ******************************************************************************************************/