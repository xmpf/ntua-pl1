#include <iostream>
#include <new>


typedef long long int bigInt;

/** main **/
int main(int argc, char *argv[]) {

    /********[ Input file ]************/
    FILE *fin = fopen (argv[1], "r");
    if (fin == NULL) { exit(EXIT_FAILURE); }

    /********[ Data structures]********/
    typedef struct {
        bigInt value;
        bigInt index;
    } pair_t;
    pair_t *L;
    pair_t *R;

    /********[ Parse input ]***********/
    bigInt n, // number of stops
             i = 0, j = 0, // index
            *A; // array of heights

    fscanf (fin, " %lld", &n);

    try { // error handling for failed memory allocations
        A = new bigInt[n]; // allocate space for heights
        L = new pair_t[n];
        R = new pair_t[n];
    } catch (const std::bad_alloc& e) {
        std::cout << "Allocation failed: " << e.what() << '\n';
    }

    // parse-from-file loop
    while ((i < n) && (!feof (fin))) { // while not EOF encountered :: O(n)
        fscanf (fin, " %lld", &A[i]);
        i++;
    }

    /*******[ Processing ]*****/
    // A: array of all heights
    // L: array of <value, index> from LEFT -> RIGHT
    // ... current < previous
    // R: array of <value, index> from RIGHT -> LEFT
    // ... current > previous
    pair_t l, r;
    l.value = A[0];
    l.index = 1;
    L[0] = l;

    r.value = A[n - 1];
    r.index = n;
    R[0] = r;

    bigInt rLim = 0, lLim = 0;

    // LEFT -> RIGHT traverse
    j = 1;
    for (i = 1; i < n; i++) { // populate L list :: O(n)
        if (l.value > A[i]) {
            l.value = A[i];
            l.index = i + 1;
            L[j++] = l;
        }
        lLim = j;
    }
    // RIGHT -> LEFT traverse
    j = 1;
    for (i = n - 2; i >= 0; i--) { // populate R list :: O(n)
        if ((r.value) < A[i]) {
            r.value = A[i];
            r.index = i + 1;
            R[j++] = r;
        }
        rLim = j;
    }

    // return max (|Jindex - Iindex|) forall 0 < i,j < N
    bigInt max = 0, length = 0;

    for (i = 0; i < lLim; i++) {
        for (j = rLim - 1; L[i].value < R[j].value; j--) {}
        length = R[j + 1].index - L[i].index;
        if (max < length) { max = length; }
        i++;
    }
    printf ("Result: %lld\n", max);

    /*****[ Clean-Up routine ]*****/
    delete[] A; // free allocated space
    A = NULL;   // point A to NULL

    delete[] L;
    L = NULL;

    delete[] R;
    R = NULL;

    fclose (fin);

    return 0;
} // end-of-main
