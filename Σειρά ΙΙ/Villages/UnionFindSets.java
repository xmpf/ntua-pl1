/*
 * Notes: Disjoint sets data structure
 *        with several optimizations
 *        such as:
 *          1. tree structure
 *          2. union-by-rank
 *          3. path-compression
 * Operations:
 *      1. find/1    :: O(log n)
 *      2. unify/2   :: O(log _n_)
 *      3. makeSet/1 :: O(1)
 */

public class UnionFindSets {
    private int size;  // size of structure
    private int totalSets; // amount of current disjoint sets
    private int[] sz;  // keep track of each element size
    private int[] pid; // pid[i] -> point to parent(i)


    // constructor
    public UnionFindSets (int n) {
        if (n <= 0)
            throw new IllegalArgumentException("Wrong size");

        this.size = totalSets = n; // each element is one set
        this.sz  = new int[n + 1]; // counting starts
        this.pid = new int[n + 1]; // from `1`

        for (int i = 0; i <= n; i++) { // init
            this.pid[i] = i; // self root
            this.sz[i]  = 1; // initial set size
        }
    }

    // find `set` where element `e` belongs
    public int find (int e) {
        int root = e; // find root of `e`
        while ( root != pid[root] ) { root = pid[root]; }

        while (e != root) { // path compression heuristic
            int next = pid[e];
            pid[e] = root;
            e = next;
        }
        return root;
    }

    public boolean isConnected (int p, int q) {
        // return whether or not
        // elements `p` and `q`
        // are in the same set
        return ( find(p) == find(q) );
    }

    /* Getters */
    public int getSize () { return this.size; }
    public int getSets () { return this.totalSets; }


    // Unification
    public void unify (int p, int q) {
        int __p = find (p), // __p :: root of `p`
            __q = find (q); // __q :: root of `q`

        if ( __p == __q ) return; // skip as are the same set

        // Union-by-rank heuristic
        if ( sz[__p] < sz[__q] ) { // append `__p` tree to `__q`
            sz[__q]  += sz[__p];
            pid[__p] = __q;
        } else { // append `__q` tree to `__p`
            sz[__p] += sz[__q];
            pid[__q] = __p;
        }
        this.totalSets--; // since `roots` are different
                          // decrease total since
                          // two sets will be unified to one
    }


    @Override
    public String toString () { // for debugging purposes
        // print links
        StringBuffer sb = new StringBuffer();
        for (int i = 1; i < pid.length; i++)
            sb.append("n[" + i + "] -> "
                    + "n[" + pid[i] + "]\n");
        // []->[]
        return sb.toString();
    }
}
