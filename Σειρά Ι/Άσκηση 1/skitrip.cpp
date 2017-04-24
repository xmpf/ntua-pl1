//
// Michalis Papadopoullos (031-14702)
// Programming Languages I : First exercise (skitrip)
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int bigInt;


/****[ init ]*****/
inline void init (vector<bigInt> &A, vector<bigInt> &L, vector<bigInt> &R, bigInt n)
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
inline bigInt skitrip (vector<bigInt> &A, vector<bigInt> &L, vector<bigInt> &R)
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

    vector<bigInt>  A,  // Heights
                    L,  // indexes LEFT -> RIGHT
                    R;  // indexes RIGHT -> LEFT
    bigInt n = 0; // number of stops

    init(A, L, R, n); // call initialization routine

    cout << "Result: " << skitrip (A, L, R) << endl;

    return 0;
} // end-of-main